#include "Extras.h"

using namespace std;

// convert from this form <user> to this "user":
// convert from this form <user> to this "user":
string getString(string t1)
{
    t1.replace(0, 1, "\"");
    t1.replace(t1.length() - 1, 1, "\"");
    t1 = t1 + ":";
    return t1;
}
// Find a certain character in a string
bool findChar(char charToFind, string input) {
    for (int i = 0; i < input.length() - 1; i++) {
        if (input[i] == charToFind) {
            return 1;
        }
    }
    return 0;
}

void removeEndTags(vector<string> &XMLvector)   //Removes all end tags from a vector of strings having the XML file contents
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

void writeToFile_int(string fileName, vector<int> intVector)    //Takes the path of the file we will write into and takes the file input as a vector of integers
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

void writeToFile_string(string fileName, vector<string> stringVector)   //Takes the path of the file we will write into and takes the file input as a vector of strings
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
