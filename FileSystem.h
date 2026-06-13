#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Folder.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class FileSystem {
private:
  Folder root;
  Folder *currentFolder;

public:
  FileSystem();
  string getroot;

  void createFile();
  void deleteFile();
  void createFolder();
  void deleteFolder();
  void searchFolder();
  void showCurrentPath();
  void loadFileSystem();
  void mainMenu();
};

#endif