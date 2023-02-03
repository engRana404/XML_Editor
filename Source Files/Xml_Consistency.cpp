#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include "readXml.h"
#include "XmlToVector.h"
using namespace std;
/*
*Input: string vector of XML
*brief description:
    This function returns false in case of missing closing, opening tags or mismatched tags. 
    First, it iterates XML file line by line and pushes opening tags to stack if there is no comment or prolog. 
    Second, it checks closing tags to detect mismatched tags by comparing each closing and top of opening tags 
    if they match then pop from the stack else returns false, to detect closing without opening. In the end, 
    if the stack is empty,  it will return true
*/
//IsConsistent function returns false in case of missing closing or opening tags or mismatching tags
bool IsConsistent(vector<string> xmlFile){
    stack<string> tag;
    //iterating on XML file line by line
     for (int i = 0; i < xmlFile.size(); i++){
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
    }
    return (tag.empty());
}
