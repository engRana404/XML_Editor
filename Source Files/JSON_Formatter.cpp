#include <iostream>
#include <fstream>
#include <string>

using namespace std;


string json_tree(string file_path)
{
	ifstream fin;
	string json = "";
	int tabs, tokens; //here tokens are  { } , :
	tokens = -1;
	char ch;
	fin.open(file_path.c_str());
	if (!fin)
		cout << "Failed to open file";
	else
	{
		while (fin.get(ch))
		{

			if (ch == '{')
			{
				tokens++;

				//open braces tabs
				tabs = tokens;
				if (tokens > 0)
					json += "\n";
				while (tabs)
				{
					json += "\t";
					tabs--;
				}
				json = json + '{' + "\n";

				//json key:value tabs
				tabs = tokens + 1;
				while (tabs)
				{
					json += "\t";
					tabs--;
				}
			}
			else if (ch == ':')
			{
				json += " : ";
			}
			else if (ch == ',')
			{
				json += ",\n";
				tabs = tokens + 1;
				while (tabs)
				{
					json += "\t";
					tabs--;
				}
			}
			else if (ch == '}')
			{
				tabs = tokens;
				json += "\n";
				while (tabs)
				{
					json += "\t";
					tabs--;
				}

				json = json + '}' + "\n";
				tokens--;
				tabs = tokens + 1;

				while (tabs)
				{
					json += "\t";
					tabs--;
				}
			}
			else
			{
				if (ch == '\n' || ch == '\t')
					continue;
				else
					json += ch;
			}
		}
	}
	fin.close();
	return json;
}
