#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#pragma once

void removeEndTags(std::vector<std::string> &XMLvector);

void writeToFile_int(std::string fileName, std::vector<int> intVector);

void writeToFile_string(std::string fileName, std::vector<std::string> stringVector);
