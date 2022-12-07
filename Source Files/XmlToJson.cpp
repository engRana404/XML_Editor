#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

//check if a node has same type of childern or not
bool diffChildern(Node* node) {
	if (node->getchildren()[0]->gettagname() != node->getchildren()[1]->gettagname())
		return true;
	if (node->getchildren()[0]->gettagname() == node->getchildren()[1]->gettagname())
		return false;
}



//depth traversal of the xml tree
vector <Node*> depthTraversal(Node* root)
{
	stack <Node*> s;
	vector < Node* > allNodes;
	s.push(root);

	while (!s.empty()) {
		Node* node = s.top();
		s.pop();
		allNodes.push_back(node);
		// loop to put all childern of node into the stack from left to right
		for (int i = (node->getchildren()).size() - 1; i >= 0; i--) {
			s.push((node->getchildren())[i]);
		}
	}
	return allNodes; // vector of pointers to all nodes in the tree
}



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
	vector <Node*> x = depthTraversal(root);  // x is vector of all nodes in the tree

	for (int i = 0; i < x.size(); i++)
	{
		if (i == 0) // root of tree
		{
			json.push_back("{");
			json.push_back("\n");
		}
		//node with more than child with diffrent tag names
		if (x[i]->getchildren().size() > 1 && diffChildern(x[i])) {
			json.push_back("{");
			json.push_back("\n");
			json.push_back(getString(x[i]->getchildren()[0]->gettagname()));
			brackets.push("}");
		}
		//node with more than child with same tag name
		if (x[i]->getchildren().size() > 1) {

			if (!diffChildern(x[i]))
			{

				json.push_back(getString(x[i]->gettagname()));

				json.push_back("{");
				json.push_back("\n");

				brackets.push("}");
				json.push_back(getString(x[i]->getchildren()[0]->gettagname()));

				json.push_back("[");
				json.push_back("\n");

				brackets.push("]");


			}
		}
		//node with one child
		if (x[i]->getchildren().size() == 1) {
			if (!(x[i]->gettagname() == "<follower>"))
			{
				json.push_back(getString(x[i]->gettagname()));
			}

			json.push_back("{");
			json.push_back("\n");
			json.push_back(getString(x[i]->getchildren()[0]->gettagname()));
			brackets.push("}");


		}
		
		if (x[i]->getchildren().size() > 0)
		{
			// root of tree
			if (i == 0) {
				num_of_children.push(x[i]->getchildren().size());
			}
			//put current node childern number and decrease previous node childern by 1
			if (i != 0) {
				int z = num_of_children.top() - 1;
				num_of_children.pop();
				num_of_children.push(z);
				num_of_children.push(x[i]->getchildren().size());

			}
		}

		if (x[i]->getchildren().size() == 0)

		{
			if ((x[i]->gettagname()) == "<name>") {
				json.push_back(getString(x[i]->gettagname()));
			}

			json.push_back(x[i]->getdata());


			//pop top bracket when all childern are finished
			int z = num_of_children.top() - 1;
			if (z == 0) {
				string j = brackets.top();
				//json.push_back("\n");
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
					int x = num_of_children.top();

					if (num_of_children.top() == 0) {

						string b = brackets.top();
						json.push_back(brackets.top());
						brackets.pop();
						json.push_back(",");
						json.push_back("\n");

						if (b == "]") {

							json.push_back(brackets.top());
							json.push_back("\n");
							brackets.pop();
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
	for (int i = 0; i < x.size(); i++)
	{
           s = s + x[i];
	}
	return s;
}
