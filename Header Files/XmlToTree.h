#pragma once
#include <vector>
#include <string>
using namespace std;

typedef struct
{
    string name;
    int start_index;
} tag;

class Node
{
private:
    string name;
    string data;
    vector<Node*> children;

public:
    Node();
    Node(string name, string data);
    string get_name();
    void set_name(string node_name); 
    string get_data();
    void set_data(string node_data);
    void add_child(Node* child);
    Node* pop_child();
    vector<Node*> get_children();
    bool diffChildern(Node* node);
    void addchild2Node(Node* child, int& level);
    static void addchild(Node* node, Node* child);
    ~Node();
};

class Tree
{
private:
    Node root;
public:
    Node getroot();
};

static void xml2tree(Node* node, vector <string> xml, int& i, Node* root);
vector <Node*> Traversal(Node* root);