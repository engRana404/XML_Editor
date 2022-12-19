#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "XmlToTree.h"
using namespace std;

string getString(string r);
bool diffChildern(Node* node);
void xmlToJson(Node* root, vector <string>& json);
string VectorToString(vector <string> x);
