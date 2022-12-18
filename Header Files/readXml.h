#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#pragma once

std::string removeSpaces(std::string line);

int readWords(std::vector <std::string> &words, std::ifstream &inputFile, std::string &S);
