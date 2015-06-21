#include "StoreFile.h"
#include <fstream>
#include "util.h"
#include <sys/stat.h>

using namespace boost::filesystem;
using namespace std;

StoreFile::StoreFile(const path& fileName, const path& binaryName) : fileName(removeLastSlash(fileName)), binaryName(removeLastSlash(binaryName))
{
   try
   {
        checkExistFile();
        generateBinary();
   }
   catch(exception& e)
   {
        error.assign(e.what());
   }
}

void StoreFile::checkExistFile() const
{
        if (!exists(this->fileName) || !is_regular(this->fileName))
           throw domain_error("No such file: " + this->fileName.string() + ".");
}

void StoreFile::generateBinary() const
{
        ifstream file(fileName.string(), ifstream::binary);
        ofstream output(binaryName.string(), ofstream::binary | ofstream::app);
        try
        {
                if (!file)
                   throw domain_error("Store file begin. Can't read the file: " + fileName.string() + ".");

                if (!output)
                   throw domain_error("Store file begin. Can't create binary file: " + binaryName.string() + ".");

                output << FLAG_FILE;
                if (!output.good())
                   throw domain_error("Attempt to write the begin file flag. Error while writing to the file: " + binaryName.string() + ".");

                output << fileName.filename().string() << '\0';
                if (!output.good())
                   throw domain_error("Attempt to write the file name. Error while writing to the file: " + binaryName.string() + ".");

                size = file_size(fileName);
                output.write((char*)&size, sizeof(uintmax_t));
                if (!output.good())
                   throw domain_error("Attempt to write the size of the file. Error while writing to the file: " + binaryName.string() + ".");

                struct stat filestatus;
                stat( fileName.string().c_str(), &filestatus );

                time_t creationTime = filestatus.st_ctime;
                output.write((char*)&creationTime, sizeof(time_t));
                if (!output.good())
                   throw domain_error("Attempt to write the file creation time. Error while writing to the file: " + binaryName.string() + ".");

                file.seekg(0, file.beg);
                if (!file.good())
                   throw domain_error("Error while setting position to the output file: " + fileName.string() + ".");

                storeFileContent(file, output, size);
        }
        catch (exception& e)
        {
                error.assign(e.what());
        }
        file.close();
        output.close();
}

bool StoreFile::good() const
{
        return error.empty();
}

uintmax_t StoreFile::getSizeInBytes() const
{
        checkForError();
        return size;
}

void StoreFile::checkForError() const
{
        if (!error.empty())
           throw domain_error(error);
}