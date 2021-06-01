#include "input.h"


Input::Input(HasmData* hd) {
  hasmData = hd;
}


Input::~Input() {}


void Input::readFiles() {
  for (auto filename : hasmData->getFilenames()) {
    readFile(filename);
  }
}


void Input::readFile(std::string filename) {
  std::string line;
  std::vector<std::string> source;
  std::fstream infile(filename);

  if (!infile.is_open()) {
    throw HasmException("file not found: " + filename);
  }

  while(std::getline(infile, line)) {
    source.push_back(line);
  }

  infile.close();
  hasmData->addSource(source);
}


