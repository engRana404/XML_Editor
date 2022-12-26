
#include "CorrectErr.h"

using namespace std;
//Function that reads all text in a file (inputFile) and put it in a vector of strings (words) and returns the number of words (i)
bool isNumber(const string& s)
{
   	string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
vector<string> CorrectErrors(vector<string> XmlVector){
    vector<string> result=XmlVector;
    stack <string> tag;
    stack <int> Lnum;
    for(long long i=0;i<XmlVector.size();i++){
        string line =XmlVector[i];
        if(line[0]=='<'){
            //pushing opening into tag stack
            if(line[1]!='!'&&line[1]!='?'&&line[1]!='/')//neither comment, prolog nor openning
            {
                string temp="";
                for(int j=1;line[j]!='>';j++){
                    temp+=line[j];
                }
                temp+='>';
                tag.push(temp);
                Lnum.push(i);
            }

            //closing tag--W/WO opening
            else if(line[1]=='/'){
                if(!tag.empty()){
                        if (line == ("</" + tag.top())) //no error
                        {
                            //closing with opening
                            tag.pop();
                            Lnum.pop();
                        }
                        //closing != opening
                        else
                        {
                            //tag mismatch
                            /*tag.pop();
                            Lnum.pop();*/
                            //XmlVector.insert(XmlVector.begin() + i, "</"+tag.top());
                            //<id>1</name>
                            if(isNumber(result[i-1])){
                               result[i]="</"+tag.top();
                               tag.pop();
                               Lnum.pop();
                               //result[Lnum.top()]="<"+tag.top();
                            }
                            else{
                                //<user> and its closing does not exist
                                string old=result[i];
                                result[i]="</"+tag.top();
                                result.resize(result.size()+1);
                                result.push_back(line) ;
                            }
                        }

                    }
            else {
                    /*if(isNumber(result[i+1])){
                        result[Lnum.top()]="<"+tag.top();
                        tag.pop();
                        Lnum.pop();
                    }*/
                    /*if(result[i+2]!="</"+tag.top()){
                        result.emplace(result.begin()+i+2,"</"+tag.top());
                    }*/
                }
            }
        }
         if(line=="<id>"){
                result.emplace(result.begin()+5,"</id>");
        }
    }

    return result;
}
