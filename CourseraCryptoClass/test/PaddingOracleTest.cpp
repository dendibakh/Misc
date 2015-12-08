#include "gtest/gtest.h"
#include "utils.h"
#include "PaddingOracle.h"

using namespace testing;

TEST(PaddingOracleUnitTest, 1)
{
    const std::string initialRequest("http://www.bing.com/");
    EXPECT_EQ(ERROR_TYPE_SUCCESS, sendHTTPRequest(initialRequest));
}

TEST(PaddingOracleUnitTest, 2)
{
    const std::string initialRequest_FirstPart("http://crypto-class.appspot.com/po?er=");
    const std::string initialRequest_EncryptPart("f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4");
    EXPECT_EQ(ERROR_TYPE_SUCCESS, sendHTTPRequest(initialRequest_FirstPart + initialRequest_EncryptPart));
}

TEST(PaddingOracleUnitTest, 3)
{
    const std::string initialRequest_FirstPart("http://crypto-class.appspot.com/po?er=");
    const std::string initialRequest_EncryptPart("f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb5");
    EXPECT_EQ(ERROR_TYPE_PADDING, sendHTTPRequest(initialRequest_FirstPart + initialRequest_EncryptPart));
}

TEST(PaddingOracleUnitTest, 4)
{
    const std::string firstPartOfRequest("http://crypto-class.appspot.com/po?er=");
    const std::string IV     = convertFromHex("f20bdba6ff29eed7b046d1df9fb70000");
    const std::string block1 = convertFromHex("58b1ffb4210a580f748b4ac714c001bd");
    const std::string block2 = convertFromHex("4a61044426fb515dad3f21f18aa577c0");
    const std::string block3 = convertFromHex("bdf302936266926ff37dbf7035d5eeb5");
    EXPECT_EQ("The Magic Words ", decodeLastBlock(firstPartOfRequest, IV + block1));
    EXPECT_EQ("are Squeamish Os", decodeLastBlock(firstPartOfRequest, IV + block1 + block2));
    EXPECT_EQ("", decodeLastBlock(firstPartOfRequest, IV + block1 + block2 + block3));
}

