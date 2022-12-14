#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string removeSpaces(string line){
    int start = 0;
    while(line[start] == ' ' || line[start] == '\t' || line[start] == '\n'){
        start += 1;
    }
    int end = line.length() - 1;
    while(line[end] == ' ' || line[end] == '\t' || line[end] == '\n') {
        end -= 1;
    }
    string result = "";
    for(int i = start ; i <= end; i++){
        result += line[i];
    }
    return result;
}

//Function that reads all text in a file (inputFile) and put it in a string (S) using the vector (words) and returns the number of words (i)
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
