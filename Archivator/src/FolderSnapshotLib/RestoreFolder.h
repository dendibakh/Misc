#pragma once
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>

namespace Private
{
   class RestoreFolder
   {
           void checkExistFolder() const;
           void generateOutput() const;
           void restoreDirectoryInfo() const;
           void checkForError() const;
           void runConstructor() const;
           void restoreNestedFolder() const;
           void restoreOneFile() const;
           void printFolderInfo() const;
   protected:
                   struct FileInfo
           {
              std::string filename;
              uintmax_t size;
              time_t creationTime;
           };
           typedef std::vector<FileInfo> FileInfoVect;
           RestoreFolder(std::ifstream* binary, const boost::filesystem::path& binaryFile, const boost::filesystem::path& folderPath, bool needPrintInfo);
   public:
           RestoreFolder(const boost::filesystem::path& binaryPath, const boost::filesystem::path& folderPath, bool needPrintInfo);
           bool good() const;
           std::string getError() const;
           uintmax_t getSizeInBytes() const;
   private:
           mutable std::ifstream* binary;
           const boost::filesystem::path folderPath;
           const boost::filesystem::path binaryFile;
           const bool needPrintInfo;
           mutable boost::filesystem::path subDirPath;
           mutable std::string error;
   protected:
           mutable size_t filesCount;
           mutable size_t foldersCount;
           mutable uintmax_t size;
           mutable FileInfoVect files;
   };
}

typedef Private::RestoreFolder IRestoreFolder;

class RestoreFolderNoLogging : public IRestoreFolder
{
   public:
      RestoreFolderNoLogging(const boost::filesystem::path& binaryPath, const boost::filesystem::path& folderPath) :
                             IRestoreFolder(binaryPath, folderPath, false)
      {}
};

class RestoreFolder : public IRestoreFolder
{
   public:
      RestoreFolder(const boost::filesystem::path& binaryPath, const boost::filesystem::path& folderPath) :
                    IRestoreFolder(binaryPath, folderPath, true)
      {}
};
