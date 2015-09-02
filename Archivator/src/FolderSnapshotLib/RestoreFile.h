#pragma once
#include <string>
#include <boost/filesystem.hpp>
#include <fstream>

class RestoreFile
{
        void checkExistFile() const;
        void setOutputFile() const;
        void generateOutput() const;
        void checkForError() const;
public:
        RestoreFile(std::ifstream& binary, const boost::filesystem::path& outputDir);
        bool good() const;
        std::string getError() const;
        boost::filesystem::path getOutputPath() const;
        uintmax_t getSizeInBytes() const;
        time_t getCreationTime() const;
private:
        const boost::filesystem::path outputDir;
        mutable std::ifstream& binary;
        mutable std::string error;
        mutable boost::filesystem::path outputFilePath;
        mutable uintmax_t size;
        mutable time_t creationTime;
};
