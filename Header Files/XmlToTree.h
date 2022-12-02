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
    ~Node();
};

