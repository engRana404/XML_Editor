#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "XmlToVector.h"

int readWords(std::vector <std::string> &words, std::ifstream &inputFile, std::string &S);

void removeEndTags(std::vector<std::string> &XMLvector);

void writeToFile_int(std::string fileName, std::vector<int> intVector);

void writeToFile_string(std::string fileName, std::vector<std::string> stringVector);
