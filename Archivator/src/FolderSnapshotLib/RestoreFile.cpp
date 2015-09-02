#include "RestoreFile.h"
#include <sstream>
#include "util.h"

using namespace boost::filesystem;
using namespace std;

RestoreFile::RestoreFile(ifstream& binary, const boost::filesystem::path& outputDir) : outputDir(removeLastSlash(outputDir)), binary(binary)
{
        try
        {
                checkExistFile();
                setOutputFile();
                generateOutput();
        }
        catch(exception& e)
        {
                error.assign(e.what());
        }
}

void RestoreFile::checkExistFile() const
{
        if (!exists(this->outputDir) || !is_directory(this->outputDir))
                throw domain_error("No such file: " + this->outputDir.string() + ".");
}

void RestoreFile::setOutputFile() const
{
        try
        {
                if (!binary)
                        throw domain_error("RestoreFile: binary file is in invalid state");
        
                stringbuf strBuf;
                binary.get(strBuf, '\0');
                if (!binary.good())
                        throw domain_error("RestoreFile: Can't read file name from binary.");
                
                outputFilePath = outputDir;
                outputFilePath /= path(strBuf.str());

                binary.seekg(1, ios_base::cur);
                if (!binary.good())
                        throw domain_error("RestoreFile: Attempt to set position in the binary handler. Binary may be corrupted.");

                std::string buffer;
                buffer.resize(sizeof(uintmax_t));
                                
                binary.read(const_cast<char*>(buffer.data()), sizeof(uintmax_t));
                if (!binary.good())
                        throw domain_error("RestoreFile: Attempt to read the filename from the binary handler. Error while reading from the binary.");

                size = *((uintmax_t*)buffer.data());

                buffer.resize(sizeof(time_t));

                binary.read(const_cast<char*>(buffer.data()), sizeof(time_t));
                if (!binary.good())
                        throw domain_error("RestoreFile: Attempt to read the creation time of the file from the binary handler. Error while reading from the binary.");

                creationTime = *((time_t*)buffer.data());
        }
        catch (exception& e)
        {
                error.assign(e.what());
        }
}

void RestoreFile::generateOutput() const
{
        ofstream output(outputFilePath.string().c_str(), ofstream::binary | ofstream::app);

        if (!output)
            error.assign("RestoreFile: Can't create output file: " + outputFilePath.string() + ".");

        try
        {
                storeFileContent(binary, output, size);
        }
        catch (exception& e)
        {
                error.assign(e.what());
        }

        output.close();
}

bool RestoreFile::good() const
{
        return error.empty();
}

std::string RestoreFile::getError() const
{
        return error;
}

path RestoreFile::getOutputPath() const
{
        checkForError();
        return outputFilePath;
}

uintmax_t RestoreFile::getSizeInBytes() const
{
        checkForError();
        return size;
}

time_t RestoreFile::getCreationTime() const
{
        checkForError();
        return creationTime;
}

void RestoreFile::checkForError() const
{
        if (!error.empty())
                throw domain_error(error);
}
