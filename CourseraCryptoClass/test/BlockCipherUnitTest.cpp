#include "gtest/gtest.h"
#include "BlockCiphers.h"
#include "cryptocpp562/aes.h"
#include "utils.h"

#include "cryptocpp562/modes.h"
#include "cryptocpp562/filters.h"
#include "cryptocpp562/hex.h"

using namespace testing;
using namespace CryptoPP;
using namespace MyModesImplementation;

TEST(BlockCipherUnitTest, 1)
{
	std::string cipher = LibImplementation::encrypt_AES_CBC(hex_to_string("140b41b22a29beb4061bda66b6747e14"), hex_to_string("4ca00ff4c898d61e1edbf1800618fb28"), 
                                             hex_to_string("4ca00ff4c898d61e1edbf1800618fb2828a226d1"));
}

TEST(BlockCipherUnitTest, 2)
{
	std::string key = hex_to_string("140b41b22a29beb4061bda66b6747e14");
	std::string cipher = hex_to_string("4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1daafb94ffe0c5da05d9476be028ad7c1d81");

	std::string recoveredText = decrypt_AES_CBC(key, cipher); 
	EXPECT_EQ("Basic CBC mode encryption needs padding.", recoveredText);//.substr(AES::BLOCKSIZE));
}

TEST(BlockCipherUnitTest, 3)
{
	std::string key = hex_to_string("140b41b22a29beb4061bda66b6747e14");
	std::string cipher = hex_to_string("5b68629feb8606f9a6667670b75b38a5b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253");

	std::string recoveredText = decrypt_AES_CBC(key, cipher); 
	EXPECT_EQ("Our implementation uses rand. IV", recoveredText.substr(AES::BLOCKSIZE));
}

TEST(BlockCipherUnitTest, 4)
{
	std::string key = hex_to_string("36f18357be4dbd77f050515c73fcf9f2");
	std::string cipher = hex_to_string("69dda8455c7dd4254bf353b773304eec0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329");

	std::string recoveredText = decrypt_AES_CTR(key, cipher); 
	EXPECT_EQ("CTR mode lets you build a stream cipher from a block cipher.", recoveredText);
}

TEST(BlockCipherUnitTest, 5)
{
	std::string key = hex_to_string("36f18357be4dbd77f050515c73fcf9f2");
	std::string cipher = hex_to_string("770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451");

	std::string recoveredText = decrypt_AES_CTR(key, cipher); 
	EXPECT_EQ("Always avoid the two time pad!", recoveredText);
}

