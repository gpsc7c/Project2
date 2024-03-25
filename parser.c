#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "scanner.h"
#include "langscan.h"
#include "ttoken.h"
#include "parser.h"
#include "node.h"
#include "tree.h"

//enum tokenTypes{IDTK, INTTK, ASSIGNTK, GREATTK, LESSTK, ISEQUALTK, NOTEQUALTK, COLONTK, COLONEQLTK, PLUSTK, MINUSTK, MULTIPLYTK, DIVIDETK, EXPONTK, DOTTK, OPENPARENTK, CLOSEPARENTK, COMMATK, OPENCURLTK, CLOSECURLTK, SEMICOLONTK, OPENSQUARETK, CLOSESQUARETK, ORTK, ANDTK, STARTTK, STOPTK, WHILETK, REPEATTK, UNTILTK, LABELTK, RETURNTK, CINTK, COUTTK, TAPETK, JUMPTK, IFTK, THENTK, PICKTK, CREATETK, SETTK, FUNCTK, EOFTK};
#ifndef PARSER_C
#define PARSER_C
void error(){
	fprintf(stderr, "\nAn error has occurred.\n");
	exit(-1);
}
node* R0(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[25]);
	if(tk->ID == GREATTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		return nNode;
	}
	if(tk->ID == LESSTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		return nNode;
	}
	if(tk->ID == ISEQUALTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		return nNode;
	}
	if(tk->ID == NOTEQUALTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		return nNode;
	}
	if(tk->ID == DOTTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		if(tk->ID == DOTTK){
			nNode->two = newTermNode(tk);
			*tk = scanner(file, c, row, col);	
			if(tk->ID == DOTTK){
				nNode->three = newTermNode(tk);
				*tk = scanner(file, c, row, col);	
				return nNode;
			}
		}
	}
	error();
	return NULL;
}
node* RTriplet(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[24]);
	nNode->one = expr(tk, file, c, row, col);
	nNode->two = R0(tk, file, c, row, col);
	nNode->three = expr(tk, file, c, row, col);
	return nNode;	
}
node* RBrackets(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[23]);
	if(tk->ID == OPENSQUARETK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		nNode->two = RTriplet(tk, file, c, row, col);
		if(tk->ID == CLOSESQUARETK){
			nNode->three = newTermNode(tk);
			*tk = scanner(file, c, row, col);
			return nNode;
		}
	}
	error();
	return NULL;
}

