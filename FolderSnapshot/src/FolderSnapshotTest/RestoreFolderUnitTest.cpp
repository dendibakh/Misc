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
        [TestClass]
        public ref class RestoreFolderUnitTest
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

                        Assert::IsTrue(StoreFolderNoFilterFullDepth(folderPath, binaryPath).good());
                        Assert::IsTrue(RestoreFolderNoLogging(binaryPath, restoreFolderPath).good());
                        
                        path checkFolderPath = restoreFolderPath; checkFolderPath /= "InitialDir";
                        Assert::IsTrue(compareTwoDirectories(folderPath, checkFolderPath));
                }
        public: 
                [TestMethod] void TestRestoreFolder1() { checkRestoreOneFolder("TestRestoreFolder1"); }
                [TestMethod] void TestRestoreFolder2() { checkRestoreOneFolder("TestRestoreFolder2"); }
                [TestMethod] void TestRestoreNestedFolder1() { checkRestoreOneFolder("TestRestoreNestedFolder1"); }
                [TestMethod] void TestRestoreNestedFolder2() { checkRestoreOneFolder("TestRestoreNestedFolder2"); }
                [TestMethod] void TestRestoreComplexFolder1() { checkRestoreOneFolder("TestRestoreComplexFolder1"); }
                [TestMethod] void TestRestoreComplexFolder2() { checkRestoreOneFolder("TestRestoreComplexFolder2"); }
        };
}
