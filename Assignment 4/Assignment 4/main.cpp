/*
 * Popularity
 * Assignment 4
 * Kashif, August 2014
 */
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

struct Babies
{
public:
	string name, rank, uses;
    void* pContext;
};

struct TwoThreeTree
{
    TwoThreeTree *leftChildPtr;
    TwoThreeTree *midChildPtr;
    TwoThreeTree *rightChildPtr;
    Babies smallItem;
    Babies largeItem;
};

bool InsertRec(TwoThreeTree *parentNode, Babies &baby, TwoThreeTree **ppN1,TwoThreeTree **ppN2)
{
    TwoThreeTree *newNode1  = NULL;
    TwoThreeTree *newNode2  = NULL;
    TwoThreeTree *pNew = NULL;
    
    Babies key[3];           // If split occurs, turn a 3-node into a 4-node
    TwoThreeTree *pC[4];     // However, 4-node in a 2-3 is not possible in 2-3 Tree
                            // This array is used as a placeholder while rearranging thefour nodes in the correct order.
    
    
    // Internal node.  Recurses down to the appropriate child. If the recursion caused a split, finish the split logic here.
    if (parentNode->leftChildPtr != NULL)
    {
        if (baby.name < parentNode->smallItem.name) // Recurse down the first child.
        {
            if (InsertRec(parentNode->leftChildPtr, baby, &newNode1, &newNode2) == false)
                return false;
            
            // A split of the child nodes was performed. If this is a 2-node, we just need to rearrange the keys and child pointers.
            if (NULL == parentNode->largeItem.pContext)              // shift the second child over to become the third child.
            {
                parentNode->largeItem   = parentNode->smallItem;
                parentNode->smallItem   = baby;
                parentNode->rightChildPtr = parentNode->midChildPtr;      // In this case, the splitting is now contained, so we return false
                parentNode->midChildPtr = newNode2;
                parentNode->leftChildPtr = newNode1;
                return false;
            }
            else // Convert this 3-node into a 4-node.
            {
                key[0] = baby;
                key[1] = parentNode->smallItem;
                key[2] = parentNode->largeItem;
                pC[0]  = newNode1;
                pC[1]  = newNode2;
                pC[2]  = parentNode->midChildPtr;
                pC[3]  = parentNode->rightChildPtr;
            }
        }
        
        else if (NULL != parentNode->largeItem.pContext)    // If this is a 3-node, we need to decide whether to recurse down the second or third child.
        {
            if (baby.name < parentNode->largeItem.name)  // Recurse down the middle child.
            {
                if (false == InsertRec(parentNode->midChildPtr, baby, &newNode1, &newNode2))
                    return false;
                
                key[0] = parentNode->smallItem;   // The recursive call caused a split.  As we now have a 4-node, split this node as well.
                key[1] = baby;
                key[2] = parentNode->largeItem;
                pC[0]  = parentNode->leftChildPtr;
                pC[1]  = newNode1;
                pC[2]  = newNode2;
                pC[3]  = parentNode->rightChildPtr;
            }
            else if (baby.name > parentNode->largeItem.name)       // Recurse down the third child.
            {
                if (false == InsertRec(parentNode->rightChildPtr, baby, &newNode1, &newNode2))
                    return false;
                
                key[0] = parentNode->smallItem;
                key[1] = parentNode->largeItem;
                key[2] = baby;
                pC[0]  = parentNode->leftChildPtr;
                pC[1]  = parentNode->midChildPtr;
                pC[2]  = newNode1;
                pC[3]  = newNode2;
            }
            else
            {
                parentNode->largeItem = baby;
                return false;
            }
        }
        else if (baby.name > parentNode->smallItem.name)          // Otherwise this is a 2-node, so recurse down the middle child.
        {
            if (InsertRec(parentNode->midChildPtr, baby, &newNode1, &newNode2) == false)
                return false;
            
            parentNode->largeItem   = baby;       // Split occured. Replace the current key and pointers with the values returned from recursive call
            parentNode->midChildPtr = newNode1;
            parentNode->rightChildPtr = newNode2;
            return false;
        }
        
        else
        {
            parentNode->smallItem = baby;
            return false;
        }
    }
    
    else             // Leaf node. No children. Insert the new key in this node
    {
        if (NULL == parentNode->largeItem.pContext)  //This leaf only contains one key. No split required. Insert the new key into the correct place
        {
            if (baby.name > parentNode->smallItem.name)    // If the new key is bigger than the one key in this node, it becomes the second key.
                parentNode->largeItem = baby;
            else if (baby.name < parentNode->smallItem.name)// Shift the existing key over to be the second key, then drop the new key in as the first key.
            {
                parentNode->largeItem = parentNode->smallItem;
                parentNode->smallItem = baby;
            }
            else                                 // Replace an existing key with a new value.
                parentNode->smallItem = baby;

            return false;                        // No split required.
        }
        
        if (baby.name < parentNode->smallItem.name)    // Otherwise splitting is required. Rearrange the existing keys so that they are correctly sorted.
        {
            key[0] = baby;
            key[1] = parentNode->smallItem;
            key[2] = parentNode->largeItem;
        }
        else if (baby.name == parentNode->smallItem.name)   // Special case: replace an existing value.
        {
            parentNode->smallItem = baby;
            cout << "small item " << parentNode->smallItem.name << endl;
            return false;
        }
        else if (baby.name < parentNode->largeItem.name)
        {
            key[0] = parentNode->smallItem;
            key[1] = baby;
            key[2] = parentNode->largeItem;
        }
        else if (baby.name == parentNode->largeItem.name)  // Special case: replace an existing value.
        {
            parentNode->largeItem = baby;
            cout << "large item " << parentNode->largeItem.name << endl;

            return false;
        }
        else
        {
            key[0] = parentNode->smallItem;
            key[1] = parentNode->largeItem;
            key[2] = baby;
        }
        pC[0] = pC[1] = pC[2] = pC[3] = NULL;  // This is a leaf node, leave all child pointers NULL.
    }
    
    // The remaining code is only executed if we have created a 4-node. This forces pNode to split.
    // The code above has already stored the keys and child pointers in the correct order.
    
    parentNode->smallItem          = key[0];   // Replace the contents of pNode to contain the first two child nodes.
    parentNode->largeItem.name     = "";
    parentNode->largeItem.pContext = NULL;
    parentNode->leftChildPtr        = pC[0];
    parentNode->midChildPtr        = pC[1];
    parentNode->rightChildPtr        = NULL;
    
    pNew = new TwoThreeTree();       // Create a new node to contain the last two child pointers.
    pNew->smallItem           = key[2];
    pNew->leftChildPtr         = pC[2];
    pNew->midChildPtr         = pC[3];
    pNew->rightChildPtr         = NULL;
    
    baby   = key[1];     // Return the info about these two sibling nodes for splitting it in Insert Function
    *ppN1 = parentNode;
    *ppN2 = pNew;
    return true;
}


