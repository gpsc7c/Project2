#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "scanner.h"
#include "langscan.h"
#include "ttoken.h"
#include "parser.h"
//enum tokenTypes{IDTK, INTTK, ASSIGNTK, GREATTK, LESSTK, ISEQUALTK, NOTEQUALTK, COLONTK, COLONEQLTK, PLUSTK, MINUSTK, MULTIPLYTK, DIVIDETK, EXPONTK, DOTTK, OPENPARENTK, CLOSEPARENTK, COMMATK, OPENCURLTK, CLOSECURLTK, SEMICOLONTK, OPENSQUARETK, CLOSESQUARETK, ORTK, ANDTK, STARTTK, STOPTK, WHILETK, REPEATTK, UNTILTK, LABELTK, RETURNTK, CINTK, COUTTK, TAPETK, JUMPTK, IFTK, THENTK, PICKTK, CREATETK, SETTK, FUNCTK, EOFTK};
#ifndef PARSER_C
#define PARSER_C
void error(){
	fprintf(stderr, "\nAn error has occurred.\n");
	exit(-1);
}
void R0(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	if(tk->ID == GREATTK){
		*tk = scanner(file, c, row, col);	
		return;
	}
	if(tk->ID == LESSTK){
		*tk = scanner(file, c, row, col);	
		return;
	}
	if(tk->ID == ISEQUALTK){
		*tk = scanner(file, c, row, col);	
		return;
	}
	if(tk->ID == NOTEQUALTK){
		*tk = scanner(file, c, row, col);	
		return;
	}
	if(tk->ID == DOTTK){
		*tk = scanner(file, c, row, col);	
		if(tk->ID == DOTTK){
			*tk = scanner(file, c, row, col);	
			if(tk->ID == DOTTK){
				*tk = scanner(file, c, row, col);	
				return;
			}
		}
	}
	error();
	return;
}
void RTriplet(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	expr(tk, file, c, row, col);
	R0(tk, file, c, row, col);
	expr(tk, file, c, row, col);
	return;	
}
void RBrackets(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	if(tk->ID == OPENSQUARETK){
		*tk = scanner(file, c, row, col);	
		RTriplet(tk, file, c, row, col);
		if(tk->ID == CLOSESQUARETK){
			*tk = scanner(file, c, row, col);
			return;
		}
		error();
		return;
	}
}

void gotochk(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	if(tk->ID == JUMPTK){
		*tk = scanner(file, c, row, col);	
		if(tk->ID == IDTK){
			*tk = scanner(file, c, row, col);	
			*found = true;
			return;
		}
		error();
		return;
	}
	return;
}
void label(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	if(tk->ID == LABELTK){
		*tk = scanner(file, c, row, col);	
		if(tk->ID == IDTK){
			*tk = scanner(file, c, row, col);	
			*found = true;
			return;
		}
		error();
		return;
	}
	return;
}
void assign(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	bool set;
	if(tk->ID == SETTK){
		*tk = scanner(file, c, row, col);
		set = true;
	}
	if(tk->ID == IDTK){
		*tk = scanner(file, c, row, col);
		if(tk->ID == ASSIGNTK){
			*tk = scanner(file, c, row, col);
			expr(tk, file, c, row, col);
			*found = true;
			return;
		}
		error();
		return;
	}
	if(set == true){
		error();
		return;
	}
	return;
}
void loop2(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	if(tk->ID == REPEATTK){
		*tk = scanner(file, c, row, col);
		stat(tk, file, c, row, col);
		if(tk->ID == UNTILTK){
			*tk = scanner(file, c, row, col);
			RBrackets(tk, file, c, row, col);
			*found = true;
			return;
		}
		error();
	}
	return;	
}
void loop1(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	if(tk->ID == WHILETK){
		*tk = scanner(file, c, row, col);
		RBrackets(tk, file, c, row, col);
		stat(tk, file, c, row, col);
		*found = true;
	}
	return;
}
void pickbody(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	stat(tk, file, c, row, col);
	if(tk->ID == COLONTK){
		*tk = scanner(file, c, row, col);	
		stat(tk, file, c, row, col);
		return;
	}
	error();
	return;
}
void pick(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	if(tk->ID == PICKTK){
		*tk = scanner(file, c, row, col);	
		expr(tk, file, c, row, col);
		pickbody(tk, file, c, row, col);
		*found = true;
		return;
	}
	return;
}
void ifchk(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	if(tk->ID == IFTK){
		*tk = scanner(file, c, row, col);	
		RBrackets(tk, file, c, row, col);
		if(tk->ID == THENTK){
			*tk = scanner(file, c, row, col);
			stat(tk, file, c, row, col);
			*found = true;
			return;
		}
	}
	return;
}
void out(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	if(tk->ID == COUTTK){
		*tk = scanner(file, c, row, col);	
		if(tk->ID == IDTK){
			*tk = scanner(file, c, row, col);	
			*found = true;
			return;
		}
		error();
		return;
	}
	return;
}
void in(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found){
	if(tk->ID == CINTK){
		*tk = scanner(file, c, row, col);	
		if(tk->ID == IDTK){
			*tk = scanner(file, c, row, col);
			*found = true;
			return;
		}
		error();
		return;
	}
	return;
}
void stat(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	bool* found = malloc(sizeof(bool));
	*found = false;
	if(tk->ID != OPENCURLTK){
		in(tk,file,c,row,col,found);
		if(!*found){
			out(tk,file,c,row,col,found);
		}
		if(!*found){
			ifchk(tk,file,c,row,col,found);
		}
		if(!*found){
			pick(tk,file,c,row,col,found);
		}
		if(!*found){
			loop1(tk,file,c,row,col,found);
		}
		if(!*found){
			loop2(tk,file,c,row,col,found);
		}
		if(!*found){
			assign(tk,file,c,row,col,found);
		}
		if(!*found){
			label(tk,file,c,row,col,found);
		}
		if(!*found){
			gotochk(tk,file,c,row,col,found);
		}
		if(tk->ID == SEMICOLONTK){
			*tk = scanner(file, c, row, col);
			return;
		}
		
		error();
		return;
	}
	block(tk, file, c, row, col);
	return;
}
void mStat(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	if(tk->ID == CINTK || tk->ID == COUTTK ||tk->ID == OPENCURLTK ||tk->ID == IFTK ||tk->ID == WHILETK ||tk->ID == REPEATTK ||tk->ID == SETTK ||tk->ID == JUMPTK ||tk->ID == LABELTK ||tk->ID == PICKTK){		
		stat(tk, file, c, row, col);
	}
	return;
}
void stats(Ttoken* tk, FILE* file, char* c, int* row, int* col){	
	stat(tk, file, c, row, col);
	mStat(tk, file, c, row, col);
	return;
}
void R(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	if(tk->ID == OPENPARENTK){
		*tk = scanner(file, c, row, col);
		expr(tk, file, c, row, col);
		if(tk->ID == CLOSEPARENTK){
			*tk = scanner(file, c, row, col);
			return;
		}
		error();
		return;
	}
	if(tk->ID == IDTK){
		*tk = scanner(file, c, row, col);
		return;
	}
	if(tk->ID == INTTK){
		*tk = scanner(file, c, row, col);
		return;
	}
	error();
	return;
}
void M(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	if(tk->ID == EXPONTK){
		*tk = scanner(file, c, row, col);
		M(tk, file, c, row, col);
		return;
	}
	R(tk, file, c, row, col);
	return;
}