node* gotochk(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	node* nNode = newNode(nonterms[27]);
	if(tk->ID == JUMPTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		if(tk->ID == IDTK){
			nNode->two = newTermNode(tk);
			*tk = scanner(file, c, row, col);	
			*found = true;
			return nNode;
		}
		error();
		return NULL;
	}
	return nNode;
}
node* label(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	node* nNode = newNode(nonterms[26]);
	if(tk->ID == LABELTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		if(tk->ID == IDTK){
			nNode->two = newTermNode(tk);
			*tk = scanner(file, c, row, col);	
			*found = true;
			return nNode;
		}
		error();
		return NULL;
	}
	return nNode;
}
node* assign(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	node* nNode = newNode(nonterms[22]);
	bool set = false;
	if(tk->ID == SETTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		set = true;
	}
	if(tk->ID == IDTK){
		nNode->two = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		if(tk->ID == ASSIGNTK){
			nNode->three = newTermNode(tk);
			*tk = scanner(file, c, row, col);
			nNode->four = expr(tk, file, c, row, col);
			*found = true;
			return nNode;
		}
		error();
	}
	if(set == true){
		error();
	}
	return NULL;
}
node* loop2(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	node* nNode = newNode(nonterms[21]);
	if(tk->ID == REPEATTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		nNode->two = stat(tk, file, c, row, col);
		if(tk->ID == UNTILTK){
			nNode->three = newTermNode(tk);
			*tk = scanner(file, c, row, col);
			nNode->four = RBrackets(tk, file, c, row, col);
			*found = true;
			return nNode;
		}
		error();
	}
	return NULL;	
}
node* loop1(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	node* nNode = newNode(nonterms[20]);
	if(tk->ID == WHILETK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		nNode->two = RBrackets(tk, file, c, row, col);
		nNode->three = stat(tk, file, c, row, col);
		*found = true;
		return nNode;
	}
	return NULL;
}
node* pickbody(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[19]);
	nNode->one = stat(tk, file, c, row, col);
	if(tk->ID == COLONTK){
		nNode->two = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		nNode->three = stat(tk, file, c, row, col);
		return nNode;
	}
	error();
	return NULL;
}
node* pick(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	node* nNode = newNode(nonterms[18]);
	if(tk->ID == PICKTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		nNode->two = expr(tk, file, c, row, col);
		nNode->three = pickbody(tk, file, c, row, col);
		*found = true;
		return nNode;
	}
	return NULL;
}
node* ifchk(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	node* nNode = newNode(nonterms[17]);
	if(tk->ID == IFTK){
		nNode->one = newTermNode(tk);	
		*tk = scanner(file, c, row, col);	
		nNode->two = RBrackets(tk, file, c, row, col);
		if(tk->ID == THENTK){
			nNode->three = newTermNode(tk);
			*tk = scanner(file, c, row, col);
			nNode->four = stat(tk, file, c, row, col);
			*found = true;
			return nNode;
		}	
		error();
		return NULL;
	}
	return NULL;
}
node* out(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	node* nNode = newNode(nonterms[16]);
	if(tk->ID == COUTTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		if(tk->ID == IDTK){
			nNode->two = newTermNode(tk);
			*tk = scanner(file, c, row, col);	
			*found = true;
			return nNode;
		}
		error();
		return NULL;
	}
	return NULL;
}
node* in(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	node* nNode = newNode(nonterms[15]);
	if(tk->ID == CINTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);	
		if(tk->ID == IDTK){
			nNode->two = newTermNode(tk);
			*tk = scanner(file, c, row, col);
			*found = true;
			return nNode;
		}
		error();
		return NULL;
	}
	return NULL;
}
node* stat(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[14]);
	bool* found = malloc(sizeof(bool));
	*found = false;
	if(tk->ID != OPENCURLTK){
		nNode->one = in(tk,file,c,row,col,found);
		if(!*found){
			nNode->one = out(tk,file,c,row,col,found);
		}
		if(!*found){
			nNode->one = ifchk(tk,file,c,row,col,found);
		}
		if(!*found){
			nNode->one = pick(tk,file,c,row,col,found);
		}
		if(!*found){
			nNode->one = loop1(tk,file,c,row,col,found);
		}
		if(!*found){
			nNode->one = loop2(tk,file,c,row,col,found);
		}
		if(!*found){
			nNode->one = assign(tk,file,c,row,col,found);
		}
		if(!*found){
			nNode->one = label(tk,file,c,row,col,found);
		}
		if(!*found){
			nNode->one = gotochk(tk,file,c,row,col,found);
		}
		if(tk->ID == SEMICOLONTK){
			nNode->two = newTermNode(tk);
			*tk = scanner(file, c, row, col);
			return nNode;
		}
		
		error();
		return NULL;
	}
	nNode->one = block(tk, file, c, row, col);
	return nNode;
}
node* mStat(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[13]);
	if(tk->ID == CINTK || tk->ID == COUTTK ||tk->ID == OPENCURLTK ||tk->ID == IFTK ||tk->ID == WHILETK ||tk->ID == REPEATTK ||tk->ID == SETTK ||tk->ID == JUMPTK ||tk->ID == LABELTK ||tk->ID == PICKTK){		
		nNode->one = stat(tk, file, c, row, col);
		nNode->two = mStat(tk, file, c, row, col);
	}
	return nNode;
}
node* stats(Ttoken* tk, FILE* file, char* c, int* row, int* col){	
	node* nNode = newNode(nonterms[12]);
	nNode->one = stat(tk, file, c, row, col);
	nNode->two = mStat(tk, file, c, row, col);
	return nNode;
}
node* R(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[11]);
	if(tk->ID == OPENPARENTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		nNode->two = expr(tk, file, c, row, col);
		if(tk->ID == CLOSEPARENTK){
			nNode->three = newTermNode(tk);
			*tk = scanner(file, c, row, col);
			return nNode;
		}
		error();
		return NULL;
	}
	if(tk->ID == IDTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		return nNode;
	}
	if(tk->ID == INTTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		return nNode;
	}
	error();
	return NULL;
}
node* M(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[10]);
	if(tk->ID == EXPONTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		nNode->two = M(tk, file, c, row, col);
		return nNode;
	}
	nNode->one = R(tk, file, c, row, col);
	return nNode;
}

