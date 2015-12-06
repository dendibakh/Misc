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
    const std::string initialRequest_EncryptPart("f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeff");
    EXPECT_EQ(ERROR_TYPE_PADDING, sendHTTPRequest(initialRequest_FirstPart + initialRequest_EncryptPart));
}

