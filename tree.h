/*
 * tree.h
 *
 *  Created on: Jan 20, 2024
 *      Author: Greg
 */
#include "node.h"
#include <stdio.h>
#include <string.h>
#ifndef TREE_H_
#define TREE_H_

struct node* newNode(Ttoken* tk){ // Allocate memory for new node
    	struct node* node
        	= (struct node*)malloc(sizeof(struct node));

    	//assign title
    	node->tk = tk;
	node->title.nonterm = nonterms[0];

    	//initialize children as NULL
	node->one = NULL;
    	node->two = NULL;
    	node->three = NULL;
	node->four = NULL;
    	return (node);
}
struct node* newNode(char* nonterms){ // Allocate memory for new node
    	struct node* node
        	= (struct node*)malloc(sizeof(struct node));

    	//assign title
    	node->tk = NULL;
    	node->title.nonterm = nonterms;

    	//initialize children as NULL
	node->one = NULL;
    	node->two = NULL;
    	node->three = NULL;
	node->four = NULL;
    	return (node);
}
#ifndef bool
typedef enum { false, true } bool;
#endif
#include "node.h"

struct node* insert(char dat, char* data, int dataLength, node* startNode){
	int i = 0;
	//creates a new node by loading up a char array and then putting it in
	if (startNode == NULL){
		char* letterHolder = malloc(sizeof(char) * dataLength);
		for(; i < dataLength; i++){
			letterHolder[i] = data[i];
		}
		startNode = newNode(letterHolder);
	}
	//check if midnode
	else if(startNode->letters[0] == dat || startNode->letters[0] == dat + 32){
		startNode->mid = insert(dat, data, dataLength, startNode->mid);
	}
	//this checks as follows: if both are lowercase is dat later in the alphabet||
	// OR if both are uppercase is dat later in the alphabet
	// OR if letters is lowercase and dat is uppercase and later in the alphabet
	// OR if letters is uppercase and dat is lowercase and later in the alphabet
	else if(( startNode->letters[0] > 95 && startNode->letters[0] < dat)
			|| (dat < 91 && startNode->letters[0] < dat)
			|| (startNode->letters[0] > 95 && dat < 91 && startNode->letters[0] - 32 < dat)
			|| (startNode->letters[0] < 91 && dat > 95 && startNode->letters[0] + 32 < dat)){

			startNode->right = insert(dat, data, dataLength, startNode->right);
	}
	else{
		startNode->left = insert(dat, data, dataLength, startNode->left);
	}
	return startNode;
}

bool lengthCheckPass(char* word, int i){
	if(i > MAX_WORD_LENGTH){
		fprintf(stderr, "too long word encountered," 
			"skipping to prevent buffer overflow\n");
		return false;
	}		
	return true;
}
bool letterCheck(char c, int i){
	if((c > 64 && c < 91) || (c > 96 && c < 123)||(c == 39 && i != 0)){
		return true;
	}
	return false;
}

struct node* kbEntry(struct node* rootNode){
	int c, freeFlag, skipFlag;
	int i = freeFlag = skipFlag = 0;
	char* word = NULL;
	size_t size = 0;
	while ((c = getchar()) != EOF) {
		if(skipFlag == 0 && letterCheck(c, i)){
			word = realloc(word, sizeof(*word)*(size+=16)+1);
			word[i] = c;
			word[i+1] = '\0';
			i++;
		}else if (skipFlag != 0 && !letterCheck(c, i)){
			skipFlag = 0;
		}else if (i > 0 && ((freeFlag = 1))&& skipFlag == 0){
			rootNode= insert(word[0], word, strlen(word), rootNode);
		}
		if(!lengthCheckPass(word, i) && ((freeFlag = 1)) && ((skipFlag = 1))){}
		if(freeFlag != 0){
			size = i = freeFlag = 0;
			free(word);
			word = NULL;
		}
	}
	if(i > 0){
		rootNode = insert(word[0], word, strlen(word), rootNode);
		free(word);
	}
	return rootNode;
}



struct node* fileEntry(char* fname, struct node* rootNode){
	FILE *infp;
	int c, freeFlag, skipFlag;
	int i = freeFlag = skipFlag = 0; 
	char* word = NULL;
	size_t size = 0;

