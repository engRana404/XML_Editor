#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
/*#include "XmlToTree.h"
#include "xml Formatting.h"
#include "XmlToVector.h"*/
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
/*
We want to remove spaces from start and end of the line only but not the spaces inside the line;
*/
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

vector<string> convert2vector(string xmlFile){
    vector <string> xmlVector;
    //Loop over the whole file
    for(int i=0; i<xmlFile.length();i++){
            string XmlTemp="";
            if(xmlFile[i]=='<'){
                while(xmlFile[i]!='>'){
                    //add characters of the wanted tag
                    XmlTemp+=xmlFile[i];
                    //Go to next char.
                    i++;
                    }//End of while == We have <word inside temp
                    //Add '>' to finish the tag
                    XmlTemp+='>';
                    i++;
                    //Clean line from unwanted spaces
                    XmlTemp= removeSpaces(XmlTemp);
                    //Push tag into vector
                    xmlVector.push_back(XmlTemp);
                    //Clean temp variable
                    XmlTemp= "";
                    } //End of if char is <
            //if it's not <
            else {
                    //continue;
                    while(xmlFile[i]!='<'){
                        //add characters of the wanted tag
                       if(xmlFile[i]!='\n'&& xmlFile[i]!='\t') XmlTemp+=xmlFile[i];
                        //Go to next char.
                        i++;

                    }
                    XmlTemp= removeSpaces(XmlTemp);
                    if(XmlTemp!=""){xmlVector.push_back(XmlTemp);}
                    XmlTemp="";



            }//End of else
            i--;


    }//End of whole file loop
    return xmlVector;
}

//IsConsistent function returns false in case of missing closing or opening tags or mismatching tags
bool IsConsistent(vector<string> xmlFile){
    stack<string> tag;
    //iterating on XML file line by line
    int i=0;
    while(i<xmlFile.size()){
        string line = xmlFile[i];

        if (line[0] == '<'){
            //pushing tags
            if(line[1] != '!' && line[1] != '?'&&line[1] != '/')//Not comment or prolog + not closing
            {
                if(!(line[line.length()-2] == '/' && line[line.length()-1] == '>')){
                        string temp = "";
                        for(int j=1; j<line.length(); j++){
                            if(line[j] != ' ' && line[j] != '>'){
                             temp += line[j];
                            }
                            else{
                                temp += '>';
                                break;
                            }
                        }
                        tag.push(temp);
                    }
            }
            //handling opening and closing tags
            else if(line[1] == '/')//checking for closing tags
            {
                    if(!tag.empty()){
                        if (line != ("</" + tag.top())) {
                            // tags mismatch
                            return false;
                        }
                        else {
                            tag.pop();
                        }
                    }
                    else{
                        //closing with no opening tag
                        return false;
                    }
            }
        }
        i++;
    }
    return (tag.empty());
}

int main(){
    ifstream ifp("C:/Users/oem/Desktop/DS_Project/sample.xml");
    vector<string> w(500);
    string xml;
    read_words(w, ifp, xml);

    //cout<<xml;
    /*vector<string> xmlFile=convert2vector(xml);
    for(int i = 0; i < xmlFile.size(); i++)
        cout << xmlFile[i] << ' ';*/
    cout<<IsConsistent(convert2vector(xml));

return 0;
}
