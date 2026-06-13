#include "Folder.h"
#include <iostream>

using namespace std;

void Folder::addFile(File temp) { files.push_back(temp); }

Folder *Folder::addSubfolder(string n) {
  Folder *newFolder = new Folder(n, this);
  subfolders.push_back(newFolder);
  return newFolder;
}

void Folder::addSubfolder(Folder *newFolder) {
  subfolders.push_back(newFolder);
}

void Folder::printFiles() {
  if (files.empty()) {
    cout << "No files" << endl;
    return;
  }

  for (int i = 0; i < files.size(); i++) {
    cout << files[i].getFullFileName() << endl;
  }
}

// Displays only folders directly inside the current folder.
// This function is not recursive.
void Folder::printFolders() {
  if (subfolders.empty()) {
    cout << "No folders" << endl;
    return;
  }

  for (int i = 0; i < subfolders.size(); i++) {
    cout << subfolders[i]->getName() << endl;
  }
}

// Displays the current folder's direct contents only.
// It does not go inside subfolders.
void Folder::displayCurrentFolder() {
  cout << "Current folder: " << name << endl;

  cout << "\nFiles:" << endl;
  printFiles();

  cout << "\nFolders:" << endl;
  printFolders();
}

string Folder::getPath() {
  if (parent == nullptr) {
    return name;
  }
  return parent->getPath() + "/" + name;
}

void Folder::displayTree(int level) {
  for (int i = 0; i < level; i++) {
    cout << "    ";
  }

  if (level == 0) {
    cout << name << endl;
  } else {
    cout << "|-- " << name << endl;
  }

  // Print files inside the current folder.
  for (int i = 0; i < files.size(); i++) {
    for (int j = 0; j < level + 1; j++) {
      cout << "    ";
    }

    cout << "|-- " << files[i].getFullFileName() << endl;
  }

  // Recursive step:
  // Ask each child folder to display its own tree.
  for (int i = 0; i < subfolders.size(); i++) {
    subfolders[i]->displayTree(level + 1);
  }
}

// Student 1: recursive file search.
// Returns the file address if found, otherwise returns nullptr.
File *Folder::searchFile(string fileName) {
  // First search files directly inside this folder.
  for (int i = 0; i < files.size(); i++) {
    if (files[i].getFullFileName() == fileName ||
        files[i].getName() == fileName) {
      return &files[i];
    }
  }

  // Recursive step:
  // If the file is not here, search inside each subfolder.
  for (int i = 0; i < subfolders.size(); i++) {
    File *foundFile = subfolders[i]->searchFile(fileName);

    if (foundFile != nullptr) {
      return foundFile;
    }
  }

  return nullptr;
}
bool Folder::folderExists(string folderName) {
  for (int i = 0; i < subfolders.size(); i++) {
    if (subfolders[i]->getName() == folderName) {
      return true;
    }
  }
  return false;
}

bool Folder::fileExists(File f) {
  for (int i = 0; i < files.size(); i++) {
    if (files[i].getFullFileName() == f.getFullFileName()) {
      return true;
    }
  }
  return false;
}

void Folder::deleteFile(string fileName) {
  // Search files in the current folder
  for (int i = 0; i < files.size(); i++) {
    if (files[i].getFullFileName() == fileName) {
      files.erase(files.begin() + i);
      cout << "File deleted successfully.\n";
      return;
    }
  }
  // Search recursively in subfolders
  for (int i = 0; i < subfolders.size(); i++) {
    try {
      subfolders[i]->deleteFile(fileName);
      return; // file found and deleted
    } catch (const char *) {
      // Continue searching remaining subfolders
    }
  }
  // File not found anywhere
  throw "Error: File not found.";
}

void Folder::deleteFolder(string folderName) {
  // Search immediate subfolders
  for (int i = 0; i < subfolders.size(); i++) {
    if (subfolders[i]->getName() == folderName) {
      delete subfolders[i]; // invokes destructor
      subfolders.erase(subfolders.begin() + i);

      cout << "Folder deleted successfully.\n";
      return;
    }
  }

  // Search recursively inside subfolders
  for (int i = 0; i < subfolders.size(); i++) {
    try {
      subfolders[i]->deleteFolder(folderName);
      return; // folder found and deleted
    } catch (const char *) {
      // continue searching
    }
  }

  throw "Error: Folder not found.";
}

Folder::~Folder() {
  for (int i = 0; i < subfolders.size(); i++) {
    delete subfolders[i];
  }

  subfolders.clear();
}