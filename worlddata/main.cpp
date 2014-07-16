// Binary Search Tree - Implemenation in C++
// Simple program to create a BST of integers and search an element in it
#include<iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
//Definition of Node for Binary search tree
struct node
{
    int key_value, lineNumber;
    char *word;
    struct node *left,*right;
};

struct node *inserttree(struct node *tree,char *s, int lineNumber)
{
    int i;
    
    if (tree==NULL)
    {
        if ( ( tree = (struct node *) malloc( sizeof(struct node) ) ) !=NULL)
        {
            if ((tree->word=(char *) malloc(strlen(s)+1))==NULL)
            {
                free(tree);
                tree=NULL;
            }
            else
            {
                tree->left=NULL;
                tree->right=NULL;
                strcpy(tree->word,s);
                tree->lineNumber = lineNumber ;
            }
        }
    }
    
    else if ((i=strcmp(tree->word,s))>0)
    {
        tree->left=inserttree(tree->left,s, lineNumber);
    }
    else if (i<0)
    {
        tree->right=inserttree(tree->right,s, lineNumber);
    }
    
    return tree;
}

void printtree(struct node *tree)
{
    
    if (tree!=NULL)
    {
        printtree(tree->left);
        printf("%s %d\n",tree->word, tree->lineNumber);
        
        printtree(tree->right);
    }
}

//int search(struct node *tree)
//{
//  int key;
//  tree->right->key_value = key;
//  return key;
//}

void freetree(struct node *tree)
{
    if (tree!=NULL)
    {
        free(tree->word);
        freetree(tree->left);
        freetree(tree->right);
        free(tree);
    }
}

int main(void)
{
    FILE *f;
    char s[1024]; /*assumes a word cannot be longer than 1023 chars*/
    struct node *tree=NULL;
    int line = 1;
    
    if ((f=fopen("consumption.txt","r"))==NULL)
        printf("Unable to open Test.txt\n");
    else
    {
        while (fscanf(f,"%1023s",s)!=EOF)
            tree=inserttree(tree,s, line++);
        fclose(f);
        
        printtree(tree);  //moved from inserttree
        freetree(tree);
    }
    
    system("pause");
    return 0;
}
