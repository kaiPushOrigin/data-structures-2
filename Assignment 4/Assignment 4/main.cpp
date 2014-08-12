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
    TwoThreeTree *pChild1;
    TwoThreeTree *pChild2;
    TwoThreeTree *pChild3;
    Babies RefLo;
    Babies RefHi;
};

bool InsertRec(TwoThreeTree *pNode, Babies &baby, TwoThreeTree **ppN1,TwoThreeTree **ppN2)
{
    TwoThreeTree *pN1  = NULL;
    TwoThreeTree *pN2  = NULL;
    TwoThreeTree *pNew = NULL;
    
    Babies key[3];           // If split occurs, turn a 3-node into a 4-node
    TwoThreeTree *pC[4];     // However, 4-node in a 2-3 is not possible in 2-3 Tree
                            // This array is used as a placeholder while rearranging thefour nodes in the correct order.
    
    
    // Internal node.  Recurses down to the appropriate child. If the recursion caused a split, finish the split logic here.
    if (pNode->pChild1 != NULL)
    {
        if (baby.name < pNode->RefLo.name) // Recurse down the first child.
        {
            if (InsertRec(pNode->pChild1, baby, &pN1, &pN2) == false)
                return false;
            
            // A split of the child nodes was performed. If this is a 2-node, we just need to rearrange the keys and child pointers.
            if (NULL == pNode->RefHi.pContext)              // shift the second child over to become the third child.
            {
                pNode->RefHi   = pNode->RefLo;
                pNode->RefLo   = baby;
                pNode->pChild3 = pNode->pChild2;      // In this case, the splitting is now contained, so we return false
                pNode->pChild2 = pN2;
                pNode->pChild1 = pN1;
                return false;
            }
            else // Convert this 3-node into a 4-node.
            {
                key[0] = baby;
                key[1] = pNode->RefLo;
                key[2] = pNode->RefHi;
                pC[0]  = pN1;
                pC[1]  = pN2;
                pC[2]  = pNode->pChild2;
                pC[3]  = pNode->pChild3;
            }
        }
        
        else if (NULL != pNode->RefHi.pContext)    // If this is a 3-node, we need to decide whether to recurse down the second or third child.
        {
            if (baby.name < pNode->RefHi.name)  // Recurse down the middle child.
            {
                if (false == InsertRec(pNode->pChild2, baby, &pN1, &pN2))
                    return false;
                
                key[0] = pNode->RefLo;   // The recursive call caused a split.  As we now have a 4-node, split this node as well.
                key[1] = baby;
                key[2] = pNode->RefHi;
                pC[0]  = pNode->pChild1;
                pC[1]  = pN1;
                pC[2]  = pN2;
                pC[3]  = pNode->pChild3;
            }
            else if (baby.name > pNode->RefHi.name)       // Recurse down the third child.
            {
                if (false == InsertRec(pNode->pChild3, baby, &pN1, &pN2))
                    return false;
                
                key[0] = pNode->RefLo;
                key[1] = pNode->RefHi;
                key[2] = baby;
                pC[0]  = pNode->pChild1;
                pC[1]  = pNode->pChild2;
                pC[2]  = pN1;
                pC[3]  = pN2;
            }
            else
            {
                pNode->RefHi = baby;
                return false;
            }
        }
        else if (baby.name > pNode->RefLo.name)          // Otherwise this is a 2-node, so recurse down the middle child.
        {
            if (InsertRec(pNode->pChild2, baby, &pN1, &pN2) == false)
                return false;
            
            pNode->RefHi   = baby;       // Split occured. Replace the current key and pointers with the values returned from recursive call
            pNode->pChild2 = pN1;
            pNode->pChild3 = pN2;
            return false;
        }
        
        else
        {
            pNode->RefLo = baby;
            return false;
        }
    }
    
    else             // Leaf node. No children. Insert the new key in this node
    {
        if (NULL == pNode->RefHi.pContext)  //This leaf only contains one key. No split required. Insert the new key into the correct place
        {
            if (baby.name > pNode->RefLo.name)    // If the new key is bigger than the one key in this node, it becomes the second key.
                pNode->RefHi = baby;
            else if (baby.name < pNode->RefLo.name)// Shift the existing key over to be the second key, then drop the new key in as the first key.
            {
                pNode->RefHi = pNode->RefLo;
                pNode->RefLo = baby;
            }
            else                                 // Replace an existing key with a new value.
                pNode->RefLo = baby;

            return false;                        // No split required.
        }
        
        if (baby.name < pNode->RefLo.name)    // Otherwise splitting is required. Rearrange the existing keys so that they are correctly sorted.
        {
            key[0] = baby;
            key[1] = pNode->RefLo;
            key[2] = pNode->RefHi;
        }
        else if (baby.name == pNode->RefLo.name)   // Special case: replace an existing value.
        {
            pNode->RefLo = baby;
            return false;
        }
        else if (baby.name < pNode->RefHi.name)
        {
            key[0] = pNode->RefLo;
            key[1] = baby;
            key[2] = pNode->RefHi;
        }
        else if (baby.name == pNode->RefHi.name)  // Special case: replace an existing value.
        {
            pNode->RefHi = baby;
            return false;
        }
        else
        {
            key[0] = pNode->RefLo;
            key[1] = pNode->RefHi;
            key[2] = baby;
        }
        pC[0] = pC[1] = pC[2] = pC[3] = NULL;  // This is a leaf node, leave all child pointers NULL.
    }
    
    // The remaining code is only executed if we have created a 4-node. This forces pNode to split.
    // The code above has already stored the keys and child pointers in the correct order.
    
    pNode->RefLo          = key[0];   // Replace the contents of pNode to contain the first two child nodes.
    pNode->RefHi.name     = "";
    pNode->RefHi.pContext = NULL;
    pNode->pChild1        = pC[0];
    pNode->pChild2        = pC[1];
    pNode->pChild3        = NULL;
    
    pNew = new TwoThreeTree();       // Create a new node to contain the last two child pointers.
    pNew->RefLo           = key[2];
    pNew->pChild1         = pC[2];
    pNew->pChild2         = pC[3];
    pNew->pChild3         = NULL;
    
    baby   = key[1];     // Return the info about these two sibling nodes for splitting it in Insert Function
    *ppN1 = pNode;
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
            Tree->RefLo   = baby;
            Tree->pChild1 = pN1;
            Tree->pChild2 = pN2;
        }
    }
    else    // Insert into an empty tree
    {
        Tree = new TwoThreeTree();
        Tree->RefLo  = baby;
    }
    return (Tree);
}


