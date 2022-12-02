// XML Editor.cpp : Formatting Function

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Find a certain character in a string
bool findChar(char x, string y) {
    for (int i = 0; i < y.length() - 1; i++) {
        if (y[i] == x) {
            return 1;
        }
    }
    return 0;
}


string formatting(vector<string> xmlFile) 
{
    string formeted_XML;
    int parent = 0;

    for (int i = 0; i < xmlFile.size(); i++) 
    {
        if (xmlFile[i] == "")
        {
            continue;
        }
        else if(findChar('<', xmlFile[i]) && !findChar('/', xmlFile[i]))
        {
            for (int j = 0; j < parent; j++)
            {
                formeted_XML += "   ";
            }
            formeted_XML = formeted_XML + xmlFile[i] + "\n";
            parent++;
        }
        else if (findChar('<', xmlFile[i]) && findChar('/', xmlFile[i]))
        {
            parent--;
            for (int j = 0; j < parent; j++)
            {
                formeted_XML += "   ";
            }
            formeted_XML = formeted_XML + xmlFile[i] + "\n";
        }
        else
        {
            for (int j = 0; j < parent; j++)
            {
                formeted_XML += "   ";
            }
            formeted_XML = formeted_XML + xmlFile[i] + "\n";
        } 
    }
    return formeted_XML;
}

int main()
{
    vector <string> xml = { "<user>", "<name>", "<id>", "</id>", "< /name>" , "< /user>" };
    std::cout << formatting(xml);
}