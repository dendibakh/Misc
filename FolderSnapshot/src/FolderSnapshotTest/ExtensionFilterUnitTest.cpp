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
        bool checkFilesExtension(const path& p, const extensionFilter& filter)
        {
                typedef vector<path> dirVector;

                dirVector dirVec;
                
                copy(directory_iterator(p), directory_iterator(), CommonInserter(dirVec));

                dirVector::const_iterator iter(dirVec.begin());
                for (; iter != dirVec.end(); ++iter)
                {
                        if ( is_directory(*iter) ) 
                                if (!checkFilesExtension (*iter, filter))
                                        return false;
                                
                        if ( is_regular_file(*iter) )
                        {
                                string ext;
                                path copyP(*iter);
                                for (; !copyP.extension().empty(); copyP = copyP.stem())
                                        ext = copyP.extension().string() + ext;
                                if (filter.find(ext) == filter.end())
                                        return false;
                        }
                }
                return true;
        }

        [TestClass]
        public ref class ExtensionFilterUnitTest
        {
                 void checkRestoreOneFolder(const string& testFolder, const extensionFilter& filter)
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

                        Assert::IsTrue(StoreFolder(folderPath, binaryPath, filter, MAX_DEPTH).good());
                        Assert::IsTrue(RestoreFolderNoLogging(binaryPath, restoreFolderPath).good());
        
                        path checkFolderPath = restoreFolderPath; checkFolderPath /= path("InitialDir");
                        Assert::IsTrue(checkFilesExtension(checkFolderPath, filter));
                 }
        public: 
                [TestMethod]
                void TestExtensionFilter1()
                {
                        extensionFilter filter;
                        filter.insert(".txt");
                        checkRestoreOneFolder("TestExtensionFilter1", filter);
                }

                [TestMethod]
                void TestExtensionFilter2()
                {
                        extensionFilter filter;
                        checkRestoreOneFolder("TestExtensionFilter2", filter);
                }

                [TestMethod]
                void TestExtensionFilter3()
                {
                        extensionFilter filter;
                        filter.insert(".ttt");
                        checkRestoreOneFolder("TestExtensionFilter3", filter);
                }

                [TestMethod]
                void TestExtensionFilter4()
                {
                        extensionFilter filter;
                        filter.insert(".vcxproj");
                        filter.insert(".vcxproj.filters");
                        filter.insert(".sln");
                        checkRestoreOneFolder("TestExtensionFilter4", filter);
                }
        };
}
