#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "XmlToTree.h"
using namespace std;

vector <vector <int>> FollowerList(vector <Node*> tree);
void RepresentinFile(vector<vector<int>> list);
vector <int> inDegree(vector <vector <int>> list);
vector <int> outDegree(vector <vector <int>> list);
int maxdegree(vector<int> degree);
