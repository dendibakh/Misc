#include "stdafx.h"
#include "StoreFolder.h"
#include "RestoreFolder.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace std;
using namespace boost::filesystem;

namespace FolderSnapshotTest
{
            class RestoreFolderWithLoggingTest : public RestoreFolder
                {
                public:
                        RestoreFolderWithLoggingTest(const boost::filesystem::path& binaryPath, const boost::filesystem::path& folderPath) :
                                                     RestoreFolder(binaryPath, folderPath)
                        {}
                        size_t getfilesCount() const
                        {
                                return filesCount;
                        }

            size_t getfoldersCount() const
                        {
                                return foldersCount;
                        }

            uintmax_t getsize() const
                        {
                                return size;
                        }
            
                        FileInfoVect getfiles() const
                        {
                                return std::move(files);
                        }
                };

        [TestClass]
        public ref class StoreInfoOfRestoredFolderUnitTest
        {
        public: 
                [TestMethod] void TestStoreInfoOfRestoredFolder() 
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

                    Assert::IsTrue(StoreFolderNoFilterFullDepth(folderPath, binaryPath).good());
                    RestoreFolderWithLoggingTest rf(binaryPath, restoreFolderPath);
                    Assert::IsTrue(rf.good());
                        
                    Assert::AreEqual(2u, rf.getfilesCount());
                    Assert::AreEqual(1u, rf.getfoldersCount());
                    Assert::AreEqual(uintmax_t(164), rf.getsize());
                    auto files = rf.getfiles();
                    Assert::AreEqual(2u, files.size());
                    Assert::IsTrue(string("test0.txt") == files[0].filename);
                    Assert::IsTrue(0 == files[0].size);
                    Assert::IsTrue(string("Sun Oct 12 15:25:29 2014\n") == string(ctime(&files[0].creationTime)));
                    Assert::IsTrue(string("test1.txt") == files[1].filename);
                    Assert::AreEqual(uintmax_t(12), files[1].size);
                    Assert::IsTrue(string("Sun Oct 12 15:25:29 2014\n") == string(ctime(&files[1].creationTime)));
                }
        };
}
