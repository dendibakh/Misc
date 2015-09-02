#include "testUtil.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;
using namespace boost::filesystem;

TEST(CompareTwoFolders, test)
{
     	path curFolderPath = TestFolderPath + "TestCompareTwoFolders/";
     	path equal1 = curFolderPath.string() + "Equal1/";
     	path equal2 = curFolderPath.string() + "Equal2/";
     	path NotEqual1 = curFolderPath.string() + "NotEqual1/";
     	path NotEqual2 = curFolderPath.string() + "NotEqual2/";
     	path NotEqual3 = curFolderPath.string() + "NotEqual3/";
     	path NotEqual4 = curFolderPath.string() + "NotEqual4/";
     	path NotEqual5 = curFolderPath.string() + "NotEqual5/";
     	EXPECT_TRUE(compareTwoDirectories(equal1, equal2));
     	EXPECT_FALSE(compareTwoDirectories(NotEqual1, NotEqual2));
     	EXPECT_FALSE(compareTwoDirectories(NotEqual1, NotEqual3));
     	EXPECT_FALSE(compareTwoDirectories(NotEqual1, NotEqual4));
     	EXPECT_FALSE(compareTwoDirectories(NotEqual1, NotEqual5));
}
