This is a console tool for creating snapshot of folder's structure and vice versa.

1. MakeFolderSnapshot:

Input:
- path to desired directory
- Depth of exploring
- Extension filter

Output:
- Binary file with hierarchy structure of folders and files.

Allowed options:
  --help                           produce help message
  -f [ --folder_path ] arg         path to folder for making a snapshot
  -d [ --depth ] arg (=2147483647) depth of exploring
  -e [ --extension_filter ] arg    list of extensions separated by comma

Additional description:
- For each directory tool collects information about:
  o Number of nested folders
  o Number of nested files
  o Size in bytes (including all files and subfolders)
- For each file:
  o Size in bytes
  o Creation date & time
  o Content of the files, specified in extension filter


2. RestoreFolder.

Input:
- Generated binary file
- Destination folder

Output:
- Restored folder structure
- Restored files with content
- Additional text file with information about directory + list of files with information about them.

Allowed options:
  --help                   produce help message
  -b [ --binary_file ] arg path to generated binary file
  -d [ --dest_folder ] arg destination folder

For more information write to dendibakh@gmail.com