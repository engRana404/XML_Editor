#include "JSON_Formatter.h" 

string json_formatter(string input)
{
	//ifstream fin;
	string json = "";
	int tabs, tokens; //here tokens are  { } , :
	tokens = -1;
	char ch;
	//fin.open(file_path.c_str());
	for(int i = 0; i < input.size(); i++)
	{
			if (input[i] == '{')
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
			else if (input[i] == ':')
			{
				json += " : ";
			}
			else if (input[i] == ',')
			{
				json += ",\n";
				tabs = tokens + 1;
				while (tabs)
				{
					json += "\t";
					tabs--;
				}
			}
			else if (input[i] == '}')
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
				if (input[i] == '\n' || input[i] == '\t')
					continue;
				else
					json += input[i];
			}
		}
	}
	return json;
}