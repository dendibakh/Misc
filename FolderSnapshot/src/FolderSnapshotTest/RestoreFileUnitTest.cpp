#include "stdafx.h"
#include "RestoreFile.h"
#include "StoreFile.h"
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
        public ref class RestoreFileUnitTest
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
                        
                        Assert::IsTrue(StoreFile(filePath, binaryPath).good());
                        ifstream binary(binaryPath.string(), ifstream::binary);
                        Assert::AreEqual(FLAG_FILE, getFlagFromBinary(binary));
                        RestoreFile rf(binary, restoreFolderPath);
                        Assert::IsTrue(rf.good());

                        Assert::IsTrue(exists(rf.getOutputPath()));
                        if (compareFiles)
                           Assert::IsTrue(compareTwoFiles(filePath, rf.getOutputPath()));
                }

                void checkRestoreOneFile_CompareFiles(const string& testFile, const string& testFolder)
                {
                        checkRestoreOneFile(testFile, testFolder, true);
                }

                void checkRestoreOneFile_NoCompareFiles(const string& testFile, const string& testFolder)
                {
                        checkRestoreOneFile(testFile, testFolder, false);
                }
        public: 
                [TestMethod] void TestRestoreFile1() { checkRestoreOneFile_CompareFiles("test.txt", "TestRestoreSingleFile1");    }
                [TestMethod] void TestRestoreFile2() { checkRestoreOneFile_CompareFiles("video.mp4", "TestRestoreSingleFile2");   }
                [TestMethod] void TestRestoreFile3() { checkRestoreOneFile_CompareFiles("test.txt", "TestRestoreSingleFile3");    }
                [TestMethod] void TestRestoreFile4() { checkRestoreOneFile_NoCompareFiles("video.mp4", "TestRestoreSingleFile4"); }
                [TestMethod] void TestRestoreFile5() { checkRestoreOneFile_NoCompareFiles("video.mp4", "TestRestoreSingleFile5"); }
        };
}