void A(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	M(tk, file, c, row, col);
	if(tk->ID == MULTIPLYTK){
		*tk = scanner(file, c, row, col);
		A(tk, file, c, row, col);
	}
	return;
}
void N1(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	if(tk->ID == DIVIDETK){
		*tk = scanner(file, c, row, col);
		A(tk, file, c, row, col);
		N1(tk, file, c, row, col);
		return;
	}
	if(tk->ID == MINUSTK){
		*tk = scanner(file, c, row, col);
		A(tk, file, c, row, col);
		N1(tk, file, c, row, col);
		return;
	}
	return;
}
void N(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	A(tk, file, c, row, col);
	N1(tk, file, c, row, col);
	return;
}
void expr(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	N(tk, file, c, row, col);
	if(tk->ID == MINUSTK){
		*tk = scanner(file, c, row, col);
		expr(tk, file, c, row, col);
	}
	return;
}
//factorvars is complete
void factorvars(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* coleql){
	if(tk->ID == CREATETK){
		*tk = scanner(file, c, row, col);
		if(tk->ID == IDTK){
			*tk = scanner(file, c, row, col);
			if(tk->ID == COLONEQLTK){
				*tk = scanner(file, c, row, col);
				*coleql = true;
				return;
			}
			if(tk->ID ==SEMICOLONTK){
				*tk = scanner(file, c, row, col);
				return;	
			}
		}
	}
	error();
	return;
}
//vars is complete
void vars(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	bool* coleql = malloc(sizeof(bool));
	*coleql = false;
	if(tk->ID == CREATETK){
		factorvars(tk, file, c, row, col, coleql);
		if(*coleql == false){
			//vars(tk, file, c, row, col);
			return;
		}
		if(tk->ID == INTTK){
			*tk = scanner(file, c, row, col);
			if(tk->ID == SEMICOLONTK){
				*tk = scanner(file, c, row, col);
				vars(tk, file, c, row, col);
			}
		}
	}
	return;
}

void block(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	if(tk->ID != OPENCURLTK){
		error();
		return;
	}
	*tk = scanner(file, c, row, col);
	vars(tk,file,c,row,col);
	stats(tk,file,c,row,col);
	if(tk->ID != CLOSECURLTK){
		error();
		return;
	}	
	*tk = scanner(file, c, row, col);
	return;
}
void func(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	if(tk->ID == FUNCTK){	
		*tk = scanner(file, c, row, col);
		if(tk->ID == IDTK){
			*tk = scanner(file, c, row, col);
			block(tk, file, c, row, col);
			return;
		}
	}
	error();
	return;
}
//Identifies BNF for program
void program(Ttoken* tk, FILE* file, char* c, int* row, int* col){
	vars(tk,file,c,row,col);
	if(tk->ID == TAPETK){
		*tk = scanner(file, c, row, col);
		if(tk->ID == FUNCTK){
			func(tk,file,c,row,col);
		}
		block(tk,file,c,row,col);
		return;
	}
	error();
	return;
}

void parser(FILE* file){
	//create malloc'd variables to send to other functions
	int *col = malloc(sizeof(int));
	int *row = malloc(sizeof(int));
	Ttoken* tk = malloc(sizeof(Ttoken));
	*col = 0;
	*row = 1;
	char c[2] = {'\0','\0'};		//character iterator
	*tk = scanner(file, c, row, col);
	program(tk, file, c, row, col);
}
#endif
