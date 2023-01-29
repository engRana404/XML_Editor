#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "readXml.h"
#include "XmlToVector.h"
using namespace std;
map<int, string> CorrectErr(vector<string> xml){
    map<int, string> result;
    stack<string> tag;
    stack<int> lineNum;
        int i = 0;
        for (i = 0; i < xml.size(); i++) {
            string l = xml[i];
            if (l[0] == '<') {
                if (l[1] == '/') {
                    if(!tag.empty()){
                        if (l != ("</" + tag.top())) {
                            // tags mismatch -> make a closing tag that fits the opening one
                            result[i] = "</" + tag.top();
                            tag.pop();
                            lineNum.pop();
                        }
                        else {
                            tag.pop();
                            lineNum.pop();
                        }
                    }
                    else{
                        // closing tag without opening tag    ->   remove it
                        result.erase(i);
                    }
                }
                else if(l[1] != '!' && l[1] != '?') {
                    if(!(l[l.length()-2] == '/' && l[l.length()-1] == '>')){
                        string tmp = "";
                        for(int j=1; j<l.length(); j++){
                            if(l[j] != ' ' && l[j] != '>'){
                             tmp += l[j];
                            }
                            else{
                                tmp += '>';
                                break;
                            }
                        }
                        tag.push(tmp);
                        lineNum.push(i);
                    }
                }
            }
            else{
                // no closing tag -> add it
                if(i+1 < xml.size()){
                    string closingTag = xml[i+1]; //must be closing tag
                    if(!(closingTag[0] == '<' && closingTag[1] == '/')){
                        if(!tag.empty()){
                            result[i] = "</" + tag.top();
                            tag.pop();
                            lineNum.pop();
                        }
                    }
                }
            }
        }
        return result;
}