	infp = fopen(fname, "r");
	if(infp == NULL){
		fprintf(stderr, "ERROR: tree.h: File does not exist at "
			"specified location, or can't be opened.\n");
		return NULL;
	}
	while ((c = fgetc(infp)) != EOF) {
		if(skipFlag == 0 && letterCheck(c, i)){
			word = realloc(word, sizeof(*word)*(size+=16)+1);
			word[i] = c;
			word[i+1] = '\0';
			i++;
		}else if (skipFlag != 0 && !letterCheck(c, i)){
			skipFlag = 0;
		}else if (i > 0 && ((freeFlag = 1))&& skipFlag == 0){
			rootNode= insert(word[0], word, strlen(word), rootNode);
		}
		if(!lengthCheckPass(word, i) && ((freeFlag = 1)) && ((skipFlag = 1))){}
		if(freeFlag != 0){
			size = i = freeFlag = 0;
			free(word);
			word = NULL;
		}
	}
	if(i > 0){
		rootNode = insert(word[0], word, strlen(word), rootNode);
		free(word);
	}
	return rootNode;
}
void printPreOrder(struct node* dataNode, int depth, char* fName){
	
	if(dataNode == NULL){
		return;
	}
	FILE* pre = fopen(fileName(fName, ".preorder"), "a");
	int i;	
	for(i = 0; i < depth; i++){
		fprintf(pre, "  ");
	}
	fprintf(pre, "%c:%s\n", dataNode->letters[0], dataNode->letters);
	printPreOrder(dataNode->left, depth+1, fName);
	printPreOrder(dataNode->mid, depth+1, fName);
	printPreOrder(dataNode->right, depth+1, fName);
}
void printInOrder(struct node* dataNode, int depth, char* fName){
	if(dataNode == NULL){
		return;
	}
	FILE* in = fopen(fileName(fName, ".inorder"), "a");
	int i;
	printInOrder(dataNode->left, depth+1, fName);
	for(i = 0; i < depth; i++){
		fprintf(in,"  ");
	}
	fprintf(in, "%c:%s\n", dataNode->letters[0], dataNode->letters);
	printInOrder(dataNode->mid, depth+1, fName);
	printInOrder(dataNode->right, depth+1, fName);
}
void printPostOrder(struct node* dataNode, int depth, char* fName){
	if(dataNode == NULL){
		return;
	}
	FILE* post = fopen(fileName(fName, ".postorder"), "a");

	printPostOrder(dataNode->left, depth+1, fName);
	printPostOrder(dataNode->mid, depth+1, fName);
	printPostOrder(dataNode->right, depth+1, fName);
	int i;	
	for(i = 0; i < depth; i++){
		fprintf(post,"  ");
	}
	printf("%c:%s\n", dataNode->letters[0], dataNode->letters);
}
void deleteTree(struct node* dataNode){
	if(dataNode == NULL){
		fprintf(stderr, "\nERROR: tree.h: deleteTree: tree does not exist\n"); 
		return;
	}
	if(dataNode->left != NULL){
		deleteTree(dataNode->left);
	}
	if(dataNode->mid != NULL){
		deleteTree(dataNode->mid);
	}
	if(dataNode->right != NULL){
		deleteTree(dataNode->right);
	}
	free(dataNode->letters);
	free(dataNode);
}
int fileOpener(char* fName, char* suffix){
	char* result = malloc(strlen(fName) + strlen(suffix) + 2);
	
	strcat(result, fName);
	strcat(result, ".");
	strcat(result, suffix);

	FILE* resultFile = fopen(result, "w");

	if(resultFile == NULL){
		fprintf(stderr, "ERROR: Failed to open necessary output files");
		return 1;
	}
	//char* fileType = malloc(strlen(suffix) + 1)
	//fileType
	fprintf(result, "This is the %s file.\n", suffix);
	fclose(resultFile);
	return 0;	
}
char* fileName(char* fName, char* suffix){
	char* result = malloc(strlen(fName) + strlen(suffix) + 1);
	
	strcat(result, fName);
	strcat(result, suffix);

	return result;	
}
#endif
