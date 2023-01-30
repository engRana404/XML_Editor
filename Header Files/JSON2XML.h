#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Formatting.h"

using namespace std;

std::string GetPropName(const std::string& line);
std::string GetPropValue(const std::string& line);
std::vector<std::string> saveLines(std::string text);
string JSON2XML(string json);
