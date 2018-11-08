/*bst.c*/

/* Artur Wojcik
   CS 251
   */

//
// Binary Search Tree ADT implementation file.
// Artur Wojcik
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS251, Spring 2017
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bst.h"


//
// BSTCreate: dynamically creates and returns an empty
// binary search tree:
//
BST *BSTCreate()
{
	BST *tree;

	tree = (BST *)malloc(sizeof(BST));
	tree->Root = NULL;
	tree->Count = 0;

	return tree;
}


//
// BSTCompareKeys: compares key1 and key2, returning
//   value < 0 if key1 <  key2
//   0         if key1 == key2
//   value > 0 if key1 >  key2
//
int BSTCompareKeys(BSTKey key1, BSTKey key2)
{
	if (strcmp(key1, key2) < 0)
		return -1;
	else if (strcmp(key1, key2) == 0)
		return 0;
	else
		return 1;
}

//function that compares beginig of the string in the tree 
//depends on size for example if size = 9 compares first 9 characters 
//from string that user looking for to string in the node 
int BSTCompareKeysSuggest(BSTKey key1, BSTKey key2, int size)
{
	if (strncmp(key1, key2, size) < 0)
		return -1;
	else if (strncmp(key1, key2, size) == 0)
		return 0;
	else
		return 1;
}//BSTCompareKeysSuggest

 // BSTSearchSuggest: searches the binary search tree for a node containing the
 // begining of the string. Based on user input and size of the input 
//If a match is found, a pointer to the node is returned, otherwise NULL is returned.
 //
BSTNode *BSTSearchSuggest(BST *tree, BSTKey key, int size)
{
	BSTNode *cur = tree->Root;

	//
	// search the tree to see if it contains a matching key:
	//
	while (cur != NULL)
	{
		if (BSTCompareKeysSuggest(key, cur->Key, size) == 0)  // found!
			return cur;
		else if (BSTCompareKeysSuggest(key, cur->Key, size) < 0)  // smaller, go left:
		{
			cur = cur->Left;
		}
		else  // larger, go right:
		{
			cur = cur->Right;
		}
	}

	// if we get here, we fell out of the tree, and didn't find it:
	return NULL;
}//end BSTSearchSuggest


// BSTSearch: searches the binary search tree for a node containing the
// same key.  If a match is found, a pointer to the node is returned, 
// otherwise NULL is returned.
//
BSTNode *BSTSearch(BST *tree, BSTKey key)
{
	BSTNode *cur = tree->Root;

	//
	// search the tree to see if it contains a matching key:
	//
	while (cur != NULL)
	{
		if (BSTCompareKeys(key, cur->Key) == 0)  // found!
			return cur;
		else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
		{
			cur = cur->Left;
		}
		else  // larger, go right:
		{
			cur = cur->Right;
		}
	}

	// if we get here, we fell out of the tree, and didn't find it:
	return NULL;
}


//
// BSTSearchDepth: searches the binary search tree for a node containing the
// same key, returning the depth of that node if found.  The root node is 
// considered depth 0, the next level down is a depth of 1, and so forth.
// If a matching key is not found, the function returns a depth of -1.
//
int BSTSearchDepth(BST *tree, BSTKey key)
{
	BSTNode *cur = tree->Root;
	int depth = 0;

	//
	// search the tree to see if it contains a matching key:
	//
	while (cur != NULL)
	{
		if (BSTCompareKeys(key, cur->Key) == 0)  // found!
			return depth;
		else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
		{
			cur = cur->Left;
		}
		else  // larger, go right:
		{
			cur = cur->Right;
		}

		depth++;
	}

	// if we get here, we fell out of the tree, and didn't find it:
	return -1;
}



// BSTInsert: inserts the given (key, value) pair into the binary search
// tree.  Returns true (non-zero) if the insert was successful, returns 
// false (0) if the given key is already in the tree -- in which case the
// given (key, value) pair is not inserted.
//
int BSTInsert(BST *tree, BSTKey key, BSTValue value)
{
	BSTNode *prev = NULL;
	BSTNode *cur = tree->Root;

	//
	// first we search the tree to see if it already contains key:
	//
	while (cur != NULL)
	{
		if (BSTCompareKeys(key, cur->Key) == 0)  // already in tree, failed:
		{
			return 0;
		}
		else if (BSTCompareKeys(key, cur->Key) < 0)  // smaller, go left:
		{
			prev = cur;
			cur = cur->Left;
		}
		else  // larger, go right:
		{
			prev = cur;
			cur = cur->Right;
		}
	}

	// 
	// If we get here, tree does not contain key, so insert new node
	// where we fell out of tree:
	//
	BSTNode *T = (BSTNode *)malloc(sizeof(BSTNode));

	T->Key = key; 
	T->Value = value;
	T->Left = NULL;
	T->Right = NULL;

	//
	// link T where we fell out of tree -- after prev:
	//
	if (prev == NULL)  // tree is empty, insert @ root:
	{
		tree->Root = T;
	}
	else if (BSTCompareKeys(key, prev->Key) < 0)  // smaller, insert to left:
	{
		prev->Left = T;
	}
	else  // larger, insert to right:
	{
		prev->Right = T;
	}

	tree->Count++;

	return 1;  // success:
}