TwoThreeTree *Insert(Babies baby, TwoThreeTree *Tree)
{
    if (Tree != NULL)
    {
        TwoThreeTree *pN1  = NULL;
        TwoThreeTree *pN2  = NULL;
        if (InsertRec(Tree, baby, &pN1, &pN2))  // If InsertRec is true, split the root of the tree
        {                                       // pN1 is the current root pointer, a new node is returned in pN2
            Tree = new TwoThreeTree();          // baby is passed by reference, it contains the key for the new root
            Tree->smallItem   = baby;
            Tree->leftChildPtr = pN1;
            Tree->midChildPtr = pN2;
        }
    }
    else    // Insert into an empty tree
    {
        Tree = new TwoThreeTree();
        Tree->smallItem  = baby;
    }
    return (Tree);
}


void inorder(TwoThreeTree *copyTree)
{
    if((copyTree->leftChildPtr == NULL) && (copyTree->midChildPtr == NULL) && (copyTree->rightChildPtr == NULL))
        cout << copyTree->smallItem.name << endl;// << " " << copyTree->smallItem.uses << " " << copyTree->smallItem.rank << endl;
    
    else if((copyTree->smallItem.name != "") && (copyTree->largeItem.name != ""))
    {
        inorder(copyTree->leftChildPtr);
        cout << copyTree->smallItem.name << endl;//<< " " << copyTree->smallItem.uses << " " << copyTree->smallItem.rank << endl;
        inorder(copyTree->midChildPtr);
        cout << copyTree->largeItem.name << endl;//<< " " << copyTree->largeItem.uses << " " << copyTree->largeItem.rank << endl;
        inorder(copyTree->rightChildPtr);
    }
    
    else
    {
        inorder(copyTree->leftChildPtr);
        cout << copyTree->smallItem.name << endl;//<< " " << copyTree->smallItem.uses << " " << copyTree->smallItem.rank << endl;
        inorder(copyTree->midChildPtr);
    }
}

