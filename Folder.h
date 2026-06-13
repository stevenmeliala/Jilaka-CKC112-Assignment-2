#ifndef FOLDER_H
#define FOLDER_H

#include "File.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Folder {
private:
  string name;
  Folder *parent;
  vector<File> files;
  vector<Folder *> subfolders;

public:
  Folder() {
    name = "";
    parent = nullptr;
  }

  Folder(string n) {
    name = n;
    parent = nullptr;
  }

  Folder(string n, Folder *p) {
    name = n;
    parent = p;
  }

  void setName(string n) { name = n; }
  string getName() { return name; }
  void setParent(Folder *p) { parent = p; }
  Folder *getParent() { return parent; }
  vector<Folder *> &getSubfolders() { return subfolders; }

  void addFile(File temp);
  Folder *addSubfolder(string n);
  void addSubfolder(Folder *newFolder);
  void deleteFile(string);
  void deleteFolder(string);
  string getPath();
  void printFiles();
  void printFolders();
  void displayCurrentFolder();
  void displayTree(int level);
  File *searchFile(string fileName);
  bool folderExists(string folderName);
  bool fileExists(File f);
  ~Folder();
};
#endif