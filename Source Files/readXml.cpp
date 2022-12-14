#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Function that reads all text in a file (inputFile) and put it in a string (S) using the vector (words) and returns the number of words (i)
int readWords(vector <string> &words, ifstream &inputFile, string &S)
{
    int i = 0;

    while (!inputFile.eof())
    {
        inputFile >> words[i];
        S += words[i] + " ";
    }

    return i;
}

int main()
{
    string XMLpath;

    cout << "Enter the File's Path:" << endl;
    cin >> XMLpath;

    ifstream XMLfile(XMLpath);

    vector <string> XMLvector(500);

    string XML;     //The string variable where the XML contents will be concatenated into

    int wordsNumber = readWords(XMLvector, XMLfile, XML);

    XMLvector.resize(wordsNumber);

    cout << XML;
 }
