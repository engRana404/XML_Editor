#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

string getString(string r);

bool findChar(char charToFind, string input);

void removeEndTags(std::vector<std::string> &XMLvector);

void writeToFile_int(std::string fileName, std::vector<int> intVector);

void writeToFile_string(std::string fileName, std::vector<std::string> stringVector);
