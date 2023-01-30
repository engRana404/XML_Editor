#include "JSON2XML"

std::string GetPropName(const std::string& line)
{
    //Return the string up to the ':' and after the tab special characters (compare to line)
    std::string propName = line.substr(3, line.find(58) - 3);

    //Take off the final '\'
    if (propName != "")
        propName.pop_back();


    return propName;
}

std::string GetPropValue(const std::string& line)
{
    std::string value = line.substr(line.find(58), line.length() - 1);
    value = value.substr(2, line.length() - 2);

    if (value != "")
        value.pop_back();
    return value;
}

std::vector<std::string> saveLines(std::string text) {
    std::vector<std::string> lines;
    std::istringstream iss(text);
    std::string line;
    while( std::getline(iss, line) ) {
        lines.push_back(line);
    }
    return lines;
}


string JSON2XML(string json)
{
    string xmlFile;
    string rootElement = "users";
    vector<string> line = saveLines(json);

    string propName;
    string propValue;
    string beginTag;
    string endTag;
    string xmlValue;

    xmlFile = xmlFile + "<?xml version=\"1.0\"?>" + "\n";

    string beginRootTag = "<" + rootElement + ">";
    string endRootTag = "<\/" + rootElement + ">";

    xmlFile = xmlFile + beginRootTag + "\n";

    size_t pos = -1;
    bool insideJsonValue = false;
    for(int i = 0; i < line.size(); i++)
    {
       
        //cout << line[i] << "\n";
        if (line[i] == "\t{")
        {
            insideJsonValue = true;
        }

        if (line[i] == "\t},")
        {
            insideJsonValue = false;
        }

        if (insideJsonValue && line[i] != "\t{" && line[i] != "\t}" && line[i] != "]")
        {//this line is a json property

            propName = GetPropName(line[i]);
            propValue = GetPropValue(line[i]);
            beginTag = "<" + propName + ">";
            endTag = "<\/" + propName + ">";
            xmlValue = beginTag + propValue + endTag + "\n";

            xmlFile += xmlValue;
        }
    }

    xmlFile = xmlFile + endRootTag + "\n";
    xmlFile = formatting(xmlFile);
    return xmlFile;
}