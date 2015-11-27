#include "SHA256Integrity.h"
#include "cryptocpp562/sha.h"

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