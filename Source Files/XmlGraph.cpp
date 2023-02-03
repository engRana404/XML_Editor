#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <String>
#include "XmlToTree.h"
#include "XmlGraph.h"



//A function that takes a vector of node pointers as input
//And Return Vector of vectors as output
vector <vector <int>> FollowerList(vector <Node*> tree)
{
    //Vector of vectors with n values.
    vector <vector <int>> list;
    //the vector has 10 elements each of them is a vector of integer.
    list.resize(10, vector <int>());

    int l = 0;
    int i = 0;
    //Iterate over the vector of nodes
    while (i < tree.size() -1 )
    {
        //If the name of the node is <user>
        if (tree[i]->get_name() == "<user>")
        {
            //We want to get all the data of the current user so we iterate till we reach another <user>
            while (i < tree.size() - 1 && tree[i + 1]->get_name() != "<user>" )
            {
                //If the element is "<id>"
                if (tree[i + 1]->get_name() == "<id>" )
                {
                    //Push the id in the list and turn it into int.
                    list[l].push_back(stoi(tree[i + 1]->get_data()));

                }
                //ِAdvance i to complete the iteration
                i++;

            }
            //if l is advanced  -> we go to the next user.
            l++;
        }
        else { //skip anything other than user.
                i++;
        }
    }

    return list; //((ids in user 1 ),(ids in user 2),())
}

//The function takes a vector of string ###(The result of convert2vector function)
void graph(vector <string> data)
{
    //Make a root node of the tree
    Node* root = new Node();
    //Let the root name equal to the firt tag in the vector (normally users)
    root->set_name(data[1]);
    int i{ 2 };
    //Create a tree with the root and the rest of the nodes from the vector
    xml2tree(root, data, i, root);
   //Traverse the tree
    vector <Node*> t = Traversal(root);
   //Make a vector of vectors of the followers using the previous function
    vector <vector <int>> v = FollowerList(t);
    //A function used to create a file representing the graph ###(Will be removed when we do the GUI)
    RepresentinFile(v); //Another function.

}


//Function to represent the list of followers in a file.
void RepresentinFile(vector<vector<int>> list)
{
    fstream myfile;
    myfile.open("a.dot", ios::out); // 8 2 3
    myfile << "digraph test{\n";
    for (int i = 0; i < (int)list.size(); i++)
    {
        for (int j = 1; j < (int)list[i].size(); j++)
        {
            myfile << list[i][0] << "->" << list[i][j] << endl;
        }
    }
    myfile << "}";
    myfile.close();
}
//Get nDegree of all users
vector <int> inDegree(vector <vector <int>> list){
    int n=list.size();

    vector <int> indegree(n,0);

     for (int i = 0; i < (int)list.size(); i++)
    {
        for (int j = 1; j < (int)list[i].size(); j++)
        {
           indegree[list[i][0]]++;

        }
    }
return indegree;
}

//Get outDegree of all users
vector <int> outDegree(vector <vector <int>> list){

    int n=list.size();
    vector <int> outdegree(n,0);

     for (int i = 0; i < (int)list.size(); i++)
    {
        for (int j = 1; j < (int)list[i].size(); j++)
        {
           outdegree[list[i][j]]++;

        }
    }
return outdegree;
}
int maxdegree(vector<int> degree){
    int maxm=0;
    int maxin=0;

    for(int i=0; i<degree.size();i++){
       if(degree[i]>maxm) {
               maxin=i;
               maxm=degree[i];
    } }
    return maxin; }


string Mutual(int n1,int n2,vector <vector <int>> list){
    vector <int> mutual;
    string m="";
    int count=0;
    for (int i = 0; i < (int)list.size(); i++)
   {
       count = 0;
       for (int j = 1; j < (int)list[i].size(); j++)
       {
          if(list[i][j]==n1 ||list[i][j]==n2){count++;}
          if(count==2){mutual.push_back(list[i][0]);}
       }
   }
   for(int i=0;i<(int)mutual.size();i++){
       m=m+to_string(mutual[i])+" ";

   }
   return "The mutuals between "+to_string(n1)+" and  "+to_string(n2)+" are \n "+m;

}
