/*main.cpp*/

//
// Auto-complete using a binary search tree.
//
// Artur Wojcik
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project 03
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "bst.h"





//
// skipRestOfInput:
//
// Inputs and discards the remainder of the current line for the 
// given input stream, including the EOL character(s).
//
void skipRestOfInput(FILE *stream)
{
	char restOfLine[256];
	int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);

	fgets(restOfLine, rolLength, stream);
}

//
// getFileName: inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
//
char *getFileName()
{
	char filename[512];
	int  fnsize = sizeof(filename) / sizeof(filename[0]);

	// input filename from the keyboard:
	fgets(filename, fnsize, stdin);
	filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):

												 // make sure filename exists and can be opened:
	FILE *infile = fopen(filename, "r");
	if (infile == NULL)
	{
		printf("**Error: unable to open '%s'\n\n", filename);
		exit(-1);
	}

	fclose(infile);

	// duplicate and return filename:
	char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
	strcpy(s, filename);

	return s;
}
//BSTValue _getpop(BSTNode *root, BSTKey key) {
//	BSTValue temp;
//	if (root == NULL)
//		return temp;
//	if (root->Key == key)
//		return root->Value;
//	else {
//		temp=_getpop(root->Left, key);
//		temp=_getpop(root->Right, key);
//	}
//	return temp;
//}
//
//BSTValue getpop(BST *tree, BSTKey key) {
//	return _getpop(tree->Root, key);
//}


int main()
{
	char *filename;
	char  cmd[64];
	char  text[512];


	printf("** Starting Autocomplete **\n");

	filename = getFileName();
  
	BST *tree = BSTCreate();//cal to creat *tree
	openFile(filename, tree);
	
	//
	// now interact with user:
	//
	printf("** Ready **\n");

	scanf("%s", cmd);
	// BSTValue val; 
	//val = getpop(tree, cmd);

	while (strcmp(cmd, "exit") != 0)
	{

		if (strcmp(cmd, "stats") == 0)
		{
			printf("**Tree count:  %d\n", tree->Count);
			printf("**Tree Height: %d\n", BSTHeight(tree));
		}

		else if (strcmp(cmd, "add") == 0)
		{
			long long weight;
			char      part2[512];
			int       part2size = sizeof(part2) / sizeof(part2[0]);
			BSTValue value; 
			BSTKey key; 


			//
			// add weight text
			//
			scanf("%lld %s", &weight, text);
			fgets(part2, part2size, stdin);
			part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
			strcat(text, part2);

			value.name = (char*)malloc((strlen(text) + 1) * sizeof(char)); 
			strcpy(value.name, text); 
			value.weight = weight; 
			key = value.name;
				
			int newEntry = BSTInsert(tree, key, value); 
			
			if (newEntry == 1) {
				printf("**Added\n");
			}
			else 
				printf("**Not added...\n");
			
		}
		else if (strcmp(cmd, "find") == 0)
		{
			char part2[512];
			int  part2size = sizeof(part2) / sizeof(part2[0]);

			
		//	 find text
			
			scanf("%s", text);
			fgets(part2, part2size, stdin);
			part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
			strcat(text, part2);

			BSTNode *founded = BSTSearch(tree, text);

			if (founded == NULL)
				printf("**Not found...\n");
			else
				printf("%s: %lld\n", founded->Key, founded->Value.weight);

		}
		else if (strcmp(cmd, "suggest") == 0)
		{
			int  k;
			char part2[512];
			int  part2size = sizeof(part2) / sizeof(part2[0]);

			//
			// suggest k text
			//
			scanf("%d %s", &k, text);
			fgets(part2, part2size, stdin);
			part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
			strcat(text, part2);
			
			Suggest(tree, k, text); 
			
		}
		else
		{
			printf("**unknown cmd, try again...\n");
		}

		scanf("%s", cmd);
	}

	printf("** Done **\n");
	freeTree(tree);
	free(filename);

	getchar();

	
	return 0;
}