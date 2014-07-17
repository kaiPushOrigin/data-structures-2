// Binary Search Tree - Implemenation in C++
// Simple program to create a BST of integers and search an element in it
#include<iostream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
//Definition of Node for Binary search tree


class Athelete{
public:
    string name, total, salary, endorse, sport;
};

struct BstNode {
    Athelete data;
    BstNode* left;
    BstNode* right;
};

// Function to create a new Node in heap
BstNode* GetNewNode(Athelete data) {
    BstNode* newNode = new BstNode();
    newNode->data.name = data.name;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// To insert data in BST, returns address of root node
BstNode* Insert(BstNode* root, Athelete data) {
    if(root == NULL) { // empty tree
        root = GetNewNode(data);
        
    }
    // if data to be inserted is lesser, insert in left subtree.
    else if(data.name <= root->data.name) {
        root->left = Insert(root->left,data);
    }
    // else, insert in right subtree.
    else {
        root->right = Insert(root->right,data);
        
    }
    return root;
}

//To search an element in BST, returns true if element is found
bool Search(BstNode* root,Athelete data) {
	if(root == NULL) {
		return false;
	}
	else if(root->data.name == data.name) {
		return true;
        
	}
	else if(data.name <= root->data.name) {
		return Search(root->left,data);
	}
	else {
		return Search(root->right,data);
	}
}



void DisplayTree
(
 BstNode* treePtr, //in
 ostream& outStream           //inout
)

{
    
    if (treePtr != nullptr)
    {
        //Display left subtree ...
        DisplayTree(treePtr->left, outStream);
        //Display current node value, then a space ...
        outStream << treePtr->data.name << endl;
        //Display right subtree ...
        DisplayTree(treePtr->right, outStream);
    }
    
}


int main()

{
    // Creating an empty tree
    BstNode* root = NULL;
    string location;                         //name of the country
    vector<string> data, data_stream;
    string store;
    string store_stream;
    int lines=0;                             //counts no. of lines
    ifstream inFile("salaries.txt");
    while(getline(inFile, store))
    {
        
        data.push_back(store);
        lines++;
    }
    
    Athelete ath;
    for(vector<string>::size_type i=0; i<data.size(); ++i)
    {
        istringstream stream(data.at(i));           //string buffer
        while (!stream.eof())
        {
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
            //cout << ath.name << " " << ath.total << " " << ath.salary << " " << ath.endorse << " " << ath.sport << endl;
            data_stream.push_back(store_stream);
        }
    }
    cout <<"Enter name";
    string name;
    cin >> name;
    DisplayTree(root, cout);
    cout <<"Initialising from consumption.txt: "<< lines <<" lines, "
    <<(lines-3)<<" records\n";
    
    
    
    
    
    
    ///*Code to test the logic*/
    //root = Insert(root,"Hello");
    //root = Insert(root,"abcde");
    //root = Insert(root,"efefe");
    //root = Insert(root,"kaka");
    //root = Insert(root,"popo");
    //root = Insert(root,"aaa");
    //// Ask user to enter a number.
    /*string name;
     cout<<"Enter name be searched\n";
     cin>>name;*/
    ////If number is found, print "FOUND"
    /*if(Search(root,name) == true) cout<<"Found\n";
     else cout<<"Not Found\n";*/
}