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

/*
This function corrects the formatting of the XML file

e.g.
input      -------->   output
<user>                  <user>
<name>                      <name>
<id>                            <id>
</id>                           </id>
</name>                     </name>
</user>                 </user>

*/

//if the input is vector of strings
string formatting(vector<string> xmlFile)
{
    string formeted_XML; //store the formeted xml file
    int parent = 0; //count the number of perants

    //loop on the file
    for (int i = 0; i < xmlFile.size(); i++)
    {
        //if the element is empty continue
        if (xmlFile[i] == "")
        {
            continue;
        }
        /*
            if open tags
            <--->
        */
        else if (findChar('<', xmlFile[i]) && !findChar('/', xmlFile[i]))
        {
            //print the required tabs before the parent
            for (int j = 0; j < parent; j++)
            {
                formeted_XML += "   ";
            }
            //print new line after the element
            formeted_XML = formeted_XML + xmlFile[i] + "\n";
            // increase the number of parents 
            parent++; 
        }
        /*
            if closed tags
            </--->
        */
        else if (findChar('<', xmlFile[i]) && findChar('/', xmlFile[i]))
        {
            // decrease the number of parents
            parent--;
            //print the required tabs before it
            for (int j = 0; j < parent; j++)
            {
                formeted_XML += "   ";
            }
            //print new line after the element
            formeted_XML = formeted_XML + xmlFile[i] + "\n";
        }
        // if any thing else comment or the first line in the xml or the any sentence
        else
        {
            //print the required tabs before the element
            for (int j = 0; j < parent; j++)
            {
                formeted_XML += "   ";
            }
            //print new line after the element
            formeted_XML = formeted_XML + xmlFile[i] + "\n";
        }
    }
    return formeted_XML;
}

//if the input is string
string formatting2(string xmlFile)
{
    string formeted_XML; //store the formeted xml file
    int size = xmlFile.length(); // store the size of the input xml
    int parent = 0; //count the number of perants
    //flags to control the number of new lines
    int newlineFlag = 0; 
    int removingNewlinesFlag = 0;

    for (int i = 0; i < size; i++)
    {
        //if the element is empty continue
        if (xmlFile[i] == NULL)
        {
            continue;
        }
        /*
            if open tags
            <--->
        */
        else if (xmlFile[i] == '<' && xmlFile[i + 1] != '/')
        {
            formeted_XML = formeted_XML + xmlFile[i];
            // increase the number of parents 
            parent++;
            //set the new line flag to zero
            newlineFlag = 0;
        }
        /*
            if closed tags
            </--->
        */
        else if (xmlFile[i] == '<' && xmlFile[i + 1] == '/')
        {
            // decrease the number of parents
            parent--;
            //print new line after the element
            formeted_XML = formeted_XML + "\n";
            //print the required tabs before the element
            for (int j = 0; j < parent; j++)
            {
                formeted_XML += "   ";
            }
            formeted_XML = formeted_XML + xmlFile[i];
            //set the new line flag to one
            newlineFlag = 1;
        }
        else if (xmlFile[i] == '>')
        {
            if (!(xmlFile[i + 1] == '<' && xmlFile[i + 2] == '/'))
            {
                //print new line after the element
                formeted_XML = formeted_XML + xmlFile[i] + "\n";
            }
            else
            {
                formeted_XML = formeted_XML + xmlFile[i];
            }
            //print the required tabs before the element
            for (int j = 0; j < parent; j++)
            {
                formeted_XML += "   ";
            }
        }
        // if any thing else comment or the first line in the xml or the any sentence
        else if (!(xmlFile[i - 1] == '>' && (xmlFile[i] == ' ' || xmlFile[i] == '\n' || xmlFile[i] == '\t')))
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