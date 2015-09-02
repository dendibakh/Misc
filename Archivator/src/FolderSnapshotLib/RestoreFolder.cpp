#include "RestoreFolder.h"
#include "RestoreFile.h"
#include <algorithm>
#include <sstream>
#include "util.h"
#include <iomanip> 

using namespace boost::filesystem;
using namespace std;

namespace Private
{
   RestoreFolder::RestoreFolder(ifstream* binary, const path& binaryFile, const path& folderPath, bool needPrintInfo) : 
                  binary(binary), folderPath(folderPath), binaryFile(binaryFile), needPrintInfo(needPrintInfo), filesCount(0), foldersCount(0), size(0)

   {
      // This is private constructor. Recursively created instances store binary handler in pointer "binary".
      runConstructor();
   }

   RestoreFolder::RestoreFolder(const path& binaryFile, const path& folderPath, bool needPrintInfo) : 
                  binary(0), folderPath(removeLastSlash(folderPath)), binaryFile(removeLastSlash(binaryFile)), needPrintInfo(needPrintInfo), filesCount(0), foldersCount(0), size(0)
   {  
      // This is public constructor. Only this constructor open input binary file.
      // All next recursive instances of RestoreFolder class use this handler.
      ifstream binaryHandler(binaryFile.string().c_str(), ifstream::binary);
      if (!binaryHandler)
      {
          error.assign("Can't read binary file: " + binaryFile.string() + ".");
      }
      else
      {
         binary = &binaryHandler;
         if (getFlagFromBinary(*binary) != FLAG_FOLDER) 
            error.assign("Can't read binary file: " + binaryFile.string() + ".");
         else
            runConstructor();
         binary = 0;
      }
      binaryHandler.close();
   }

   void RestoreFolder::runConstructor() const
   {
      try
      {
           checkExistFolder();
           restoreDirectoryInfo();
           generateOutput();
           if (needPrintInfo)
              printFolderInfo();
      }
      catch(exception& e)
      {
           error.assign(e.what());
      }
   }

   void RestoreFolder::checkExistFolder() const
   {
      if (!exists(this->folderPath) || !is_directory(this->folderPath))
         throw domain_error("No such folder: " + this->folderPath.string() + ".");
   }

   void RestoreFolder::restoreDirectoryInfo() const
   {
      try
      {
         stringbuf strBuf;
         binary->get(strBuf, '\0');
         if (!binary->good())
                 throw domain_error("Attempt to read the folder name. Error while reading from the file: " + binaryFile.string() + ".");

         binary->seekg(1, ios_base::cur);
         if (!binary->good())
                 throw domain_error("Attempt to set position in the binary handler. Error while reading from the file: " + binaryFile.string() + ". Binary may be corrupted.");

         subDirPath = folderPath;
         subDirPath /= path(strBuf.str());
         create_directory(subDirPath);
      }
      catch(exception& e)
      {
           error.assign(e.what());
      }
   }

   void RestoreFolder::generateOutput() const
   {
           bool done = false;
           while(!done)
           {
                   switch (getFlagFromBinary(*binary))
                   {
                      case FLAG_FILE:
                         restoreOneFile();
                         break;
                      case FLAG_FOLDER:
                         restoreNestedFolder();
                         break;
                      case FLAG_END_FOLDER:
                         done = true;
                         break;
                      default:
                         throw domain_error("Attempt to get the flag from binary handler. Wrong flag specified. Binary may be corrupted.");
                   }
           }
   }

   void RestoreFolder::restoreNestedFolder() const
   {
      RestoreFolder rf(binary, binaryFile, subDirPath, needPrintInfo);
      if (!rf.good())
         throw domain_error(rf.getError());
      if (needPrintInfo)
      {
         ++foldersCount;
         size += rf.getSizeInBytes();
      }
   }

   void RestoreFolder::restoreOneFile() const
   {
      RestoreFile rf(*binary, subDirPath);
      if (!rf.good())
         throw domain_error(rf.getError());
      if (needPrintInfo)
      {
         ++filesCount;
         size += rf.getSizeInBytes();
         FileInfo fileInfo = { rf.getOutputPath().filename().string(), rf.getSizeInBytes(), rf.getCreationTime() };
         files.push_back(fileInfo);
      }
   }

   void RestoreFolder::printFolderInfo() const
   {
      string dirInfoFileName = subDirPath.string() + "/directoryInfo.txt";
      ofstream dirInfo(dirInfoFileName.c_str(), ofstream::binary | ofstream::app);
      try
      {
              if (!dirInfo)
                      throw domain_error("Can't create directoryInfo file: " + dirInfoFileName + ".");

              dirInfo << "Number of nested folders: " << foldersCount << endl;
              if (!dirInfo.good())
                      throw domain_error("Attempt to write the number of nested folders. Error while writing to the file: " + dirInfoFileName + ".");

              dirInfo << "Number of nested files: " << filesCount << endl;
              if (!dirInfo.good())
                      throw domain_error("Attempt to write the number of nested files. Error while writing to the file: " + dirInfoFileName + ".");

              dirInfo << "Size in bytes: " << size << endl;
              if (!dirInfo.good())
                      throw domain_error("Attempt to write the size of folder in bytes. Error while writing to the file: " + dirInfoFileName + ".");

                          if (files.size())
                          {
                                  dirInfo << "List of files:" << endl;
                                  if (!dirInfo.good())
                                                  throw domain_error("Attempt to write the list of files. Error while writing to the file: " + dirInfoFileName + ".");

                                  for (std::vector<FileInfo>::const_iterator i = files.begin(); i != files.end(); ++i)
                                  {
                                         dirInfo << i - files.begin() + 1 << ". " << i->filename << " " << i->size << " bytes; " << ctime(&i->creationTime);
                                         if (!dirInfo.good())
                                                         throw domain_error("Attempt to write the file info. Error while writing to the file: " + dirInfoFileName + ".");
                                  }
                          }
      }
      catch (exception& e)
      {
              error.assign(e.what());
      }
      dirInfo.close();
   }

   void RestoreFolder::checkForError() const
   {
      if (!error.empty())
         throw domain_error(error);
   }

   bool RestoreFolder::good() const
   {
      return error.empty();
   }

   std::string RestoreFolder::getError() const
   {
      return error;
   }

   uintmax_t RestoreFolder::getSizeInBytes() const
   {
      checkForError();
      return size;
   }
}