node* A(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[9]);
	nNode->one = M(tk, file, c, row, col);
	if(tk->ID == MULTIPLYTK){
		nNode->two = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		nNode->three = A(tk, file, c, row, col);
	}
	return nNode;
}
node* N1(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[8]);
	if(tk->ID == DIVIDETK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		nNode->two = A(tk, file, c, row, col);
		nNode->three = N1(tk, file, c, row, col);
		return nNode;
	}
	if(tk->ID == MINUSTK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		nNode->two = A(tk, file, c, row, col);
		nNode->three = N1(tk, file, c, row, col);
		return nNode;
	}
	return nNode;
}
node* N(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[7]);
	nNode->one = A(tk, file, c, row, col);
	nNode->two = N1(tk, file, c, row, col);
	return nNode;
}
node* expr(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[6]);
	nNode-> one = N(tk, file, c, row, col);
	if(tk->ID == MINUSTK){
		nNode->two = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		nNode->three = expr(tk, file, c, row, col);
	}
	return nNode;
}
//factorvars is complete
node* facvars(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* coleql){
	node* nNode = newNode(nonterms[5]);
	if(tk->ID == CREATETK){
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		if(tk->ID == IDTK){
			nNode->two = newTermNode(tk);
			*tk = scanner(file, c, row, col);
			if(tk->ID == COLONEQLTK){
				nNode->three = newTermNode(tk);
				*tk = scanner(file, c, row, col);
				*coleql = true;
				return nNode;
			}
			if(tk->ID ==SEMICOLONTK){
				nNode->three = newTermNode(tk);
				*tk = scanner(file, c, row, col);
				return nNode;	
			}
		}
	}
	error();
	return NULL;
}
//vars is complete
node* vars(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[4]);
	bool* coleql = malloc(sizeof(bool));
	*coleql = false;
	if(tk->ID == CREATETK){
		nNode->one = facvars(tk, file, c, row, col, coleql);
		if(*coleql == false){
			return nNode;
		}
		if(tk->ID == INTTK){
			nNode->two = newTermNode(tk);
			*tk = scanner(file, c, row, col);
			if(tk->ID == SEMICOLONTK){
				nNode->three = newTermNode(tk);
				*tk = scanner(file, c, row, col);
				vars(tk, file, c, row, col);
				return nNode;
			}
		}
		error();
		return NULL;
	}
	return nNode;
}

node* block(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[3]);
	if(tk->ID != OPENCURLTK){
		error();
		return NULL;
	}
	nNode->one = newTermNode(tk);
	*tk = scanner(file, c, row, col);
	nNode->two = vars(tk,file,c,row,col);
	nNode->three = stats(tk,file,c,row,col);
	if(tk->ID != CLOSECURLTK){
		error();
		return NULL;
	}
	nNode->four = newTermNode(tk);	
	*tk = scanner(file, c, row, col);
	return nNode;
}
node* func(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* nNode = newNode(nonterms[2]);
	if(tk->ID == FUNCTK){	
		nNode->one = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		if(tk->ID == IDTK){
			nNode->two = newTermNode(tk);
			*tk = scanner(file, c, row, col);
			nNode->three = block(tk, file, c, row, col);
			return nNode;
		}
	}
	error();
	return NULL;
}
//Identifies BNF for program
node* program(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	node* root = newNode(nonterms[1]);
	root->one = vars(tk,file,c,row,col);
	if(tk->ID == TAPETK){
		root->two = newTermNode(tk);
		*tk = scanner(file, c, row, col);
		
		if(tk->ID == FUNCTK){
			root->three = func(tk,file,c,row,col);
			root->four = block(tk,file,c,row,col);
			return root;
		}
		root->three = block(tk,file,c,row,col);
		return root;
	}
	error();
	return NULL;
}

void parser(FILE* file){
	//create malloc'd variables to send to other functions
	int *col = malloc(sizeof(int));
	int *row = malloc(sizeof(int));
	int depth = 0;
	Ttoken* tk = malloc(sizeof(Ttoken));
	*col = 0;
	*row = 1;
	char c[2] = {'\0','\0'};		//character iterator
	node* root;
	*tk = scanner(file, c, row, col);
	root = program(tk, file, c, row, col);
	printPreOrder(root, depth);
}
#endif
