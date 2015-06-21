#include "stdafx.h"
#include "StoreFolder.h"
#include "RestoreFolder.h"
#include "testUtil.h"
#include "util.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace std;
using namespace boost::filesystem;

namespace FolderSnapshotTest
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
          
        [TestClass]
        public ref class DepthExploringUnitTest
        {
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

                       Assert::IsTrue(StoreFolderNoFilterWithDepth(folderPath, binaryPath, depth).good());
                       Assert::IsTrue(RestoreFolderNoLogging(binaryPath, restoreFolderPath).good());
       
                       path checkFolderPath = restoreFolderPath; checkFolderPath /= path("InitialDir");
                       Assert::AreEqual(checkDepth, getFolderDepth(checkFolderPath));
                }
        public: 
                [TestMethod] void TestDepthExploring1() { checkRestoreOneFolder("TestDepthExploring1", 0, 0); }
                [TestMethod] void TestDepthExploring2() { checkRestoreOneFolder("TestDepthExploring2", 1, 1); }
                [TestMethod] void TestDepthExploring3() { checkRestoreOneFolder("TestDepthExploring3", 2, 2); }
                [TestMethod] void TestDepthExploring4() { checkRestoreOneFolder("TestDepthExploring4", 3, 2); }
                [TestMethod] void TestDepthExploring5() { checkRestoreOneFolder("TestDepthExploring5", MAX_DEPTH, 2); }
        };
}
