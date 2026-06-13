#include "File.h"

File::File(string n, string ext) {
  name = n;
  extension = ext;
}

void File::setName(string n) { name = n; }
void File::setExtension(string ext) { extension = ext; }
string File::getFullFileName() { return (name + "." + extension); }
