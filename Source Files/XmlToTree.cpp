// XmlToTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include "XmlToTree.h"
#include <stack>
using namespace std;

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
    this->name = name;
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
Node::~Node()
{

}

void convert2tree(Node* root, vector<string> XML)
{
    stack<Node*> node_stack;
    stack<char> parentsCounter;
    node_stack.push(root);//pushing root as the first element
    int xmlTags = 0; // variable used for this tag <? ?>

    for (int i = 0; i < XML.size(); i++)
    {
        /*
           the first line
           <?   ?>
        */
        if (XML[i][0] == '<' && XML[i][1] == '?')
        {
            if (!xmlTags)//true in the first time
            {
                //put this data in the root
                node_stack.top()->set_data(XML[i]);
                xmlTags++;
            }
            // if it is Not the first time
            else
            {
                Node* temp = new Node("XML_TAG", XML[i]);//else put this data in a child
                node_stack.top()->add_child(temp);//make a child to the top element in the stack
            }
        }
        /*
         comment in xml
          <!-- comment  -->
        */
        else if (XML[i][0] == '<' && XML[i][1] == '!')
        {
            Node* temp = new Node("COMMENT_TAG", XML[i]);//else put this data in a child
            node_stack.top()->add_child(temp);
        }
        /*
         Openning Tag
          <tag>
        */
        else if (XML[i][0] == '<' && XML[i][1] != '!')
        {

        }
    }

}


