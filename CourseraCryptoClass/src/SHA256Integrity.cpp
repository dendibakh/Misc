#include "SHA256Integrity.h"
#include "cryptocpp562/sha.h"
#include <stdexcept>

using namespace CryptoPP;

const size_t ONE_KILO_BYTE = 1024;

namespace
{
    std::string computeSHA256(const std::string& str)
    {
        byte const* pbData = (byte*)str.data();
        size_t nDataLen = str.size();
        
        std::string hash(SHA256::DIGESTSIZE, '\0');
        byte* abDigest = (byte*)hash.data();
        
        SHA256().CalculateDigest(abDigest, pbData, nDataLen);
        return hash;
    }

    bool checkSHA256(const std::string& text, const std::string& hash)
    {
        return computeSHA256(text) == hash;
    }
}

std::string computeFirstSHA256(const std::string& fileAsStr)
{
    size_t fileSize = fileAsStr.size();
    size_t lastBlockSize = fileSize % ONE_KILO_BYTE;
    std::string hash = computeSHA256(fileAsStr.substr(fileSize - lastBlockSize, lastBlockSize));
    for (size_t pos = fileSize - lastBlockSize; pos >= ONE_KILO_BYTE; pos -= ONE_KILO_BYTE )
    {
        std::string textPlusHash = fileAsStr.substr(pos - ONE_KILO_BYTE, ONE_KILO_BYTE) + hash;
        hash = computeSHA256(textPlusHash);
    }
    return hash;
}

std::string injectSHA256Blocks(const std::string& fileAsStr)
{
    size_t fileSize = fileAsStr.size();

    size_t numbersOfSHA256Blocks = (fileSize - 1) / ONE_KILO_BYTE + 1;
    std::string resultStr;
    resultStr.resize(fileSize + numbersOfSHA256Blocks * SHA256::DIGESTSIZE);

    std::string hash;
    size_t lastBlockSize = fileSize % ONE_KILO_BYTE;
    if (lastBlockSize)
    {
	    std::string lastBlock = fileAsStr.substr(fileSize - lastBlockSize, lastBlockSize);
	    hash = computeSHA256(lastBlock);
	    memcpy((void*)(resultStr.data() + resultStr.size() - lastBlockSize - SHA256::DIGESTSIZE), (void*)hash.data(), hash.size());
	    memcpy((void*)(resultStr.data() + resultStr.size() - lastBlockSize), (void*)lastBlock.data(), lastBlock.size());
    }

    size_t posSrc = fileSize - lastBlockSize - ONE_KILO_BYTE;
    size_t posDst = resultStr.size() - lastBlockSize - SHA256::DIGESTSIZE - ONE_KILO_BYTE - SHA256::DIGESTSIZE;
    size_t blocksNumber = (fileSize - lastBlockSize) / ONE_KILO_BYTE;
    for (size_t i = 0; i < blocksNumber; ++i )
    {
        std::string text = fileAsStr.substr(posSrc, ONE_KILO_BYTE);
        hash = computeSHA256(text + hash);
        memcpy((void*)(resultStr.data() + posDst), (void*)hash.data(), hash.size());
        memcpy((void*)(resultStr.data() + posDst + SHA256::DIGESTSIZE), (void*)text.data(), text.size());
        posDst -= ONE_KILO_BYTE + SHA256::DIGESTSIZE;
        posSrc -= ONE_KILO_BYTE;
    }
    return resultStr;
}

std::string recoverSHA256InjectedFile(const std::string& fileAsStr)
{
    size_t fileSize = fileAsStr.size();

    size_t numbersOfSHA256Blocks = fileSize / (ONE_KILO_BYTE + SHA256::DIGESTSIZE) + 1;
    std::string resultStr;
    resultStr.resize(fileSize - numbersOfSHA256Blocks * SHA256::DIGESTSIZE);

    char* posSrc = (char*) fileAsStr.data();
    char* posDst = (char*) resultStr.data();

    for (size_t srcOffset = 0; srcOffset < fileSize; srcOffset += ONE_KILO_BYTE + SHA256::DIGESTSIZE)
    {
        size_t bytesLeft = fileSize - srcOffset;
        std::string text(posSrc + SHA256::DIGESTSIZE, ONE_KILO_BYTE);
        std::string hash(posSrc + SHA256::DIGESTSIZE + ONE_KILO_BYTE, SHA256::DIGESTSIZE);
        if (bytesLeft < ONE_KILO_BYTE + SHA256::DIGESTSIZE)
        {
            text.assign(posSrc + SHA256::DIGESTSIZE, bytesLeft - SHA256::DIGESTSIZE);    
            hash.clear(); 
        }
        
        std::string hashToVerify(posSrc, SHA256::DIGESTSIZE);        
        if (!checkSHA256(text + hash, hashToVerify))
            throw std::runtime_error("Wrong hash was calculated");

        memcpy(posDst, (void*)text.data(), text.size());

        posSrc += ONE_KILO_BYTE + SHA256::DIGESTSIZE;
        posDst += ONE_KILO_BYTE;
    }
    return resultStr;
}

