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

#define debug 0
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
   // void NewNode();
    
    Babies RefLo;
    Babies RefHi;
};



bool InsertRec(TwoThreeTree *pNode, Babies &baby, TwoThreeTree **ppN1,TwoThreeTree **ppN2)
{
    TwoThreeTree *pN1  = NULL;
    TwoThreeTree *pN2  = NULL;
    TwoThreeTree *pNew = NULL;
    
    Babies key[3];
    
    // If a split operation occurs, we'll have to turn a 3-node into a
    // 4-node.  However, there is no such thing as a 4-node in a 2-3
    // tree.  This array is used as a placeholder while rearranging the
    // four nodes in the correct order.
    TwoThreeTree *pC[4];
    
    // This is an internal node.  We need to start off by recursing down
    // to the appropriate child.  If the recursion caused a split, we
    // need to finish the split logic here.
    if (NULL != pNode->pChild1)
    {
        
        // Recurse down the first child.
        if (baby.name < pNode->RefLo.name)
        {
            if (false == InsertRec(pNode->pChild1, baby, &pN1, &pN2))
            {
                return false;
            }
            
            // A split of the child nodes was performed.  Figure out what
            // work is needed to clean up at this level.
            
            // If this is a 2-node, we just need to rearrange the keys and
            // child pointers.
            //
            // Since we recursed down the left, the second child remains
            // unchanged.  All we need to do for it is shift it over to
            // become the third child.
            //
            // Then we poke the returned values in as the first and second
            // child.
            //
            // In this case, the splitting is now contained, so we return
            // false.
            //
            if (NULL == pNode->RefHi.pContext)
            {
                pNode->RefHi   = pNode->RefLo;
                pNode->RefLo   = baby;
                //cout << pNode->RefLo.name;
                //cout << pNode->pChild2->RefLo.name;
                pNode->pChild3 = pNode->pChild2;
                pNode->pChild2 = pN2;
                pNode->pChild1 = pN1;
               // cout << pN2->RefLo.name;
                
                return false;
            }
            
            // Otherwise we need to convert this 3-node into a 4-node.
            // Poke the values into the arrays so the clean-up logic can
            // split this node.
            else {
                key[0] = baby;
                key[1] = pNode->RefLo;
                key[2] = pNode->RefHi;
                pC[0]  = pN1;
                pC[1]  = pN2;
                pC[2]  = pNode->pChild2;
                pC[3]  = pNode->pChild3;
            }
        }
        
        // If this is a 3-node, we need to decide whether to recurse down
        // the second or third child.
        else if (NULL != pNode->RefHi.pContext) {
            
            // Recurse down the middle child.
            if (baby.name < pNode->RefHi.name) {
                if (false == InsertRec(pNode->pChild2, baby, &pN1, &pN2)) {
                    return false;
                }
                
                // The recursive call caused a split.  Since we now have a
                // 4-node, we have no choice but to split this node as well.
                key[0] = pNode->RefLo;
                key[1] = baby;
                key[2] = pNode->RefHi;
                pC[0]  = pNode->pChild1;
                pC[1]  = pN1;
                pC[2]  = pN2;
                pC[3]  = pNode->pChild3;
            }
            
            // Recurse down the third child.
            else if (baby.name > pNode->RefHi.name) {
                if (false == InsertRec(pNode->pChild3, baby, &pN1, &pN2)) {
                    return false;
                }
                
                key[0] = pNode->RefLo;
                key[1] = pNode->RefHi;
                key[2] = baby;
                pC[0]  = pNode->pChild1;
                pC[1]  = pNode->pChild2;
                pC[2]  = pN1;
                pC[3]  = pN2;
            }
            
            else {
                pNode->RefHi = baby;
                return false;
            }
        }
        
        // Otherwise this is a 2-node, so we can only recurse down the
        // middle child.
        else if (baby.name > pNode->RefLo.name) {
            if (InsertRec(pNode->pChild2, baby, &pN1, &pN2) == false)
            {
                return false;
            }
            
            // A split occurred.  However, since this is a 2-node, the split
            // is contained to this level of the tree.  Since the recursive
            // call did all of the rearranging work, we replace the current
            // key and pointers with the values returned from the recursive
            // call.
            pNode->RefHi   = baby;
            pNode->pChild2 = pN1;
            pNode->pChild3 = pN2;
            
            return false;
        }
        
        else {
            pNode->RefLo = baby;
            return false;
        }
    }
    
    // Recursive base case:  This is where we hit a leaf node.  Unless
    // the key is found in this node, we will try to insert the new
    // key in this node, possibly causing a split.
    else
    {
        // This leaf only contains one key.  No split is required, we just
        // need to insert the new key into the correct place (or replace
        // an existing value).
        if (NULL == pNode->RefHi.pContext)
        {
            
            // If the new key is bigger than the one key in this node,
            // it becomes the second key.
            if (baby.name > pNode->RefLo.name)
            {
                pNode->RefHi = baby;
                //cout << pNode->RefHi.name;
            }
            
            // Otherwise we need to shift the existing key over to be
            // the second key, then drop the new key in as the first key.
            else if (baby.name < pNode->RefLo.name)
            {
                pNode->RefHi = pNode->RefLo;
                pNode->RefLo = baby;
            }
            
            // Otherwise we're replacing an existing key with a new value.
            // This does not insert a new value, it only replaces the
            // existing value.
            else
            {
                pNode->RefLo = baby;
            }
            
            // No split was required, so no fix-up operations will be
            // required as we back out of the recursion.
            return false;
        }
        
        // Otherwise splitting is required.  We don't need to deal with
        // any pointers, since there are no child nodes, but we do need to
        // rearrange the existing keys so that they are correctly sorted.
        //
        // Note the special cases where the key being replaced matches a
        // key already present.  Here we just need to replace the old key,
        // under the assumption that its value has been updated.
        
        if (baby.name < pNode->RefLo.name)
        {
            key[0] = baby;
            key[1] = pNode->RefLo;
            key[2] = pNode->RefHi;
            // for(int i = 0; i < 3; i++)
              // cout << key[i].name << endl;
        }
        
        // Special case: replace an existing value.
        else if (baby.name == pNode->RefLo.name)
        {
            pNode->RefLo = baby;
            return false;
        }
        
        else if (baby.name < pNode->RefHi.name)
        {
            key[0] = pNode->RefLo;
            key[1] = baby;
            key[2] = pNode->RefHi;
           // for(int i = 0; i < 3; i++)
             //   cout << key[i].name << endl;
        }
        
        // Special case: replace an existing value.
        else if (baby.name == pNode->RefHi.name)
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
        
        // Since this is a leaf node, leave all child pointers NULL.
        pC[0] = NULL;
        pC[1] = NULL;
        pC[2] = NULL;
        pC[3] = NULL;
    }
    
    
    // The remaining code is only executed if we have created a 4-node.
    // This forces pNode to be split.  The code above has already stored
    // the keys and child pointers in the correct order.
    
    // Destructively replace the contents of pNode to contain the first
    // two child nodes.
    pNode->RefLo          = key[0];
    pNode->RefHi.name     = "";
    pNode->RefHi.pContext = NULL;
    pNode->pChild1        = pC[0];
    pNode->pChild2        = pC[1];
    pNode->pChild3        = NULL;
    
    // Create a new node to contain the last two child pointers.
   
    
    pNew = new TwoThreeTree();
    pNew->RefLo           = key[2];
    pNew->pChild1         = pC[2];
    pNew->pChild2         = pC[3];
    pNew->pChild3         = NULL;
    
    // Return the info about these two sibling nodes so the caller can
    // handle the split at its level.
    baby   = key[1];
    *ppN1 = pNode;
    *ppN2 = pNew;
    
    return true;
}


