// Author: Kashif Kashif
// Binary Search Tree - Assignment 1
// paravenu.cpp
// GitHubLink - https://github.com/kashifkai28/data-structures-2/tree/Assignment-1

#include<iostream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class Athelete
{
public:
    string name, total, salary, endorse, sport;
};

struct BstNode {
    Athelete data;
    BstNode* left;
    BstNode* right;
};

//Source - YouTube - mycodeschool
//Link - https://www.youtube.com/watch?v=COZK7NATh4k
//GitHub Link - https://gist.github.com/mycodeschool/44e1a9183ab0e931f729
// Function to create a new Node in heap
BstNode* GetNewNode(Athelete data)
{
    BstNode* newNode = new BstNode();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//To insert data in BST, returns address of root node
BstNode* Insert(BstNode* root, Athelete data)
{
    if(root == NULL)
    { // empty tree
        root = GetNewNode(data);
    }
    // if data to be inserted is lesser, insert in left subtree.
    else if(data.name <= root->data.name)
    {
        root->left = Insert(root->left,data);
    }
    // else, insert in right subtree.
    else
    {
        root->right = Insert(root->right,data);
    }
    return root;
}

void SearchAthelete(BstNode* root, string a, Athelete data)
{
    if(root == NULL)
    {
        cout << "No data found for " << a << "\n" << endl;
    }
    else if(root->data.name == a)
    {
        cout << root->data.name << " made " << root->data.total
        << " last year in" <<root->data.sport
        << "\n> " << root->data.salary << " salary/winnings + "
        << root->data.endorse << " endorsements\n" << endl;
    }
    else if(a <= root->data.name )
    {
        return SearchAthelete(root->left,a, data);
    }
    else
    {
        return SearchAthelete(root->right,a, data);
    }
}

//Source - Dr. Scobey Website
//Link - http://cs.smu.ca/~porter/csc/common_341_342/code/trees/bst/bst2.cpp
//Displays the entire Binary Search Tree
void DisplayTree
(
 BstNode* treePtr, //in
 ostream& outStream,           //inout
 Athelete data
 )
{
    if (treePtr != nullptr)
    {
        //Display left subtree ...
        DisplayTree(treePtr->left, outStream, data);
        
        //Display current node value, then a space ...
        outStream << treePtr->data.name << ": " << treePtr->data.total
        << " (" << treePtr->data.salary << " + " << treePtr->data.endorse
        << ")"  << treePtr->data.sport <<endl;
        
        //Display right subtree ...
        DisplayTree(treePtr->right, outStream, data);
    }
}

int main()
{
    BstNode* root = NULL;                // Creating an empty tree
    int lines=0;                         // Counts no. of lines
    vector<string> data, data_stream;
    string location;                     //name of the country
    string store;
    string store_stream;
    ifstream inFile("salaries.txt");
    while(getline(inFile, store))
    {
        data.push_back(store);
        lines++;
    }
    
    int counter = 0;
    Athelete ath;
    for(vector<string>::size_type i=0; i<data.size(); ++i)
    {
        istringstream stream(data.at(i));           //string buffer
        while (!stream.eof())
        {
            ++counter;
            getline(stream, store_stream, ',');
            ath.name = store_stream;
            getline(stream, store_stream, ',');
            ath.total = store_stream;
            getline(stream, store_stream, ',');
            ath.salary = store_stream;
            getline(stream, store_stream, ',');
            ath.endorse = store_stream;
            getline(stream, store_stream, ',');
            ath.sport = store_stream;
            root = Insert(root,ath);
            data_stream.push_back(store_stream);
        }
    }
    cout <<"Initialising from consumption.txt: "<< lines <<" lines, "
    <<(lines-3)<<" records\n\n";
    string name;
    do
    {
        cout << "Please enter the name of a person of interest: ";
        getline(cin, name);
        if (name == "Quit")
        {
            cout <<"Thank you for using paravenu" << endl;   // Exit paravenu
            break;
        }
        else if(name == "ALL")
        {
            DisplayTree(root, cout, ath);
            cout << "\n";
        }
        else
        {
            SearchAthelete(root, name, ath);
        }
    }
    while(name !="Quit");
}