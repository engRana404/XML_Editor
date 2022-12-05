#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Function that reads all text in a file (inputFile) and put it in a vector of strings (words) and returns the number of words (i)
int readWords(vector <string> &words, ifstream &inputFile)
{
    int i = 0;
    
    while (!inputFile.eof())
    {
        inputFile >> words[i];
        i++;
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

    int wordsNumber = readWords(XMLvector, XMLfile);

    XMLvector.resize(wordsNumber);

    for(int i = 0; i < XMLvector.size(); i++)
        cout << XMLvector[i];
 }
