#include "util.h"
#include "testUtil.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

using namespace boost::filesystem;

TEST(TestRemoveLastSlash, test1)
{
    EXPECT_TRUE(path("G:\\Storage") == removeLastSlash("G:\\Storage\\"));
    EXPECT_TRUE(path("G:\\Storage") == removeLastSlash("G:\\Storage/"));
    EXPECT_TRUE(path("G:\\Storage") == removeLastSlash("G:\\Storage//"));
    EXPECT_TRUE(path("G:\\Storage") == removeLastSlash("G:\\Storage\\\\"));
    EXPECT_TRUE(path("G:\\Storage") == removeLastSlash("G:\\Storage////"));
    EXPECT_TRUE(path("G:\\Storage") == removeLastSlash("G:\\Storage//\\//\\"));
    EXPECT_TRUE(path("G:\\Storage") == removeLastSlash("G:\\Storage"));
}
