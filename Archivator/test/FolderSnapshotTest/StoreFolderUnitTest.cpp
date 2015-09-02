#include "StoreFolder.h"
#include "testUtil.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

using namespace std;
using namespace boost::filesystem;

namespace 
{
    uintmax_t directory_size(const path& dir)
    {
            vector<path> v;
            copy(directory_iterator(dir), directory_iterator(), back_inserter(v));
                    
            uintmax_t size = 0;

            size += sizeof(char);
            size += dir.filename().string().size() + 1;
                                            
            for (vector<path>::const_iterator it (v.begin()); it != v.end(); ++it)
            {
                    size += sizeof(char); 
                    size += file_size(*it);
                    size += it->filename().string().size() + 1;
                    size += sizeof(uintmax_t);
                    size += sizeof(time_t);
            }

            size += sizeof(char);

            return size;
    }
    void checkStoreOneFolder(const string& testFolder)
    {
            path folderPath = TestFolderPath + testFolder; folderPath /= "InitialDir";
            path binaryPath = TestFolderPath + testFolder; binaryPath /= "Output.bin";

            if (exists(binaryPath))
                    remove(binaryPath);
            uintmax_t size = directory_size(folderPath);
            
            EXPECT_TRUE(StoreFolderNoFilterFullDepth(folderPath, binaryPath).good());
            
            EXPECT_TRUE(exists(binaryPath));
            EXPECT_EQ(size, file_size(binaryPath));
    }
}

TEST(TestStoreFolder, test1) { checkStoreOneFolder("TestStoreFolder1"); }
TEST(TestStoreFolder, test2) { checkStoreOneFolder("TestStoreFolder2"); }
