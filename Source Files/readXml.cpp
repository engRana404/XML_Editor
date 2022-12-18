#include "readXml.h"

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
