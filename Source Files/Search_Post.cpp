#include "Search_Post.h"

int Search_String(string str,string SearchWord){
        size_t found = str.find(SearchWord);
        if (found != string::npos)
            return 1;
        return -1;
}
string Search_Post(vector <string> XmlVector,string word){
    Node* root = new Node();
    root->set_name(XmlVector[1]);
    int k{ 2 };
    xml2tree(root, XmlVector, k, root);
    vector <Node*> tree = Traversal(root);
    root->set_name(tree[0]->get_name());
	vector<Node*>tags_children = root->get_children();
	vector<Node*>posts(0);
    Node* temp=new Node();
    vector<Node*>p(0);
    for (int i = 0; i < tags_children.size(); i++) {
			if (tags_children[i]->get_name() == "<user>"){
                if((tags_children[0]->get_children())[2]->get_name()=="<posts>")
                    posts.push_back((tags_children[0]->get_children())[2]);
			}
    }
    for (int i = 0; i < posts.size(); i++) {
        for(int j=0;j<(posts[i]->get_children()).size();j++){
            if((posts[i]->get_children())[j]->get_name()=="<post>")
            {
                p.push_back((posts[i]->get_children())[j]);
            }
        }

    }
string s="";
    for(int i=0;i<p.size();i++){
        for(int j=0;j<(p[i]->get_children()).size();j++){
            if((p[i]->get_children())[j]->get_name()=="<body>"){
                if(Search_String((p[i]->get_children())[j]->get_data(),word)==1)
                    s=s+"Body: "+(p[i]->get_children())[j]->get_data()+"\n";
            }
        }

    }
return s;
}
