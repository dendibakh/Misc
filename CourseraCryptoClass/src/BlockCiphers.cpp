#include "BlockCiphers.h"
#include "cryptocpp562/aes.h"
#include "cryptocpp562/modes.h"
#include "cryptocpp562/filters.h"
#include "cryptocpp562/hex.h"
#include "utils.h"
#include <stdexcept>

using namespace CryptoPP;

namespace LibImplementation
{
	std::string encrypt_AES_CBC(const std::string& key, const std::string& iv, const std::string& plainText)
	{
		if (iv.size() != AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Lenght of init vector should be 16 bytes.");
		if (key.size() != AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Key should be 16 bytes.");		
	
		byte aes_key[AES::DEFAULT_KEYLENGTH];
		memcpy(&aes_key, key.data(), sizeof(aes_key));

		byte initVect[AES::BLOCKSIZE];	
		memcpy(&initVect, iv.data(), sizeof(initVect));


		std::string cipher;
		std::string encoded;
		try
		{

			CBC_Mode< AES >::Encryption e;
			e.SetKeyWithIV( aes_key, AES::DEFAULT_KEYLENGTH, initVect );
		    	// The StreamTransformationFilter adds padding as required. ECB and CBC Mode must be padded to the block size of the cipher.
		    	StringSource( plainText, true, new StreamTransformationFilter( e, new StringSink( cipher ) ) );
			// Pretty print cipher text
			StringSource( cipher, true, new HexEncoder(new StringSink( encoded ) ) );
		}
		catch( const CryptoPP::Exception& e )
		{
	    		throw std::runtime_error(e.what());
		}

		return encoded;
	}

	std::string decrypt_AES_CBC(const std::string& key, const std::string& cipher)
	{
		if (cipher.size() < AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Lenght of init vector should be 16 bytes.");
		if (key.size() != AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Key should be 16 bytes.");		
	
		byte aes_key[AES::DEFAULT_KEYLENGTH];
		memcpy(&aes_key, key.data(), sizeof(aes_key));

		byte iv[AES::BLOCKSIZE];
		memcpy(&iv, cipher.data(), sizeof(iv));

		CBC_Mode< AES >::Decryption d;
		d.SetKeyWithIV( aes_key, AES::DEFAULT_KEYLENGTH, iv );
	
		std::string decoded;
		// The StreamTransformationFilter removes padding as required.
		StringSource( cipher, true, new StreamTransformationFilter( d, new StringSink( decoded ) ) ); 

		return decoded.substr(AES::BLOCKSIZE);
	}

	std::string encrypt_AES_CTR(const std::string& key, const std::string& iv, const std::string& plainText)
	{
		if (iv.size() != AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Lenght of init vector should be 16 bytes.");
		if (key.size() != AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Key should be 16 bytes.");		
	
		byte aes_key[AES::DEFAULT_KEYLENGTH];
		memcpy(&aes_key, key.data(), sizeof(aes_key));

		byte initVect[AES::BLOCKSIZE];	
		memcpy(&initVect, iv.data(), sizeof(initVect));


		std::string cipher;
		std::string encoded;
		try
		{

			CTR_Mode< AES >::Encryption e;
			e.SetKeyWithIV( aes_key, AES::DEFAULT_KEYLENGTH, initVect );
		    	// The StreamTransformationFilter adds padding as required. ECB and CBC Mode must be padded to the block size of the cipher.
		    	StringSource( plainText, true, new StreamTransformationFilter( e, new StringSink( cipher ) ) );
			// Pretty print cipher text
			StringSource( cipher, true, new HexEncoder(new StringSink( encoded ) ) );
		}
		catch( const CryptoPP::Exception& e )
		{
	    		throw std::runtime_error(e.what());
		}

		return encoded;
	}

	std::string decrypt_AES_CTR(const std::string& key, const std::string& cipher)
	{
		if (cipher.size() < AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Lenght of init vector should be 16 bytes.");
		if (key.size() != AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Key should be 16 bytes.");		
	
		byte aes_key[AES::DEFAULT_KEYLENGTH];
		memcpy(&aes_key, key.data(), sizeof(aes_key));

		byte iv[AES::BLOCKSIZE];
		memcpy(&iv, cipher.data(), sizeof(iv));

		CTR_Mode< AES >::Decryption d;
		d.SetKeyWithIV( aes_key, sizeof(aes_key), iv );

		std::string decoded;
		// The StreamTransformationFilter removes  padding as required.
		StringSource ss3( cipher.substr(AES::BLOCKSIZE), true, new StreamTransformationFilter( d, new StringSink( decoded ) ) );

		return decoded;
	}
}

#include <iostream>

namespace MyModesImplementation
{
	std::string decrypt_AES_CBC(const std::string& key, const std::string& cipher)
	{
		if (cipher.size() < AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Lenght of init vector should be 16 bytes.");
		if (key.size() != AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Key should be 16 bytes.");		
	
		byte aes_key[AES::DEFAULT_KEYLENGTH];
		memcpy(&aes_key, key.data(), sizeof(aes_key));

		AESDecryption d;		        
        	d.SetKey(aes_key, AES::DEFAULT_KEYLENGTH);

		size_t cipherSize = cipher.size();
		std::string decoded(cipherSize - AES::BLOCKSIZE, 0);			
		byte* curBlock = (byte*)cipher.data();
		byte* decBlock = (byte*)decoded.data();  
		for (size_t curBlockOffset = AES::BLOCKSIZE; curBlockOffset < cipherSize; curBlockOffset += AES::BLOCKSIZE)		
		{
			d.ProcessAndXorBlock(curBlock + AES::BLOCKSIZE, curBlock, decBlock);
			decBlock += AES::BLOCKSIZE;
			curBlock += AES::BLOCKSIZE;
		}
		decoded.erase(decoded.size() - (byte)decoded.back(), (byte)decoded.back());

		return decoded;
	}

	std::string decrypt_AES_CTR(const std::string& key, const std::string& cipher)
	{
		if (cipher.size() < AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Lenght of init vector should be 16 bytes.");
		if (key.size() != AES::DEFAULT_KEYLENGTH)
			throw std::runtime_error("Key should be 16 bytes.");		
	
		byte aes_key[AES::DEFAULT_KEYLENGTH];
		memcpy(&aes_key, key.data(), sizeof(aes_key));

		byte iv[AES::BLOCKSIZE];
		memcpy(&iv, cipher.data(), sizeof(iv));

		CTR_Mode< AES >::Decryption d;
		d.SetKeyWithIV( aes_key, sizeof(aes_key), iv );

		std::string decoded;
		// The StreamTransformationFilter removes  padding as required.
		StringSource ss3( cipher.substr(AES::BLOCKSIZE), true, new StreamTransformationFilter( d, new StringSink( decoded ) ) );

		return decoded;
	}
}
