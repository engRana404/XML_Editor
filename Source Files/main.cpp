#include <iosktream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
//Function that reads all text in a file (inputFile) and put it in a vector of strings (words) and returns the number of words (i)
long long readWords(vector <string> &words, ifstream &inputFile)
{
    long long i = 0;

    while (!inputFile.eof())
    {
        inputFile >> words[i];
        i++;
    }

    return i;
}
vector<string> CorrectErrors(vector<string> XmlVector){
    stack <string> tag;
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
            }

            //closing tag--W/WO opening
            else if(line[1]=='/'){
                if(!tag.empty()){
                        if (line == ("</" + tag.top())) {
                            //closing with opening
                            tag.pop();
                        }
                        else {
                            //tag mismatch
                            tag.pop();
                            XmlVector.erase(i);
                        }
                    }
                else{
                    //closing without opening tag

                }
            }
        }
    }
}

int main(){
    string XMLpath;

    ifstream XMLfile("C:/Users/oem/Desktop/DS_Project/sample.xml");

    vector <string> XMLvector(500);

    int wordsNumber = readWords(XMLvector, XMLfile);

    XMLvector.resize(wordsNumber);
    for(int i = 0; i < XMLvector.size(); i++)
        cout << XMLvector[i];
    CorrectErrors(XMLvector);
    cout<<endl;
    for(int i = 0; i < XMLvector.size(); i++)
        cout << XMLvector[i];

return 0;
}
