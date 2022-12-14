#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;
//Function that reads all text in a file (inputFile) and put it in a vector of strings (words) and returns the number of words (i)
bool isNumber(const string& s)
{
   	string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
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

vector<string> CorrectErrors(vector<string> XmlVector){
    vector<string> result=XmlVector;
    stack <string> tag;
    stack <int> Lnum;
    for(long long i=0;i<XmlVector.size();i++){
        string line =XmlVector[i];
        if(line[0]=='<'){
            //pushing closing into tag stack
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
                            if(isNumber(result[i-1])){
                               result[i]="</"+tag.top();
                               tag.pop();
                               Lnum.pop();
                               //result[Lnum.top()]="<"+tag.top();
                            }
                            else{
                                string old=result[i];
                                result[i]="</"+tag.top();
                                result.resize(result.size()+1);
                                result.push_back(line) ;
                            }
                        }
                    }
            else{
                    //closing without opening tag
                    if(isNumber(result[i+1])){
                        result[Lnum.top()]="<"+tag.top();
                        tag.pop();
                        Lnum.pop();
                    }
                }
            }
        }
    }
    return result;
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
    vector<string> XMLvector=convert2vector(xml);

    for(int i = 0; i < XMLvector.size(); i++)
        cout << XMLvector[i];
    XMLvector=CorrectErrors(XMLvector);
    cout<<endl;
    for(int i = 0; i < XMLvector.size(); i++)
        cout << XMLvector[i];

return 0;
}