TwoThreeTree *Insert(Babies baby, TwoThreeTree *Tree)
{
    
        // In the normal case, the tree is not empty.
        if (Tree != NULL)
        {
            TwoThreeTree *pN1  = NULL;
            TwoThreeTree *pN2  = NULL;
            
            // If the recursive operation returns true, we need to split the
            // root of the tree.  The existing root node has already been
            // changed to maintain sorting order (the current root pointer is
            // returned in pN1), and a new node is returned in pN2.  Since
            // all conditioning was done by the recursive routine, all we
            // need to do is create a new root node and make the two pointers
            // the children of the new root node.
            //
            // Also note that ref is pass-by-reference, so upon exiting the
            // recursive function, ref will now contain the correct key for
            // the new root node.
            //
            if (InsertRec(Tree, baby, &pN1, &pN2))
            {
                Tree = new TwoThreeTree();
                Tree->RefLo   = baby;
                Tree->pChild1 = pN1;
                Tree->pChild2 = pN2;
            }
        }
        
        // Special case for inserting into an empty tree.
        else
        {
            Tree = new TwoThreeTree();
            Tree->RefLo  = baby;
            
            //cout << Tree->RefLo.name << endl;
        }
    return (Tree);
}


void* LookUp(const string key, TwoThreeTree* Tree)
{
	if (NULL == Tree)
    {
		return NULL;
	}
    
	TwoThreeTree *pScan = Tree;
    
	while (NULL != pScan) {
		if (key < pScan->RefLo.name) {
			pScan = pScan->pChild1;
		}
		else if (key == pScan->RefLo.name) {
			return pScan->RefLo.pContext;
		}
        
		// If this is a 2-node, iterate down to the second child.
		else if (NULL == pScan->RefHi.pContext) {
			pScan = pScan->pChild2;
		}
        
		// Otherwise we need to compare against the higher key to
		// determine whether we traverse the second or third child.
		else if (key < pScan->RefHi.name) {
			pScan = pScan->pChild2;
		}
		else if (key > pScan->RefHi.name) {
			pScan = pScan->pChild3;
		}
		else {
			return pScan->RefHi.pContext;
		}
	}
    
	return pScan;
}

void inorder(TwoThreeTree *copyTree)
{
  if((copyTree->pChild1 == NULL) && (copyTree->pChild2 == NULL) && (copyTree->pChild3 == NULL))
     cout << copyTree->RefLo.name << endl;
else if((copyTree->RefLo.name != "") && (copyTree->RefHi.name != ""))
{
  inorder(copyTree->pChild1);
cout << copyTree->RefLo.name << endl;
inorder(copyTree->pChild2);
    cout << copyTree->RefHi.name << endl;
inorder(copyTree->pChild3);
}
else
{
  inorder(copyTree->pChild1);
 cout << copyTree->RefLo.name << endl;
}

}



int main (int argc, char** argv)
{
    Babies baby;
	ifstream infile("babies.txt");
    TwoThreeTree *Tree, *copyTree;
    Tree = NULL;

	string line, token, input;
	string rank, name, uses;
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
                if(Tree == NULL)
                {
                    cout << "Null" << endl;
                }
                Tree = Insert(baby, Tree);
                femaleBabiesIndex++; count++;
                break;
                
            }
		    case 2:
            {
                count = 1;
                break;
            }
	    }
	}
    //cout << Tree->RefHi.name;
    string key;
    inorder(Tree);
    
   // cout << "Search: ";
   // cin >> key;
   // LookUp(key, Tree);
  // cout << Tree->RefLo.name;

	
}