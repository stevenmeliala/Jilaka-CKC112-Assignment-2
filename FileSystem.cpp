#include "FileSystem.h"
#include "File.h"
#include "Folder.h"
#include <iostream>

FileSystem::FileSystem() : root("Root"), getroot(root.getName()) {
  currentFolder = &root;
}

void FileSystem::createFile() {

  cout << "Enter the name of the file: ";
  string n, e;
  while (n == " " || n.length() == 0) {
    getline(cin, n);
  }
  cout << "Enter the file extension (example: txt, docx, etc.): ";
  while (e == " " || e.length() == 0) {
    cin >> e;
  }

  // Remove the leading dot if the user typed it (e.g. ".txt" -> "txt")
  if (e.length() > 0 && e[0] == '.') {
    e = e.substr(1);
  }

  File temp(n, e);
  currentFolder->addFile(temp);
  cout << "File created inside " << currentFolder->getName() << ".\n";
}

void FileSystem::createFolder() {
  cout << "Enter the name of the folder: ";
  string n;
  while (n == " " || n.length() == 0) {
    getline(cin, n);
  }
  currentFolder->addSubfolder(n);
}

void FileSystem::deleteFolder() {}
void FileSystem::deleteFile() {}
void FileSystem::searchFolder() {
  string folderName;
  cout << "Enter folder name to enter: ";
  cin >> folderName;
  try {
    if (folderName.empty())
      throw runtime_error("Error: Folder name cannot be empty.");
    if (!currentFolder->folderExists(folderName))
      throw runtime_error("Error: '" + folderName + "' not found.");

    Folder *target = nullptr;
    for (Folder *sub : currentFolder->getSubfolders()) {
      if (sub->getName() == folderName) {
        target = sub;
        break;
      }
    }
    currentFolder = target;
    cout << "Entered folder: " << currentFolder->getName() << endl;

  } catch (runtime_error e) {
    cout << e.what() << endl;
  }
}
void FileSystem::showCurrentPath() {}

void FileSystem::loadFileSystem() {
  ifstream sampleFiles("filesystem.txt");
  if (!sampleFiles) {
    cout << "Unable to load files\n";
    return;
  }
  string line;
  while (getline(sampleFiles, line)) {
    if (line.empty())
      continue;

    size_t spacePos = line.find(' ');
    if (spacePos == string::npos)
      continue;

    string type = line.substr(0, spacePos);
    string path = line.substr(spacePos + 1);

    // Parse the path into pieces
    vector<string> parts;
    size_t start = 0;
    size_t end = path.find('/');
    while (end != string::npos) {
      parts.push_back(path.substr(start, end - start));
      start = end + 1;
      end = path.find('/', start);
    }
    parts.push_back(path.substr(start));

    // Start traversing from the root
    // We skip parts[0] since it is always "Root"
    Folder *curr = &root;

    if (type == "FOLDER") {
      for (size_t i = 1; i < parts.size(); i++) {
        bool found = false;
        vector<Folder *> &subfolders = curr->getSubfolders();
        for (size_t j = 0; j < subfolders.size(); j++) {
          if (subfolders[j]->getName() == parts[i]) {
            curr = subfolders[j];
            found = true;
            break;
          }
        }
        // If the folder doesn't exist yet, create it
        if (!found) {
          Folder *newFolder = new Folder(parts[i]);
          newFolder->setParent(curr);
          curr->addSubfolder(newFolder);
          curr = newFolder;
        }
      }
    } else if (type == "FILE") {
      // Navigate to the correct parent folder first
      for (size_t i = 1; i < parts.size() - 1; i++) {
        bool found = false;
        vector<Folder *> &subfolders = curr->getSubfolders();
        for (size_t j = 0; j < subfolders.size(); j++) {
          if (subfolders[j]->getName() == parts[i]) {
            curr = subfolders[j];
            found = true;
            break;
          }
        }
        if (!found) {
          Folder *newFolder = new Folder(parts[i]);
          newFolder->setParent(curr);
          curr->addSubfolder(newFolder);
          curr = newFolder;
        }
      }

      // The last part is the file name with extension
      string fullFileName = parts.back();
      size_t dotPos = fullFileName.find('.');
      string name = fullFileName.substr(0, dotPos);
      string ext =
          (dotPos != string::npos) ? fullFileName.substr(dotPos + 1) : "";

      // Create the file and add it
      File temp(name, ext);
      curr->addFile(temp);
    }
  }
  cout << "File system loaded successfully!\n";
}

void FileSystem::mainMenu() {
  int option;
  do {
    cout << "1.  Create Folder\n";
    cout << "2.  Create File\n";
    cout << "3.  Display Current Folder\n";
    cout << "4.  Display Full Folder Tree\n";
    cout << "5.  Search File\n";
    cout << "6.  Enter Folder\n";
    cout << "7.  Go Back to Parent Folder\n";
    cout << "8.  Delete File\n";
    cout << "9.  Delete Folder\n";
    cout << "10. Show Current Path\n";
    cout << "11. Exit\n";
    cout << "Enter your option: ";
    cin >> option;
    switch (option) {
    case 1:
      createFolder();
      break;
    case 2:
      createFile();
      break;
    case 3:
      currentFolder->displayCurrentFolder();
      break;
    case 4:
      root.displayTree(0);
      break;
    case 5: {
      string n;
      cout << "Enter the file name to search: ";
      cin >> n;
      File *foundFile = root.searchFile(n);
      if (foundFile != nullptr) {
        cout << "File found: " << foundFile->getFullFileName() << "\n";
      } else {
        cout << "File not found.\n";
      }
      break;
    }
    case 6:
      searchFolder();
      break;
    case 7:
      // go back stub
      break;
    case 8:
      deleteFile();
      break;
    case 9:
      deleteFolder();
      break;
    case 10:
      showCurrentPath();
      break;
    case 11:
      cout << "Exiting...\n";
      break;
    default:
      cout << "Invalid option\n";
    }
  } while (option != 11);
}
