#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//function that reads all text in a file and put it in a string and returns the number of words
int read_words(vector<string>& words, ifstream& in,string&s)
{
    int i = 0;
    while (!in.eof()) {
        in >> words[i];
        s += words[i]+" ";
        i++;
    }
    return i - 1;
}

int main()
{
    ifstream ifp("C:\\Users\\Win10\\Desktop\\senoir 1\\sample.xml");

    vector<string> w(500);
    string xml;
    int number_of_words = read_words(w, ifp,xml);
    w.resize(number_of_words);
    cout << xml;
 }
