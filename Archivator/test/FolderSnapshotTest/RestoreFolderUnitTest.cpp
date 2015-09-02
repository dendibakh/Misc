#include "StoreFolder.h"
#include "RestoreFolder.h"
#include "testUtil.h"
#include "util.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

using namespace std;
using namespace boost::filesystem;

namespace 
{
    void checkRestoreOneFolder(const string& testFolder)
    {
            path curFolderPath = TestFolderPath + testFolder;
            path folderPath = curFolderPath; folderPath /= "InitialDir";
            path binaryPath = curFolderPath; binaryPath /= "Output.bin";
            path restoreFolderPath = curFolderPath; restoreFolderPath /= "RestoreDir";
            
            if (exists(binaryPath))
                    remove(binaryPath);
            if (exists(restoreFolderPath))
                    remove_all(restoreFolderPath);
            create_directory(restoreFolderPath);

            EXPECT_TRUE(StoreFolderNoFilterFullDepth(folderPath, binaryPath).good());
            EXPECT_TRUE(RestoreFolderNoLogging(binaryPath, restoreFolderPath).good());
            
            path checkFolderPath = restoreFolderPath; checkFolderPath /= "InitialDir";
            EXPECT_TRUE(compareTwoDirectories(folderPath, checkFolderPath));
    }
}

TEST(TestRestoreFolder, test1) { checkRestoreOneFolder("TestRestoreFolder1"); }
TEST(TestRestoreFolder, test2) { checkRestoreOneFolder("TestRestoreFolder2"); }
TEST(TestRestoreFolder, test3) { checkRestoreOneFolder("TestRestoreNestedFolder1"); }
TEST(TestRestoreFolder, test4) { checkRestoreOneFolder("TestRestoreNestedFolder2"); }
TEST(TestRestoreFolder, test5) { checkRestoreOneFolder("TestRestoreComplexFolder1"); }
TEST(TestRestoreFolder, test6) { checkRestoreOneFolder("TestRestoreComplexFolder2"); }