//
// BSTPrintInorder: prints the nodes of the given binary search
// tree inorder to the console.
//
// NOTE: "pf" is a print function that must be declared like this
// (though the name "pf" doesn't really matter):
//
//  void pf(BSTNode *cur)
//  { ...}
//
// When you call, pass pf and then you'll be able to control 
// what gets printed when a node is "visited".
//
void _BSTPrintInorder(BSTNode *root, void(*pf)(BSTNode*))
{
	if (root == NULL)  // base case: empty tree
		return;
	else  // recursive case: non-empty tree
	{
		_BSTPrintInorder(root->Left, pf);
		pf(root);
		_BSTPrintInorder(root->Right, pf);
	}
}

void BSTPrintInorder(BST *tree, void(*pf)(BSTNode*))
{
	printf(">>Inorder: %d node(s)\n", tree->Count);

	_BSTPrintInorder(tree->Root, pf);

	printf(">><<\n");
}


//
// BSTPrintPreorder: prints the nodes of the given binary search
// tree pre-order to the console.
//
// NOTE: "pf" is a print function that must be declared like this
// (though the name "pf" doesn't really matter):
//
//  void pf(BSTNode *cur)
//  { ...}
//
// When you call, pass pf and then you'll be able to control 
// what gets printed when a node is "visited".
//
void _BSTPrintPreorder(BSTNode *root, void(*pf)(BSTNode*))
{
	if (root == NULL)  // base case: empty tree
		return;
	else  // recursive case: non-empty tree
	{
		pf(root);
		_BSTPrintPreorder(root->Left, pf);
		_BSTPrintPreorder(root->Right, pf);
	}
}

void BSTPrintPreorder(BST *tree, void(*pf)(BSTNode*))
{
	printf(">>Preorder: %d node(s)\n", tree->Count);

	_BSTPrintPreorder(tree->Root, pf);

	printf(">><<\n");
}


//helper function to count number of total suggested names in program 
//typed by user
void _BSTCountSuggested(BSTNode *root, char *key1, int size, int *numSuggested) {

	if (root == NULL) {
		return;
	}if (BSTCompareKeysSuggest(key1, root->Key, size) == 0) {

		(*numSuggested)++;		//updates total suggested
	}

	if (root->Left != NULL) {//go left

		_BSTCountSuggested(root->Left, key1, size, numSuggested);

	}
	if (root->Right != NULL) {//go rigth
		_BSTCountSuggested(root->Right, key1, size, numSuggested);
	}
	
}//end bstcountsuggest

//calculate number of suggested words using recursiob 
int BSTCountSuggested(BST *tree, char *text, int size) {
	int numSuggested = 0;
	_BSTCountSuggested(tree->Root, text, size, &numSuggested);
	return  numSuggested;	//total nuber suggested

}//end bstcouny suggest

//helper function to count nodes in the tree
int _BSTCountNodes(BSTNode *root) {
	int count = 1;
	if (root == NULL) {
		return 0;
	}
	if (root->Left != NULL) {
		count += _BSTCountNodes(root->Left);
	}
	if (root->Right != NULL) {
		count += _BSTCountNodes(root->Right);
	}
	return count;//total number of nodes in the tree
}

//
// BSTCount: returns # of nodes in the tree.
//
int BSTCount(BST *tree)
{
	return _BSTCountNodes(tree->Root);
}



//recursive function to store ellemnts into dynamicly allocated aarray of struct 
//pass by refference index value 
void _StoreToArray(BSTNode *root, BSTValue *arr, int *index, char *name) {

	if (root == NULL) {
		return;
	}//if empty tree

	else {
		_StoreToArray(root->Left, arr, index, name);

		int len = strlen(name); 

		if (BSTCompareKeysSuggest(name, root->Key, len) == 0) {

			arr[*index] = root->Value;
			(*index)++;			//update index during evry call
		}//end iff...

		_StoreToArray(root->Right, arr, index, name);
	}//end else

}//end of storetoarray


//function dynamicly allocates array of struct inside call for helper 
//function to do this recursivly 
BSTValue *BSTStoreToArray(BST *tree, int size, char *name)
{
	BSTValue *values = (BSTValue*)malloc(size * sizeof(BSTValue));
	int i = 0;

	_StoreToArray(tree->Root, values, &i, name);

	return values;	//returns pointer to newly allocated array of struct
}//end BSTstoretoarray



