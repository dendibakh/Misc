#include "RestoreFile.h"
#include "StoreFile.h"
#include "testUtil.h"
#include "util.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

using namespace std;
using namespace boost::filesystem;

namespace 
{
     void checkRestoreOneFile(const string& testFile, const string& testFolder, bool compareFiles)
     {
             path filePath = TestFolderPath + testFolder;
             filePath /= testFile;
             path localFolderPath = TestFolderPath + testFolder;
             path restoreFolderPath = localFolderPath; restoreFolderPath /= "Restore";
             path binaryPath = localFolderPath; binaryPath /= "Output.bin";

             if (exists(binaryPath))
                     remove(binaryPath);
             if (exists(restoreFolderPath))
                     remove_all(restoreFolderPath);
             create_directory(restoreFolderPath);
             
             EXPECT_TRUE(StoreFile(filePath, binaryPath).good());
             ifstream binary(binaryPath.string().c_str(), ifstream::binary);
             EXPECT_EQ(FLAG_FILE, getFlagFromBinary(binary));
             RestoreFile rf(binary, restoreFolderPath);
             EXPECT_TRUE(rf.good());

             EXPECT_TRUE(exists(rf.getOutputPath()));
             if (compareFiles)
                EXPECT_TRUE(compareTwoFiles(filePath, rf.getOutputPath()));
     }

     void checkRestoreOneFile_CompareFiles(const string& testFile, const string& testFolder)
     {
             checkRestoreOneFile(testFile, testFolder, true);
     }

     void checkRestoreOneFile_NoCompareFiles(const string& testFile, const string& testFolder)
     {
             checkRestoreOneFile(testFile, testFolder, false);
     }
}      
 
TEST(TestRestoreFile, test1) { checkRestoreOneFile_CompareFiles("test.txt", "TestRestoreSingleFile1");    }
//TEST(TestRestoreFile, test2) { checkRestoreOneFile_CompareFiles("video.mp4", "TestRestoreSingleFile2");   }
TEST(TestRestoreFile, test3) { checkRestoreOneFile_CompareFiles("test.txt", "TestRestoreSingleFile3");    }
//TEST(TestRestoreFile, test4) { checkRestoreOneFile_NoCompareFiles("video.mp4", "TestRestoreSingleFile4"); }
//TEST(TestRestoreFile, test5) { checkRestoreOneFile_NoCompareFiles("video.mp4", "TestRestoreSingleFile5"); }
