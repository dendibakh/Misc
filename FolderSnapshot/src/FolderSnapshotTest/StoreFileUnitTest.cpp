#include "stdafx.h"
#include "StoreFile.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace std;
using namespace boost::filesystem;

namespace FolderSnapshotTest
{
        [TestClass]
        public ref class StoreFileUnitTest
        {
                void checkStoreOneFile(const string& testFile, const string& testFolder)
                {
                        path filePath = TestFolderPath + testFolder; filePath /= testFile;
                        path binaryPath = TestFolderPath + testFolder; binaryPath /= "Output.bin";

                        if (exists(binaryPath))
                                remove(binaryPath);

                        Assert::IsTrue(StoreFile(filePath, binaryPath).good());

                        Assert::IsTrue(exists(binaryPath));
                        Assert::AreEqual(sizeof(char) + file_size(filePath) + testFile.size() + 1 + sizeof(uintmax_t) + sizeof(time_t), file_size(binaryPath));
                }
        public: 
                [TestMethod] void TestStoreFile1() { checkStoreOneFile("test.txt", "TestStoreSingleFile1");   }
                [TestMethod] void TestStoreFile2() { checkStoreOneFile("video.mp4", "TestStoreSingleFile2");  }
                [TestMethod] void TestStoreFile3() { checkStoreOneFile("test.txt", "TestStoreSingleFile3");   }
                [TestMethod] void TestStoreFile4() { checkStoreOneFile("video.mp4", "TestStoreSingleFile4");  }
                [TestMethod] void TestStoreFile5() { checkStoreOneFile("video.mp4", "TestStoreSingleFile5");  }               
        };
}
