#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/* 
We want to remove spaces from start and end of the line only but not the spaces inside the line; 
*/
string removeSpaces(string line){
    //The line without spaecs.
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
