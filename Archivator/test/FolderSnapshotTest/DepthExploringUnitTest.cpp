#include "StoreFolder.h"
#include "RestoreFolder.h"
#include "testUtil.h"
#include "util.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

using namespace std;
using namespace boost::filesystem;

const int MAX_DEPTH = std::numeric_limits<int>::max();

namespace
{
    size_t getFolderDepth(const path& p)
    {
            typedef vector<path> dirVector;

            dirVector dirVec;
            
            copy(directory_iterator(p), directory_iterator(), CommonInserter(dirVec));

            size_t depth = 0;
            dirVector::const_iterator iter(dirVec.begin());
            for (; iter != dirVec.end(); ++iter)
            {
                    if ( is_directory(*iter) ) 
                            depth = std::max(depth, getFolderDepth(*iter) + 1);
            }
            return depth;
    }
              
    void checkRestoreOneFolder(const string& testFolder, size_t depth, size_t checkDepth)
    {
           path curFolderPath = TestFolderPath + testFolder;
           path folderPath = curFolderPath; folderPath /= path("InitialDir");
           path binaryPath = curFolderPath; binaryPath /= path("Output.bin");
           path restoreFolderPath = curFolderPath; restoreFolderPath /= path("RestoreDir");

           if (exists(binaryPath))
                remove(binaryPath);
           if (exists(restoreFolderPath))
                remove_all(restoreFolderPath);
           create_directory(restoreFolderPath);

           EXPECT_TRUE(StoreFolderNoFilterWithDepth(folderPath, binaryPath, depth).good());
           EXPECT_TRUE(RestoreFolderNoLogging(binaryPath, restoreFolderPath).good());

           path checkFolderPath = restoreFolderPath; checkFolderPath /= path("InitialDir");
           EXPECT_EQ(checkDepth, getFolderDepth(checkFolderPath));
    }
}

TEST(TestDepthExploring, test1) { checkRestoreOneFolder("TestDepthExploring1", 0, 0); }
TEST(TestDepthExploring, test2) { checkRestoreOneFolder("TestDepthExploring2", 1, 1); }
TEST(TestDepthExploring, test3) { checkRestoreOneFolder("TestDepthExploring3", 2, 2); }
TEST(TestDepthExploring, test4) { checkRestoreOneFolder("TestDepthExploring4", 3, 2); }
TEST(TestDepthExploring, test5) { checkRestoreOneFolder("TestDepthExploring5", MAX_DEPTH, 2); }
