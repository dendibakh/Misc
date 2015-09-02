#pragma once
#include <string>
#include <boost/filesystem.hpp>

class StoreFile
{
        void checkExistFile() const;
        void generateBinary() const;
        void checkForError() const;
public:
        StoreFile(const boost::filesystem::path& fileName, const boost::filesystem::path& binaryName);
        bool good() const;
        uintmax_t getSizeInBytes() const;
private:
        const boost::filesystem::path fileName;
        const boost::filesystem::path binaryName;
        mutable uintmax_t size;
        mutable std::string error;
};
