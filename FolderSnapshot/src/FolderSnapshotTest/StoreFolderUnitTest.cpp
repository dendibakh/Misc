#include "stdafx.h"
#include "StoreFolder.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace std;
using namespace boost::filesystem;

namespace FolderSnapshotTest
{
        [TestClass]
        public ref class StoreFolderUnitTest
        {
                void checkStoreOneFolder(const string& testFolder)
                {
                        path folderPath = TestFolderPath + testFolder; folderPath /= "InitialDir";
                        path binaryPath = TestFolderPath + testFolder; binaryPath /= "Output.bin";

                        if (exists(binaryPath))
                                remove(binaryPath);
                        uintmax_t size = directory_size(folderPath);
                        
                        Assert::IsTrue(StoreFolderNoFilterFullDepth(folderPath, binaryPath).good());
                        
                        Assert::IsTrue(exists(binaryPath));
                        Assert::AreEqual(size, file_size(binaryPath));
                }

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

        public: 
                [TestMethod] void TestStoreFolder1() { checkStoreOneFolder("TestStoreFolder1"); }
                [TestMethod] void TestStoreFolder2() { checkStoreOneFolder("TestStoreFolder2"); }
        };
}