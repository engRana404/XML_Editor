#include "Extra.h"

using namespace std;

int readWords(vector <string> &words, ifstream &inputFile, string &S)
{
    int i = 0;
    string S2;

    while (!inputFile.eof())
    {
        inputFile >> words[i];
        S2 += words[i] + " ";
    }

    S = removeSpaces(S2);

    return i;
}

void removeEndTags(vector<string> &XMLvector)
{
    vector<string>::iterator itr;

    for(int i = 0; i < XMLvector.size(); i++)
    {
        itr = XMLvector.begin() + i;

        if(XMLvector[i].length() >= 1)
            if(XMLvector[i].at(0) == '<' && XMLvector[i].at(1) == '/')
            {
                XMLvector.erase(itr);
                i--;
        }
    }
}

void writeToFile_int(string fileName, vector<int> intVector)
{
    ofstream Output;

    Output.open(fileName);

    if(!Output) //File could not be opened
    {
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    for(int i = 0; i < intVector.size(); i++)
        Output << intVector[i];

    Output.close();
}

void writeToFile_string(string fileName, vector<string> stringVector)
{
    ofstream Output;

    Output.open(fileName);

    if(!Output) //File could not be opened
    {
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    for(int i = 0; i < stringVector.size(); i++)
        Output << stringVector[i];

    Output.close();
}
