#include <iostream>
#include <string>
#include <vector>
#include "XmlToVector.h"
#include "XML_Minifier.h"
using namespace std;

/*
This function deletes any spaces and newlines (\n)
e.g.
input      -------->   output
<user>                 <user><name><id></id></name></user>
    <name>                      
        <id>                            
        </id>                           
    </name>                     
</user>                 
*/
string xml_minifier(string xml)
{
    //store the xml converted into vector of strings using the function coveret to vector in XmlToVector.h file
    vector<string> xmlVector = convert2vector(xml); 
    //store the formeted xml file
    string formeted_XML; 
    int size = xmlVector.size();
    for (int i = 0; i < size; i++)
    {
        formeted_XML += xmlVector[i];
    }
    return formeted_XML;
}
