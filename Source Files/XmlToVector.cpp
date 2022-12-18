#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "XmlToVector.h"

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
    xmlVector.resize(1);
    //Clean line from unwanted spaces
    xmlFile= removeSpaces(xmlFile);
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
