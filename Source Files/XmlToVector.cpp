using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


/*
We want to remove spaces from start and end of the line only but not the spaces inside the line;
*/
string removeSpaces(string line){
    //The line without spaces.
    string result_line = "";

    //Start of the line
    int start = 0;
    //End of the line
    int end = line.length() - 1;

    while(line[start] == ' ' || line[start] == '\n' || line[start] == '\t'){
        //Skip spaces in the start of the line
        start++;
    }

    while(line[end] == ' ' || line[end] == '\n' || line[end] == '\t') {
       //Skip spaces in the end of the line
        end--;
    }

    for(int i = start ; i <= end; i++){
       //Add only the part without the start and end lines
        result_line += line[i];
    }

    return result_line;
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

int main()
{

    string xml = "<root>        <name>john</name>        <loc>brazil</loc>       <age>95 </age >        </entry>        <entry>       <foo>charles</foo>";
    vector<string> xmlVector;
    xmlVector = convert2vector(xml);
    cout << xmlVector[1];


    return 0;
}

