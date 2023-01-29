#include "Compression.h"

using namespace std;

vector<int> CompressXML(string Path)       //Takes the path of the file needed to be compressed and returns a vector of integers representing the compression sequence
{
    ifstream XMLfile(Path);

    vector<string> XMLstring(1);

    string s1;     //The string variable where the XML contents will be concatenated into

    readWords(XMLstring, XMLfile, s1);

    unordered_map<string, int> codeTable;

    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        codeTable[ch] = i;
    }

    string p = "", c = "";

    p += s1[0];

    int code = 256;

    vector<int> outputCode;

    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (codeTable.find(p + c) != codeTable.end()) {
            p = p + c;
        }
        else {
            outputCode.push_back(codeTable[p]);
            codeTable[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }

    outputCode.push_back(codeTable[p]);

    return outputCode;
}

vector<string> DecompressXML(vector<int> op)
{
    string out = "";

    unordered_map<int, string> codeTable;

    for (int i = 0; i <= 255; i++)
    {
        string ch = "";
        ch += char(i);
        codeTable[i] = ch;
    }

    int old = op[0], n;

    string s = codeTable[old];

    string c = "";

    c += s[0];

    string sss = s;

    int count = 256;

    for (int i = 0; i < op.size() - 1 ; i++)
    {
        n = op[i + 1];

        if (codeTable.find(n) == codeTable.end())
        {
            s = codeTable[old];
            s = s + c;
        }

        else
            s = codeTable[n];

        out += s;

        c = "";

        c += s[0];

        codeTable[count] = codeTable[old] + c;

        count++;

        old = n;
    }

    string ff = sss + out;

    vector<string> xmlVector = convert2vector(ff);

    return xmlVector;
}
