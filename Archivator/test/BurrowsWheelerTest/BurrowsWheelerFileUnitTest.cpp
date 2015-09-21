#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "BurrowsWheeler.h"
#include "utils.h"
#include <boost/filesystem.hpp>
#include <fstream>

using namespace testing;
using namespace std;
using namespace boost::filesystem;

const string TestFolderPath = "./test/BurrowsWheelerTest/TestBinaries/";
const uintmax_t OneHundredMegabytes = 100 * 1024 * 1024;

namespace 
{
     bool compareTwoFiles(const path& rhs, const path& lhs)
     {
             ifstream rhs_f(rhs.string().c_str(), ifstream::binary);
             ifstream lhs_f(lhs.string().c_str(), ifstream::binary);

             if (!rhs_f || !lhs_f)
                     return false;

             if (file_size(rhs) != file_size(lhs))
                     return false;

             uintmax_t size = file_size(rhs);
             while (size > 0)
             {
                     size_t piecelength = 0;
                     if (size < OneHundredMegabytes)
                     {
                             piecelength = static_cast<size_t>(size);
                             size = 0;
                     }
                     else
                     {
                             piecelength = static_cast<size_t>(OneHundredMegabytes);
                             size -= OneHundredMegabytes;
                     }

                     std::string buffer_lhs, buffer_rhs;
                     buffer_lhs.resize(piecelength);
                     buffer_rhs.resize(piecelength);
                     
                     lhs_f.read(const_cast<char*>(buffer_lhs.data()), piecelength);
                     if (!lhs_f.good())
                             throw domain_error("Error while reading left-hand-side file.");

                     rhs_f.read(const_cast<char*>(buffer_rhs.data()), piecelength);
                     if (!rhs_f.good())
                             throw domain_error("Error while reading right-hand-side file.");

                     if (memcmp(buffer_lhs.data(), buffer_rhs.data(), piecelength))
                             return false;
             }

             rhs_f.close();
             lhs_f.close();

             return true;
     }

     void checkEncodeDecodeFile(const string& testFile, const string& testFolder, bool compareFiles)
     {
             path filePath = TestFolderPath + testFolder;
             path encodedPath = filePath;
             path decodedPath = filePath;
             filePath /= testFile;
             encodedPath /= "encoded.bin";
             decodedPath /= "decoded.bin";

             if (exists(encodedPath))
                     remove(encodedPath);
             if (exists(decodedPath))
                     remove(decodedPath);
             
             BurrowsWheelerFile().encode(filePath, encodedPath);
             BurrowsWheelerFile().decode(encodedPath, decodedPath);

             EXPECT_TRUE(exists(encodedPath));
             EXPECT_TRUE(exists(decodedPath));
             if (compareFiles)
                EXPECT_TRUE(compareTwoFiles(filePath, decodedPath));
     }

     void checkEncodeDecodeFile_CompareFiles(const string& testFile, const string& testFolder)
     {
             checkEncodeDecodeFile(testFile, testFolder, true);
     }

     void checkEncodeDecodeFile_NoCompareFiles(const string& testFile, const string& testFolder)
     {
             checkEncodeDecodeFile(testFile, testFolder, false);
     }

     template <class T>
     void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
     {
          EXPECT_EQ(lhs.size(), rhs.size());
          EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
     }
}      

TEST(BurrowsWheelerFileTest, test1) { checkEncodeDecodeFile_CompareFiles("Output.bin", "1");    }
TEST(BurrowsWheelerFileTest, test2) { checkEncodeDecodeFile_CompareFiles("Output.bin", "2");    }
TEST(BurrowsWheelerFileTest, test3) { checkEncodeDecodeFile_CompareFiles("Output.bin", "3");    }
