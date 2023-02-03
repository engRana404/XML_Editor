/*
*brief description: looping XML file to correct errors with 3 types: 
    1- mismatched tags corrected by making a closing that fits the opening tag
    2- closing tag without opening one corrected by removing it
    3- opening tag without closing tag corrected by adding it
*Input: string vector of XML
*output: return map that contains corrected error and line number of error
*/
#include "CorrectErr.h"
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
                            // tags mismatch --> make a closing tag that fits the opening one
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
                        // closing tag without opening tag    --->   remove it
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
