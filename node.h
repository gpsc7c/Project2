/*
 * node.h
 *
 *  Created on: Jan 20, 2024
 *      Author: nvfer
 */
#include <stdlib.h>
#include <stdio.h>
#include "ttoken.h"
#ifndef NODE_H_
//definition of trinary tree node w/ center as mid
#define NODE_H_
char nonterms[28][11] = {"TERMINAL", "<program>", "<func>", "<block>", "<vars>", "<facvars>", "<expr>", "<N>", "<N1>", "<A>", "<M>", "<R>", "<stats>", "<mStat>", "<stat>", "<in>", "<out>", "<if>", "<pick>", "<pickbody>", "<loop1>", "<loop2>", "<assign>", "<RBracket>", "<RTriplet>", "<R0>", "<label>", "<goto>"};
typedef struct title{
	char nonterm[11] ;
}title;
typedef struct node{
	Ttoken* tk;
	title tTitle;
	struct node* one;
	struct node* two;
	struct node* three;
	struct node* four;
}node;



#endif /* NODE_H_ */
