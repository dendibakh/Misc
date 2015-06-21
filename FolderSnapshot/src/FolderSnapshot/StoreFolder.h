#pragma once
#include <boost/filesystem.hpp>
#include <unordered_set>
#include <string>

typedef std::unordered_set<std::string> extensionFilter;

namespace Private
{
   class StoreFolder
   {
   protected:
           void runConstructor() const;
   private:
           void checkExistFolder() const;
           void generateBinary() const;
           void storeFolderInfo() const;
           void checkForError() const;
           void storeFolderEnd() const;
           virtual bool canGoInDepth() const = 0;
           virtual bool isExtensionSuitable(boost::filesystem::path p) const = 0;
           virtual void storeNestedFolder(const boost::filesystem::path& folderPath, const boost::filesystem::path& binaryFile) const = 0;
   public:
           StoreFolder(const boost::filesystem::path& folderPath, const boost::filesystem::path& binaryFile);
           bool good() const;
           std::string getError() const;
           uintmax_t getSizeInBytes() const;
   private:
           const boost::filesystem::path folderPath;
           const boost::filesystem::path binaryFile;
           mutable uintmax_t size;
           mutable std::string error;
   };
}

typedef Private::StoreFolder IStoreFolder;

class StoreFolderNoFilterFullDepth : public Private::StoreFolder
{
      bool canGoInDepth() const;
      bool isExtensionSuitable(boost::filesystem::path p) const;
      void storeNestedFolder(const boost::filesystem::path& folderPath, const boost::filesystem::path& binaryFile) const;
   public:
      StoreFolderNoFilterFullDepth(const boost::filesystem::path& folderPath, const boost::filesystem::path& binaryFile); 
};

class StoreFolderNoFilterWithDepth : public Private::StoreFolder
{
      bool canGoInDepth() const;
      bool isExtensionSuitable(boost::filesystem::path p) const;
      void storeNestedFolder(const boost::filesystem::path& folderPath, const boost::filesystem::path& binaryFile) const;
   public:
      StoreFolderNoFilterWithDepth(const boost::filesystem::path& folderPath, const boost::filesystem::path& binaryFile, int depth); 
   private:
      const int depth;
};

class StoreFolder : public Private::StoreFolder
{
      bool canGoInDepth() const;
      bool isExtensionSuitable(boost::filesystem::path p) const;
      void storeNestedFolder(const boost::filesystem::path& folderPath, const boost::filesystem::path& binaryFile) const;
   public:
      StoreFolder(const boost::filesystem::path& folderPath, const boost::filesystem::path& binaryFile, const extensionFilter& filter, int depth);
   private:
      const extensionFilter& filter;
      const int depth;
};