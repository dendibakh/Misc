#include "gtest/gtest.h"
#include "SHA256Integrity.h"
#include "utils.h"
#include <algorithm>

using namespace testing;

namespace
{
    std::string convertToUpper(const std::string& str)
    {
        std::string retStr(str);
        std::transform(retStr.begin(), retStr.end(), retStr.begin(), ::toupper);
        return retStr;
    }
}

TEST(SHA256IntegrityTest, 1)
{
    std::string file1 = readFileAsString("./test/6 - 2 - Generic birthday attack (16 min).mp4");
    EXPECT_EQ(convertToUpper("03c08f4ee0b576fe319338139c045c89c3e8e9409633bea29442e21425006ea8"), convertToHex(computeFirstSHA256(file1)));
}

TEST(SHA256IntegrityTest, 2)
{
    std::string file1 = readFileAsString("./test/6 - 1 - Introduction (11 min).mp4");
    EXPECT_EQ(convertToUpper("5B96AECE304A1422224F9A41B228416028F9BA26B0D1058F400200F06A589949"), convertToHex(computeFirstSHA256(file1)));
}