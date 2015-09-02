#include "StoreFolder.h"
#include "StoreFile.h"
#include "util.h"
#include <algorithm>

using namespace boost::filesystem;
using namespace std;

namespace Private
{
   StoreFolder::StoreFolder(const path& folderPath, const path& binaryFile) : folderPath(removeLastSlash(folderPath)), binaryFile(removeLastSlash(binaryFile))
   {
   }

   void StoreFolder::runConstructor() const
   {
      try
      {
           checkExistFolder();
           storeFolderInfo();
           generateBinary();
           storeFolderEnd();
      }
      catch(exception& e)
      {
           error.assign(e.what());
      }
   }

   void StoreFolder::checkExistFolder() const
   {
      if (!exists(this->folderPath) || !is_directory(this->folderPath))
         throw domain_error("No such folder: " + this->folderPath.string() + ".");
   }

   void StoreFolder::storeFolderInfo() const
   {
           ofstream binary(binaryFile.string().c_str(), ofstream::binary | ofstream::app);
           try
           {
              if (!binary)
                      throw domain_error("Store folder begin. Can't read binary file: " + binaryFile.string() + ".");

              binary << FLAG_FOLDER;
              if (!binary.good())
                      throw domain_error("Attempt to write the begin folder flag. Error while writing to the file: " + binaryFile.string() + ".");

              binary << this->folderPath.filename().string() << '\0';
              if (!binary.good())
                      throw domain_error("Attempt to write the folder's name. Error while writing to the file: " + binaryFile.string() + ".");
           }
           catch(exception& e)
           {
              error.assign(e.what());
           }
           binary.close();
   }

   void StoreFolder::generateBinary() const
   {
      if (!good())
         return;

      SeparateInserter::pathVector files;
      SeparateInserter::pathVector folders;
      copy(directory_iterator(folderPath), directory_iterator(), SeparateInserter(folders, files));

      for (SeparateInserter::pathVector::const_iterator it(files.begin()); it != files.end(); ++it)
      {
          if (isExtensionSuitable(*it))
             StoreFile(*it, binaryFile);
      }
      for (SeparateInserter::pathVector::const_iterator it(folders.begin()); it != folders.end(); ++it)
      {
          if (canGoInDepth())
             storeNestedFolder(*it, binaryFile);
      }
   }

   void StoreFolder::storeFolderEnd() const
   {
      if (!good())
         return;

      ofstream binary(binaryFile.string().c_str(), ofstream::binary | ofstream::app);
      try
      {
         if (!binary)
                 throw domain_error("Store folder end. Can't read binary file: " + binaryFile.string() + ".");

         binary << FLAG_END_FOLDER;
         if (!binary.good())
                 throw domain_error("Attempt to write the end folder flag. Error while writing to the file: " + binaryFile.string() + ".");
      }
      catch(exception& e)
      {
           error.assign(e.what());
      }
      binary.close();
   }

   void StoreFolder::checkForError() const
   {
      if (!error.empty())
         throw domain_error(error);
   }

   bool StoreFolder::good() const
   {
      return error.empty();
   }

   std::string StoreFolder::getError() const
   {
      return error;
   }

   uintmax_t StoreFolder::getSizeInBytes() const
   {
      checkForError();
      return size;
   }
}

//////////////////////////////////
// StoreFolderNoFilterFullDepth //
//////////////////////////////////

StoreFolderNoFilterFullDepth::StoreFolderNoFilterFullDepth(const path& folderPath, const path& binaryFile) : Private::StoreFolder(folderPath, binaryFile)
{
   runConstructor();
}

bool StoreFolderNoFilterFullDepth::canGoInDepth() const
{
   return true;
}

bool StoreFolderNoFilterFullDepth::isExtensionSuitable(boost::filesystem::path p) const
{
   return true;
}

void StoreFolderNoFilterFullDepth::storeNestedFolder(const path& folderPath, const path& binaryFile) const
{
   StoreFolderNoFilterFullDepth(folderPath, binaryFile);
}

//////////////////////////////////
// StoreFolderNoFilterWithDepth //
//////////////////////////////////

StoreFolderNoFilterWithDepth::StoreFolderNoFilterWithDepth(const path& folderPath, const path& binaryFile, int depth) : Private::StoreFolder(folderPath, binaryFile), depth(depth)
{
   runConstructor();
}

bool StoreFolderNoFilterWithDepth::canGoInDepth() const
{
   return depth > 0;
}

bool StoreFolderNoFilterWithDepth::isExtensionSuitable(boost::filesystem::path p) const
{
   return true;
}

void StoreFolderNoFilterWithDepth::storeNestedFolder(const path& folderPath, const path& binaryFile) const
{
   StoreFolderNoFilterWithDepth(folderPath, binaryFile, depth - 1);
}

/////////////////
// StoreFolder //
/////////////////

StoreFolder::StoreFolder(const path& folderPath, const path& binaryFile, const extensionFilter& filter, int depth) : 
                         Private::StoreFolder(folderPath, binaryFile), filter(filter), depth(depth)
{
   runConstructor();
}

bool StoreFolder::canGoInDepth() const
{
   return depth > 0;
}

bool StoreFolder::isExtensionSuitable(path p) const
{
   string ext;
   for (; !p.extension().empty(); p = p.stem())
           ext = p.extension().string() + ext;
   return filter.find(ext) != filter.end();
}

void StoreFolder::storeNestedFolder(const path& folderPath, const path& binaryFile) const
{
   if (!depth)
      throw domain_error("Internal error. We can't explore nested folder: " + folderPath.string() + ".");
   StoreFolder(folderPath, binaryFile, filter, depth - 1);
}
