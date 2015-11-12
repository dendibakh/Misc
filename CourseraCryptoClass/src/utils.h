#pragma once
#include <string>
#include <sstream>

namespace
{
    template <class T>
    void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
    {
         EXPECT_EQ(lhs.size(), rhs.size());
         EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    std::string hex_to_string(const std::string& str)
    {
        size_t N = str.size();
        std::string retStr;
        for (size_t i = 0; i < N; i+=2)
        {
            std::stringstream stream(str.substr(i, 2));
            unsigned int c = 0;
            stream >> std::hex >> c;
            retStr += c;
        }
        return retStr;
    }

    std::string XORstrings(const std::string& lhs, const std::string& rhs)
    {
        size_t minLen = std::min(lhs.size(), rhs.size());
        std::string retStr(minLen, 0);
        for (size_t i = 0; i < minLen; ++i)
        {
            retStr[i] = lhs[i] ^ rhs[i];
        }
        //retStr.append(lhs, minLen, std::string::npos);
        //retStr.append(rhs, minLen, std::string::npos);
        return retStr;
    }

    bool isLetter(unsigned char c)
    {
        return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
    }

    bool isTextSymbol(unsigned char c)
    {
        return c >= 32 && c <= 126;
    }
}