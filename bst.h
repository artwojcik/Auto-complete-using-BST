/*bst.h*/

//
// Binary Search Tree ADT header file.
// Artur Wojcik
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS251, Spring 2017
//

// make sure this header file is #include exactly once:
#pragma once


//
// BST type declarations:
//
typedef char *BSTKey;
typedef struct BSTValue
{
	char *name;
	long long  weight;
} BSTValue;

typedef struct BSTNode
{
	BSTKey    Key;
	BSTValue  Value;
	struct BSTNode  *Left;
	struct BSTNode  *Right;
} BSTNode;

typedef struct BST
{
	BSTNode *Root;
	int      Count;
} BST;


//
// BST API: function prototypes
//
BST *BSTCreate();
int  BSTCompareKeys(BSTKey key1, BSTKey key2);
BSTNode *BSTSearch(BST *tree, BSTKey key);
BSTNode *BSTSearchSuggest(BST *tree, BSTKey key, int size);
int  BSTSearchDepth(BST *tree, BSTKey key);
int  BSTInsert(BST *tree, BSTKey key, BSTValue value);
int BSTHeight(BST *tree);

void BSTPrintInorder(BST *tree, void(*pf)(BSTNode*));
void BSTPrintPreorder(BST *tree, void(*pf)(BSTNode*));
void openFile(char *fileName, BST *tree);

int       BSTCount(BST *tree);
BSTValue *BSTStoreToArray(BST *tree, int size, char *name);
int BSTCountSuggested(BST *tree, char *text, int size);
void SelectionSort(BSTValue *value, int numbersSize);
void Suggest(BST *tree, int k, char* text);
void freeTree(BST *tree);
int isBST(BSTNode *node);
int maxv(BST *tree);
