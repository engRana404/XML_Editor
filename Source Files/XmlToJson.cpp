#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "XmlToTree.h"
using namespace std;

// convert from this form <user> to this "user":
string getString(string r)
{
	r = r.substr(1, r.length() - 2);
	r = "\"" + r + "\":";
	return r;
}

//convert xml to json vector 
void xmlToJson(Node* root, vector <string>& json)
{    
	stack <string> brackets;                    // stack to keep track of brackts
	stack <int> num_of_children;               // stack to keep track of no. of childern
	vector <Node*> x = Traversal(root);  // x is vector of all nodes in the tree
	bool u=true;
	for (int i = 0; i < x.size(); i++)
	{
		if (i == 0) // root of tree
		{
			json.push_back("{");
			json.push_back("\n"); 
		}
		//node with more than child with diffrent tag names
		if (x[i]->get_children().size() > 1 && diffChildern(x[i])) {
			if (u==false || i==0) {
				json.push_back(getString(x[i]->get_name()));
			}
			json.push_back("{");
			json.push_back("\n");
			//json.push_back(getString(x[i]->getchildren()[0]->get_name()));
			brackets.push("}");
		}
		//node with more than child with same tag name
		if (x[i]->get_children().size() > 1) {

			if (!diffChildern(x[i]))
			{

				json.push_back(getString(x[i]->get_name()));

				json.push_back("{");
				json.push_back("\n");

				brackets.push("}");
				json.push_back(getString(x[i]->get_children()[0]->get_name()));

				json.push_back("[");
				json.push_back("\n");

				brackets.push("]");
				u == false;

			}
		}
		//node with one child
		if (x[i]->get_children().size() == 1) {
			
			if (!(x[i]->get_name() == "<follower>") )
			{
				json.push_back(getString(x[i]->get_name()));
			}

			json.push_back("{");
			json.push_back("\n");
			if (!(x[i]->get_name() == "<follower>"))
			{
				json.push_back(getString(x[i]->get_children()[0]->get_name()));
			}
			brackets.push("}");


		}
		
		if (x[i]->get_children().size() > 0)
		{
			// root of tree
			if (i == 0) {
				num_of_children.push(x[i]->get_children().size());
			}
			//put current node childern number and decrease previous node childern by 1
			if (i != 0) {
				int z = num_of_children.top() - 1;
				num_of_children.pop();
				num_of_children.push(z);
				num_of_children.push(x[i]->get_children().size());

			}
		}

		if (x[i]->get_children().size() == 0)

		{
			if ((x[i]->get_name()) != "<topic>" && (json[json.size() - 1] != getString(x[i]->get_name()))) 
			{
					json.push_back(getString(x[i]->get_name()));
		        }

			json.push_back(x[i]->get_data());


			//pop top bracket when all childern are finished
			int z = num_of_children.top() - 1;
			if (z == 0) {
				string j = brackets.top();
				json.push_back("\n");
				json.push_back(brackets.top());
				json.push_back("\n");
				brackets.pop();
				if (j == "]") {
					json.push_back(brackets.top());
					json.push_back("\n");
					brackets.pop();
				}
			}
			else {

				json.push_back(",");
				json.push_back("\n");

			}
			num_of_children.pop();
			num_of_children.push(z);
			//loop to check all nodes with finished childern to pop their brackets
			for (int n = 0; n < num_of_children.size(); n++) {

				if (num_of_children.top() == 0) {

					num_of_children.pop();
					if (num_of_children.size() != 0) {
						int x = num_of_children.top();

						if (num_of_children.top() == 0) {

							string b = brackets.top();
							json.push_back(brackets.top());
							brackets.pop();
							json.push_back(",");
							json.push_back("\n");

							if (b == "]") {

								json.push_back(brackets.top());
								//json.push_back(",");
								json.push_back("\n");
								brackets.pop();
							}
						}
					}
				}
			}
		}
	}
	while (!brackets.empty()) {
		json.push_back(brackets.top());
		json.push_back("\n");

		brackets.pop();
	}

	json.push_back("}");
	json.push_back("\n");

}
    //convert json vector to json string
string VectorToString(vector <string> x)
{
	string s;
	int z = 0;
	for (int i = 0; i < x.size(); i++)
	{
		s = s + x[i];
		if (x[i] == "{" || x[i] == "[") z++; 
		if(i<x.size()-1)
		if (x[i+1] == "}" || x[i+1] == "]") z--;
		if (x[i] == "\n") {
			for (int n = 1; n<= z; n++)
			{
				s = s + "  "; 
			}
		}
	}
	return s;
}
