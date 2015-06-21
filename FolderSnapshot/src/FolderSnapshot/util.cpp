#include "util.h"

using namespace std;

void storeFileContent(ifstream& source, ofstream& destination, uintmax_t size)
{
   if (!source)
           throw domain_error("Attempt to store content of the file. Can't read binary file");

   if (!destination)
           throw domain_error("Attempt to store content of the file. Can't create output file");

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

                   destination.write(buffer.data(), piecelength);
           if (!destination.good())
                   throw domain_error("Attempt to store content of the file. Error while writing to the binary.");          
   }
}

char getFlagFromBinary(std::ifstream& binary)
{
        if (!binary)
                throw domain_error("Attempt to get next flag from binary. Can't read binary file.");

        char retVal;
        binary.read(&retVal, sizeof(char));
        if (!binary.good())
                throw domain_error("Attempt to get next flag from binary. Error while reading binary.");
        return retVal;
}

boost::filesystem::path removeLastSlash(const boost::filesystem::path& path)
{
   string retPath = path.string();
   while (retPath.back() == '\\' || retPath.back() == '/')
   {
      retPath.pop_back();
   }
   return retPath;
}