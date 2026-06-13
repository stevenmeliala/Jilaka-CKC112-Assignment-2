#ifndef FILE_H
#define FILE_H

#include <iostream>
using namespace std;

class File {
private:
  string name;
  string extension;

public:
  // constructor
  File(string n, string ext);
  // setters & getters
  void setName(string n);
  void setExtension(string ext);
  string getName() { return name; }
  string getExtension() { return extension; }
  string getFullFileName();
};
#endif