void inorder(TwoThreeTree *copyTree)
{
    if((copyTree->pChild1 == NULL) && (copyTree->pChild2 == NULL) && (copyTree->pChild3 == NULL))
        cout << copyTree->RefLo.name << " " << copyTree->RefLo.uses << " " << copyTree->RefLo.rank << endl;
    
    else if((copyTree->RefLo.name != "") && (copyTree->RefHi.name != ""))
    {
        inorder(copyTree->pChild1);
        cout << copyTree->RefLo.name << " " << copyTree->RefLo.uses << " " << copyTree->RefLo.rank << endl;
        inorder(copyTree->pChild2);
        cout << copyTree->RefHi.name << " " << copyTree->RefHi.uses << " " << copyTree->RefHi.rank << endl;
        inorder(copyTree->pChild3);
    }
    
    else
    {
        inorder(copyTree->pChild1);
        cout << copyTree->RefLo.name << " " << copyTree->RefLo.uses << " " << copyTree->RefLo.rank << endl;
        inorder(copyTree->pChild2);
    }
}

TwoThreeTree* findItem(TwoThreeTree* Tree, string key)
{
    if(key == Tree->RefLo.name)
        return Tree;
    
    else if((Tree->pChild1 == NULL) && (Tree->pChild2 == NULL) && (Tree->pChild3 == NULL))
        return NULL;
    
    else if((Tree->RefLo.name != "") && (Tree->RefHi.name != ""))
    {
        if(key < Tree->RefLo.name)
            return findItem(Tree->pChild1, key);
        else if(key < Tree->RefLo.name)
            return findItem(Tree->pChild2, key);
        else
            return findItem(Tree->pChild3, key);
    }
    else
    {
        if(key < Tree->RefLo.name)
            return findItem(Tree->pChild1, key);
        else
            return findItem(Tree->pChild2, key);
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
	int femaleBabiesIndex = 0;
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
                femaleBabiesIndex++; count++;
                break;
                
            }
		    case 2:
            {
                size_t pos = line.find(" ");
                baby.rank = line.substr(0, pos);                     // Value before first whitespace
                name = line.substr(pos+1);                           // name = whole sentence after first whitespace
                size_t posn = name.find(" ");                               // i.e second white space
                baby.name = name.substr(0, posn);
                baby.uses = name.substr(posn+1);
                Tree = Insert(baby, Tree);
                femaleBabiesIndex++;
                count = 1;
                break;
            }
	    }
	}
    string key;
    inorder(Tree);
    
    cout << "\n\n Search: ";
    cin >> key;
    
    copyTree = findItem(Tree, key);
    if (copyTree == NULL)
    {
        cout << "No data found for " << key << "\n\n";
    }
    else
    {
        cout << copyTree->RefLo.name << " " << copyTree->RefLo.uses;
    }
	
}