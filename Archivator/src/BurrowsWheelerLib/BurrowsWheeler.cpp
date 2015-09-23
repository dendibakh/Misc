#include "BurrowsWheeler.h"
#include "BurrowsWheelerTransform.h"
#include "MoveToFront.h"
#include "utils.h"
#include <fstream>

using namespace std;
using namespace boost::filesystem;

BurrowsWheeler::BurrowsWheeler()
{

}

BurrowsWheeler::~BurrowsWheeler()
{

}

BurrowsWheeler::compressedResult BurrowsWheeler::encode(const std::string& text)
{
    BurrowsWheelerTransform bwTransform(text);
    MoveToFront::encodedResult encodedStr = MoveToFront().encode(bwTransform.getTransformedStr());
    BurrowsWheeler::compressedResult compressed = HuffmanAlgorithm().getCompressedResult(encodedStr);
    
    std::vector<bool> originalStringRow = getBinaryRepresentation(bwTransform.getOriginalStringRow());
    compressed.insert(compressed.begin(), originalStringRow.begin(), originalStringRow.end());
    return compressed;
}

void BurrowsWheeler::decode(const compressedResult& compressedText, std::string& result)
{
    size_t OriginalStringRow = getValue(compressedText.begin(), compressedText.begin() + 8 * sizeof(size_t));
    
    std::string expanded;
    HuffmanAlgorithm().getExpandedResult(compressedText.begin() + 8 * sizeof(size_t), compressedText.end(), expanded);
    std::string decoded;
    MoveToFront().decode(expanded, decoded);
    BurrowsWheelerDecode bwDecode(OriginalStringRow, decoded, result);
}

std::string BurrowsWheeler::decode(const compressedResult& compressedText)
{
    std::string result;
    decode(compressedText, result);
    return result;
}

BurrowsWheelerFile::BurrowsWheelerFile()
{
}

BurrowsWheelerFile::~BurrowsWheelerFile()
{
}

void BurrowsWheelerFile::encode(const boost::filesystem::path& fileName, const boost::filesystem::path& binaryName)
{
   ifstream source(fileName.string().c_str(), ifstream::binary);
   ofstream destination(binaryName.string().c_str(), ofstream::binary | ofstream::app);
   if (!source)
           throw domain_error("Attempt to store content of the file. Can't read binary file");

   if (!destination)
           throw domain_error("Attempt to store content of the file. Can't create output file");

   uintmax_t size = file_size(fileName);
   const uintmax_t OneHundredMegabytes = 100 * 1024 * 1024;
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

           std::string buffer;
           buffer.resize(piecelength);
           
           source.read(const_cast<char*>(buffer.data()), piecelength);
           if (!source.good())
                   throw domain_error("Attempt to store content of the file. Error while reading source file.");

           BurrowsWheeler::compressedResult compressed = BurrowsWheeler().encode(buffer);
           std::string comprStr = convertToString(compressed);

           size_t bitsNumber = compressed.size();
           destination.write((char*)&bitsNumber, sizeof(size_t));
           if (!destination.good())
                   throw domain_error("Attempt to write the size of the compressed block. Error while writing to the file.");

           destination.write(comprStr.data(), comprStr.size());
           if (!destination.good())
                   throw domain_error("Attempt to store content of the file. Error while writing to the binary.");          
   }
}

void BurrowsWheelerFile::decode(const boost::filesystem::path& fileName, const boost::filesystem::path& binaryName)
{
   ifstream source(fileName.string().c_str(), ifstream::binary);
   ofstream destination(binaryName.string().c_str(), ofstream::binary | ofstream::app);
   if (!source)
           throw domain_error("Attempt to store content of the file. Can't read binary file");

   if (!destination)
           throw domain_error("Attempt to store content of the file. Can't create output file");

   while (true)
   {
           size_t sizeBlock = 0;
           {
               std::string buffer;
               buffer.resize(sizeof(size_t));
                               
               source.read(const_cast<char*>(buffer.data()), sizeof(size_t));
               if (source.eof())
                   return;
               if (!source.good())
                       throw domain_error("BurrowsWheelerFile::decode: Attempt to read the size of next block from the binary handler. Error while reading from the binary.");

               sizeBlock = *((size_t*)buffer.data());
           }

           std::string buffer;
           buffer.resize(sizeBlock);
           
           source.read(const_cast<char*>(buffer.data()), (sizeBlock - 1) / 8 + 1);
           if (!source.good())
                   throw domain_error("Attempt to store content of the file. Error while reading source file.");

           BurrowsWheeler::compressedResult compressed = convertToBoolVect(buffer);
           compressed.resize(sizeBlock);
           std::string decomprStr = BurrowsWheeler().decode(compressed);

           destination.write(decomprStr.data(), decomprStr.size());
           if (!destination.good())
                   throw domain_error("Attempt to store content of the file. Error while writing to the binary.");          
   } 
}
