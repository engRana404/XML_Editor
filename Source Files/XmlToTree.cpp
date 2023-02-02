#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "XmlToTree.h"
using namespace std;

//For Node class
Node::Node() 
{

}

Node::Node(string name, string data)
{
    this->name = name;
    this->data = data;
}

string Node::get_name()
{
    return name;
}

void Node::set_name(string node_name)
{
    this->name = node_name;
}

string Node::get_data()
{
    return data;
}

void Node::set_data(string data)
{
    this->data = data;
}

void Node::add_child(Node* child)
{
    children.push_back(child);
}

Node* Node::pop_child()
{
    Node* child = children.back();
    children.pop_back();
    return child;
}

vector<Node*> Node::get_children() {
    return children;
}

void Node::addchild2Node(Node* child, int& level) {
    this->children.push_back(child);
    level++;
    return;
}

void Node::addchild(Node* node, Node* child) {
    Node* Child;
    node->get_children().push_back(Child);
    int static level = 0;
    node->addchild2Node(child, level);
}

Node::~Node()
{

}

// For Tree class
Node Tree::getroot() {
    return root;
}

//check if a node has same type of childern or not
bool diffChildern(Node* node) {
    return (node->get_children()[0]->get_name() != node->get_children()[1]->get_name());
}

//the function that transfer the xml file to tree of nodes of parents and childs with recursion
void xml2tree(Node* node, vector <string> xml, int& i, Node* root) {         
    for (; i < xml.size(); i++)
    {
        //if the string hasn't open tag, store the data of the next node
        if (xml[i].at(0) != '<') 
        {
            node->set_data(xml[i]);
            i++;
            return;
        }
        else if (xml[i].at(1) == '/')  //base case when we have a closedtag
        {
            return;
        }       
        else 
        {
            Node* child = new Node(xml[i], " ");
            // if it is Not the first time
            if (root->get_children().size() > 0 && xml[i] == root->get_children()[0]->get_name())
            {
                root->addchild(root, child);
                i++;
            }
            //else put this data in a child
            else
            {
                node->addchild(node, child);
                i++;
            }
            xml2tree(child, xml, i, root);
        }
    }
}

vector <Node*> Traversal(Node* root)                     
{
    stack <Node*> Stack;
    stack <string> brackets;
    //contains all the visited nodes
    vector < Node* > depth;
    Stack.push(root);

    while (!Stack.empty()) {
        Node* temp = Stack.top();
        Stack.pop();
        // store the key in preorder vector(visited list)
        int maxSize;
        depth.push_back(temp);
        // Push all of the child nodes of temp into the stack from right to left.
        for (int i = (temp->get_children()).size() - 1; i >= 0; i--) {
            Stack.push((temp->get_children())[i]);
        }
    }
    return depth;
}