void findItem(TwoThreeTree* Tree, string key)
{
    if(key == Tree->smallItem.name || key == Tree->largeItem.name)
    {
        if(key==Tree->smallItem.name)
            cout << Tree->smallItem.name << " is the " << Tree->smallItem.rank << "th name (" << Tree->smallItem.uses
            << " uses in 2013)";
        else
            cout << Tree->largeItem.name << " is the " << Tree->largeItem.rank << "th name (" << Tree->largeItem.uses
            << " uses in 2013)";
            
    }
    
    else if((Tree->leftChildPtr == NULL) && (Tree->midChildPtr == NULL) && (Tree->rightChildPtr == NULL))
        cout << "NULL";
    
    
    else if((Tree->smallItem.name != "") && (Tree->largeItem.name != ""))
    {
        if(key < Tree->smallItem.name)
             findItem(Tree->leftChildPtr, key);
        else if(key < Tree->largeItem.name)
             findItem(Tree->midChildPtr, key);
        else
             findItem(Tree->rightChildPtr, key);
    }
    else
    {
        if(key < Tree->smallItem.name)
             findItem(Tree->leftChildPtr, key);
        else
             findItem(Tree->midChildPtr, key);
    }
}

int main (int argc, char** argv)
{
    Babies baby;
	ifstream infile("babies.txt");
    TwoThreeTree *Tree, *copyTree;
    Tree = NULL;
    
	string line, rank, name, uses;
	int count = 1;
	int BabiesIndex = 0;
	while (getline(infile, line))
	{
        copyTree = new TwoThreeTree();
		switch(count)
		{
			case 1:
            {
                size_t pos = line.find(" ");
                baby.rank = line.substr(0, pos);      // Value before first whitespace
                name = line.substr(pos+1);                           // name = whole sentence after first whitespace
                size_t posn = name.find(" ");                               // i.e second white space
                baby.name = name.substr(0, posn);
                baby.uses = name.substr(posn+1);
                Tree = Insert(baby, Tree);
                BabiesIndex++; count++;
                break;
                
            }
		    case 2:
            {
                //size_t pos = line.find(" ");
                //baby.rank = line.substr(0, pos);                     // Value before first whitespace
                //name = line.substr(pos+1);                           // name = whole sentence after first whitespace
                //size_t posn = name.find(" ");                               // i.e second white space
                //baby.name = name.substr(0, posn);
                //baby.uses = name.substr(posn+1);
                //Tree = Insert(baby, Tree);
                BabiesIndex++;
                count = 1;
                break;
            }
	    }
	}
    cout << "Initializing from babies.txt: " << BabiesIndex << "lines/records" << endl;
    string key = "";
    inorder(Tree);
    
    do
    {
    cout << "\n\nPlease enter a name of interest: ";
    cin >> key;
    if(key == "QUIT")
    {
        cout << "Thank you for using popularity";
        break;
    }
    findItem(Tree, key);

    }while(true);
	
}