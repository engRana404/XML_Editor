#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Function to convert XML to CSV 
void xml_to_csv(string filename)
{

    // Create an input filestream object 
    ifstream in(filename);

    // Vector to store data 
    vector<vector<string> > data;

    // Temporary string to store data 
    string line;

    // Read file line by line 
    while (getline(in, line)) {

        // Vector to store row of data from each line of the file.  
        vector<string> vec;

        // Create a stringstream of the current line.  
        stringstream ss(line);

        // Read each word seperated by comma and store in a vector.  
        while (ss.good()) {

            string substr;

            getline(ss, substr, ',');

            vec.push_back(substr);

        }

        // Store the row in the main vector.  
        data.push_back(vec);

    }

    // Create an output filestream object.  
    ofstream out("output.csv");

    for (int i = 0; i < data.size(); i++) {

        for (int j = 0; j < data[i].size(); j++) {

            out << data[i][j] << ",";

        }

        out << "\n";

    }                                                                                                                                               out.close();      cout << "XML converted to CSV successfully!" << endl;      return;
} int main() { xml_to_csv("C:/Users/DELL 3550/Documents/ENG.Rana/Senior 1/Data structure/sample.xml");      return 0; }


