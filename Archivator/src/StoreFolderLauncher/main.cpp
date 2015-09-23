#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <iostream>
#include <memory>
#include "StoreFolder.h"
#include "util.h"
#include "BurrowsWheeler.h"

using namespace boost;
using namespace boost::filesystem;
using namespace boost::program_options;
using namespace std;

const int MAX_DEPTH = std::numeric_limits<int>::max();

namespace
{
   string correctExtension(const string& ext)
   {
      string retExt = ext;
      if ((*retExt.begin()) != '.')
         retExt.insert(retExt.begin(), '.');
      return retExt;
   }

   extensionFilter parseExtensionFilter(const string& filter)
   {
      extensionFilter retFilter;
      typedef tokenizer<boost::char_separator<char> > tokenizer;
      char_separator<char> sepComma(",");
      tokenizer tokens(filter, sepComma);
      for (tokenizer::iterator i = tokens.begin(); i != tokens.end(); ++i)
         retFilter.insert(correctExtension(*i));
      return retFilter;
   }
}

int main(int argc, char* argv[])
{
   try 
   {
       int depth;
       options_description desc("Allowed options");
       desc.add_options()
           ("help", "produce help message")
           ("folder_path,f", value<string>(), "path to folder for making a snapshot")
           ("depth,d", value<int>(&depth)->default_value(MAX_DEPTH), "depth of exploring")
           ("extension_filter,e", value<string>(), "list of extensions separated by comma")
           ("compress,c", "compress the output snapshot");

       positional_options_description p;
       p.add("folder_path", -1);
       
       variables_map vm;
       store(command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
       notify(vm);
   
       if (vm.count("help")) 
       {
           cout << "Usage: options_description [options]" << endl << desc;
           return 0;
       }

       if (!vm.count("folder_path"))
       {
           cout << "Please specify folder_path." << endl << desc;
           return 1;
       }

       if (depth < 0)
       {
           cout << "Depth of exploring must be greater of equal to 0." << endl << desc;
           return 1;
       }

       path folder_path(vm["folder_path"].as< string >());
       if (!folder_path.is_absolute())
          folder_path = system_complete(folder_path);
       path binaryFile = folder_path.parent_path();
       binaryFile /= path("Output.bin");
       
       if (exists(binaryFile))
           remove(binaryFile);

       auto_ptr<IStoreFolder> sf;
       if (vm.count("extension_filter"))
           sf.reset(new StoreFolder(folder_path, binaryFile, parseExtensionFilter(vm["extension_filter"].as<string>()), depth));
       else
           sf.reset(new StoreFolderNoFilterWithDepth(folder_path, binaryFile, depth));

       if (!sf->good())
       {
          cout << sf->getError() << endl;
          return 1;
       }

       if (vm.count("compress")) 
       {
           path tmpFile(binaryFile);
           tmpFile += ".tmp";
           if (exists(tmpFile))
              remove(tmpFile);

           BurrowsWheelerFile().encode(binaryFile, tmpFile);

           remove(binaryFile);
           rename(tmpFile, binaryFile);
       }
   }                                                                    
   catch(std::exception& e)
   {
       cout << e.what() << endl;
       return 1;
   }
   return 0;
}