//opens file and read line by line from file 
//stores information into BST 
void openFile(char *fileName, BST *tree) {

	long long int weight = 0; 
	char singleLine[512];
	char *cp = NULL;
	int textSize = sizeof(singleLine) / sizeof(singleLine[0]);

	BSTValue value; 
	BSTKey Key;
	
	//opens file 
	FILE *inputFile = fopen(fileName, "r");

	if (inputFile == NULL) {
		printf("ERROR OPENING FILE\n");
		exit(-1);
	}//end if file was not open 
	
	fscanf(inputFile, " %lld", &weight); 
	fgets(singleLine, textSize, inputFile); 

	while (!feof(inputFile)) {//while loop until end of file flag 

		singleLine[strcspn(singleLine, "\r\n")] = '\0';  // strip EOL char(s):
		cp = singleLine;

		//whie loop advance pointer to skip white spaces in front of the string 
		while (*cp == ' ' || *cp == '\t')
			cp++;

		//allocates memory for name/key in the struct 
		value.name = (char*)malloc((strlen(cp) + 1) * sizeof(char));

		//stores input from file to the structer 
		value.weight = weight; 
		strcpy(value.name, cp); 
		Key = value.name; 
				
		BSTInsert(tree, Key, value);	//insert into tree
		
		fscanf(inputFile, " %lldd", &weight);
		fgets(singleLine, textSize, inputFile);

	}//end while loop eof

	fclose(inputFile);//close file 

}//end open file 


//helper function to determine which value is bigger 
//to calculate height of the tree
int maxNumber(int x, int y) {
	if (x > y)
		return x;
	else
		return y;
}//end maxNumber


//recursive helper function that that calculate heigth of the tree
int _BSTHeight(BSTNode *root) {

	if (root == NULL)
		return -1;
	else
		return 1 + maxNumber(_BSTHeight(root->Left), _BSTHeight(root->Right));
}//end _BSTHeight


//function that calculates height of the tree 
//call to helper function 
int BSTHeight(BST *tree) {

	return _BSTHeight(tree->Root);
}//end BSTHeight


//selection sort that sorts values in the array by weigth 
void SelectionSort(BSTValue *value, int numbersSize) {
	int i = 0;
	int j = 0;
	int indexSmallest = 0;
	BSTValue temp;  // Temporary variable for swap

	for (i = 0; i < numbersSize; ++i) {

		// Find index of smallest remaining element
		indexSmallest = i;
		for (j = i + 1; j < numbersSize; ++j) {

			if (value[j].weight > value[indexSmallest].weight) {
				indexSmallest = j;
			}//end if 
		}//end for j ....

		// Swap numbers[i] and numbers[indexSmallest]
		temp = value[i];
		value[i] = value[indexSmallest];
		value[indexSmallest] = temp;
	}//end for i....
}//end selection sort


//function that print k number of matches and string that matches 
// with weigth if matches is less than user aksed for 
//loop will brake at number of matches
void printMatches(BSTValue *value, int k, int numOfmatchs) {
	int i = 0;

	for (i = 0; i < k; i++) {
		if (i == numOfmatchs)
			break;

		printf("%s: %lld\n", value[i].name, value[i].weight);

	}//end for i...
}//end printMatchs....

//function that to suggestion based on how many letters and what 
//string was typed to look in the tree
void Suggest(BST *tree, int k, char *text) {
	
	int len = strlen(text);			//size of suggestion input
	int numOfmatchs = 0;					//number of matches in tree
	BSTNode *temp;					//pointer to subtree
	BSTValue *value;				//pointer to 1d array of struct

	temp = BSTSearchSuggest(tree, text, len);     //call to find parent of subtree
	
	if (temp != NULL) {				//if temp == NULL no matches was found do not execute 
		
		BST *subTree = BSTCreate();		//"create" new sub tree to re use written function 
		subTree->Root = temp;			//root will point to node with matching key root of the tree
		subTree->Count = BSTCount(subTree);	//count how many nodes in a subtree
		numOfmatchs = BSTCountSuggested(subTree, text, len);	//count matches in sub treee

		//info about sub tree
		printf("** [Sub-tree root:  (%s,%lld)]\n", subTree->Root->Key, subTree->Root->Value.weight);
		printf("** [Sub-tree count: %d]\n", subTree->Count);		
		printf("** [Num matches:    %d]\n", numOfmatchs);

		value = BSTStoreToArray(subTree, numOfmatchs, text);		//storing matches into array of struct
		
		SelectionSort(value, numOfmatchs);		//call to sort array by weigth

		printMatches(value, k, numOfmatchs);

		//freeTree(subTree);
	}//end if...

	else
		printf("**No suggestions...\n");

}//end suggest...

void _FreeTree(BSTNode *root) {
	if (root == NULL) {
		 return;
	}
	else {
		_FreeTree(root->Left);
		
		_FreeTree(root->Right);
		free(root->Value.name);
		free(root);
	}
}

void freeTree(BST *tree) {
	_FreeTree(tree->Root); 
}



//void _FreeTree(BSTNode *root) {
//	if (root == NULL) {
//		return;
//	}
//	else {
//		_FreeTree(root->Left);
//
//		_FreeTree(root->Right);
//		free(root->Value.name);
//		free(root);
//	}
//}
//
//void freeTree(BST *tree) {
//	_FreeTree(tree->Root);
//	free(tree);
//}