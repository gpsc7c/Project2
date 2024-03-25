/*
 * tree.h
 *
 *  Created on: Jan 20, 2024
 *      Author: Greg
 */
#ifndef TREE_H_
#define TREE_H_
#include "node.h"
#include <stdio.h>
#include <string.h>
char nonterms[28][11] = {"TERMINAL", "<program>", "<func>", "<block>", "<vars>", "<facvars>", "<expr>", "<N>", "<N1>", "<A>", "<M>", "<R>", "<stats>", "<mStat>", "<stat>", "<in>", "<out>", "<if>", "<pick>", "<pickbody>", "<loop1>", "<loop2>", "<assign>", "<RBracket>", "<RTriplet>", "<R0>", "<label>", "<goto>"};

struct node* newTermNode(Ttoken* tk){ // Allocate memory for new node
    	 node* nNode
        	= (struct node*)malloc(sizeof(node));
	int i;
	int j;
	nNode->tk = (Ttoken*)malloc(sizeof(Ttoken));
    	//assign title
    	nNode->tk->ID = tk->ID;
	for(j = 0; j < 9; j++){
    		nNode->tk->tokenInstance[j] = tk->tokenInstance[j];
	}
    	nNode->tk->row = tk->row;
    	nNode->tk->column = tk->column;
	
	for(i = 0; i < strlen(nonterms[0]); i++){
    		nNode->tTitle.nonterm[i] = nonterms[0][i];
	}
	for(; i <=10; i++){
    		nNode->tTitle.nonterm[10] = '\0';
	}


    	//initialize children as NULL
	nNode->one = NULL;
    	nNode->two = NULL;
    	nNode->three = NULL;
	nNode->four = NULL;
    	return nNode;
}
struct node* newNode(char* nonTerms){ // Allocate memory for new node
    	node* nNode
        	= (struct node*)malloc(sizeof(struct node));
	int i;
    	//assign title
    	nNode->tk = NULL;
	for(i = 0; i < 10; i++){
    		nNode->tTitle.nonterm[i] = nonTerms[i];
	}
    	nNode->tTitle.nonterm[10] = '\0';
    	//initialize children as NULL
	nNode->one = NULL;
    	nNode->two = NULL;
    	nNode->three = NULL;
	nNode->four = NULL;
    	return nNode;
}
#ifndef bool
typedef enum { false, true } bool;
#endif
void printPreOrder(struct node* dataNode, int depth){
	
	if(dataNode == NULL){
		return;
	}
	int i;	
	for(i = 0; i < depth; i++){
		fprintf(stdout, "  ");
	}
	fprintf(stdout, "%s\n", dataNode->tTitle.nonterm);
	printPreOrder(dataNode->one, depth+1);
	printPreOrder(dataNode->two, depth+1);
	printPreOrder(dataNode->three, depth+1);
	printPreOrder(dataNode->four, depth+1);
}
void deleteTree(struct node* dataNode){
	if(dataNode == NULL){
		fprintf(stderr, "\nERROR: tree.h: deleteTree: tree does not exist\n"); 
		return;
	}
	if(dataNode->one != NULL){
		deleteTree(dataNode->one);
	}
	if(dataNode->two != NULL){
		deleteTree(dataNode->two);
	}
	if(dataNode->three != NULL){
		deleteTree(dataNode->three);
	}
	if(dataNode->four != NULL){
		deleteTree(dataNode->four);
	}
	free(dataNode->tTitle.nonterm);
	if(dataNode->tk != NULL){
		free(dataNode->tk->tokenInstance);
		free(dataNode->tk);
	}
	free(dataNode);
}
/*
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
*/
#endif
