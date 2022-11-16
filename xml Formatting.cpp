// XML Editor.cpp : Formatting Function

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

string formatting(string xmlFile)
{
    string formeted_XML;
    int size = xmlFile.length();
    int parent = 0;
    int newlineFlag = 0;
    int removingNewlinesFlag = 0;

    for (int i = 0; i < size; i++)
    {
        if (xmlFile[i] == NULL)
        {
            continue;
        }
        else if (xmlFile[i] == '<' && xmlFile[i + 1] != '/')
        {
            formeted_XML = formeted_XML + xmlFile[i];
            parent++;
            newlineFlag = 0;
        }
        else if (xmlFile[i] == '<' && xmlFile[i + 1] == '/')
        {
            parent--;
            formeted_XML = formeted_XML + "\n";
            for (int j = 0; j < parent; j++)
            {
                formeted_XML += "   ";
            }
            formeted_XML = formeted_XML + xmlFile[i];
            newlineFlag = 1;
        }
        else if (xmlFile[i] == '>')
        {
            //formeted_XML = formeted_XML + xmlFile[i] + "\n";
            if (!(xmlFile[i + 1] == '<' && xmlFile[i + 2] == '/'))
            {
                formeted_XML = formeted_XML + xmlFile[i] + "\n";
            }
            else
            {
                formeted_XML = formeted_XML + xmlFile[i];
            }
            
            for (int j = 0; j < parent; j++)
            {
                formeted_XML += "   ";
            }
        }
        else if(!(xmlFile[i - 1] == '>' && (xmlFile[i] == ' ' || xmlFile[i] == '\n' || xmlFile[i] == '\t')))
        {     
            formeted_XML = formeted_XML + xmlFile[i];
        }
        else
        {
            continue;
        }
    }
    return formeted_XML;
}

int read_words(vector<string>& words, ifstream& in, string& s)
{
    int i = 0;
    while (!in.eof()) {
        in >> words[i];
        s += words[i] + " ";
        i++;
    }
    return i - 1;
}

int main()
{
    ifstream ifp("C:/Users/DELL 3550/Downloads/sample.xml");
    vector<string> w(500);
    string xml;
    int number_of_words = read_words(w, ifp, xml);
    w.resize(number_of_words);
    cout << formatting(xml);
}