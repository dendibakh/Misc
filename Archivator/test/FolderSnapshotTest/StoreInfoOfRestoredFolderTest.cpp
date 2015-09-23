#include "StoreFolder.h"
#include "RestoreFolder.h"
#include "testUtil.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

using namespace std;
using namespace boost::filesystem;

namespace 
{
    class RestoreFolderWithLoggingTest : public RestoreFolder
    {
        public:
                RestoreFolderWithLoggingTest(const boost::filesystem::path& binaryPath, const boost::filesystem::path& folderPath) :
                                             RestoreFolder(binaryPath, folderPath)
                {}

                using RestoreFolder::filesCount;
                using RestoreFolder::foldersCount;
                using RestoreFolder::size;
                using RestoreFolder::files;
                using RestoreFolder::FileInfoVect;
    };
}

TEST(TestStoreInfoOfRestoredFolder, test1)                
{ 
    path curFolderPath = TestFolderPath; curFolderPath /= "TestInfoOfRestoredFolder";
    path folderPath = curFolderPath; folderPath /= "InitialDir";
    path binaryPath = curFolderPath; binaryPath /= "Output.bin";
    path restoreFolderPath = curFolderPath; restoreFolderPath /= "RestoreDir";
        
    if (exists(binaryPath))
            remove(binaryPath);
    if (exists(restoreFolderPath))
            remove_all(restoreFolderPath);
    create_directory(restoreFolderPath);

    EXPECT_TRUE(StoreFolderNoFilterFullDepth(folderPath, binaryPath).good());
    RestoreFolderWithLoggingTest rf(binaryPath, restoreFolderPath);
    EXPECT_TRUE(rf.good());
        
    EXPECT_EQ(2u, rf.filesCount);
    EXPECT_EQ(1u, rf.foldersCount);
    EXPECT_EQ(uintmax_t(164), rf.size);
    RestoreFolderWithLoggingTest::FileInfoVect files = rf.files;
    EXPECT_EQ(2u, files.size());
    EXPECT_TRUE(string("test0.txt") == files[0].filename);
    EXPECT_TRUE(0 == files[0].size);
    //EXPECT_EQ(string("Tue Sep  1 15:03:58 2015\n"), string(ctime(&files[0].creationTime))); // change it
    EXPECT_TRUE(string("test1.txt") == files[1].filename);
    EXPECT_EQ(uintmax_t(12), files[1].size);
    //EXPECT_EQ(string("Tue Sep  1 15:03:58 2015\n"), string(ctime(&files[1].creationTime))); // change it
}
