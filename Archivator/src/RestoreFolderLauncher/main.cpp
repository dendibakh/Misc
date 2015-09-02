#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <memory>
#include "RestoreFolder.h"

using namespace boost::program_options;
using namespace boost::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
   try 
   {
       options_description desc("Allowed options");
       desc.add_options()
           ("help", "produce help message")
           ("binary_file,b", value<string>(), "path to generated binary file")
           ("dest_folder,d", value<string>(), "destination folder")
           ("verbose,v", "print statistic for each folder");

       variables_map vm;
       store(parse_command_line(argc, argv, desc), vm);
       notify(vm);
   
       if (vm.count("help")) 
       {
           cout << "Usage: options_description [options]" << endl << desc;
           return 0;
       }

       if (!vm.count("binary_file"))
       {
           cout << "Please specify binary file." << endl << desc;
           return 1;
       }

       if (!vm.count("dest_folder"))
       {
           cout << "Please specify destination folder." << endl << desc;
           return 1;
       }

       path binary_file(vm["binary_file"].as< string >());
       if (!binary_file.is_absolute())
          binary_file = system_complete(binary_file);

       path dest_folder(vm["dest_folder"].as< string >());
       if (!dest_folder.is_absolute())
          dest_folder = system_complete(dest_folder);

       
       auto_ptr<IRestoreFolder> rf;
       if (vm.count("verbose"))
          rf.reset(new RestoreFolder(binary_file, dest_folder));
       else
          rf.reset(new RestoreFolderNoLogging(binary_file, dest_folder));
       if (!rf->good())
       {
          cout << rf->getError() << endl;
          return 1;
       }
   }                                                                    
   catch(std::exception& e)
   {
       cout << e.what() << endl;
       return 1;
   }
   return 0;
}
