#include "StoreFile.h"
#include "testUtil.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

using namespace std;
using namespace boost::filesystem;

namespace
{
    void checkStoreOneFile(const string& testFile, const string& testFolder)
    {
            path filePath = TestFolderPath + testFolder; filePath /= testFile;
            path binaryPath = TestFolderPath + testFolder; binaryPath /= "Output.bin";

            if (exists(binaryPath))
                    remove(binaryPath);

            EXPECT_TRUE(StoreFile(filePath, binaryPath).good());

            EXPECT_TRUE(exists(binaryPath));
            EXPECT_EQ(sizeof(char) + file_size(filePath) + testFile.size() + 1 + sizeof(uintmax_t) + sizeof(time_t), file_size(binaryPath));
    }
}
TEST(TestStoreFile, test1) { checkStoreOneFile("test.txt",  "TestStoreSingleFile1");  }
//TEST(TestStoreFile, test2) { checkStoreOneFile("video.mp4", "TestStoreSingleFile2");  }
TEST(TestStoreFile, test3) { checkStoreOneFile("test.txt",  "TestStoreSingleFile3");  }
//TEST(TestStoreFile, test4) { checkStoreOneFile("video.mp4", "TestStoreSingleFile4");  }
//TEST(TestStoreFile, test5) { checkStoreOneFile("video.mp4", "TestStoreSingleFile5");  }               
