#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "langscan.h"
#include "ttoken.h"
#ifndef PARSER_H
#define PARSER_H
void error();


void gotochk(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found);
void label(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found);
void R0(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void RTriplet(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void RBrackets(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void assign(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found);
void loop2(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found);
void loop1(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found);
void pickbody(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void pick(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found);
void ifchk(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found);
void out(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found);
void in(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* found);
void stat(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void mStat(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void stats(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void R(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void M(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void A(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void N(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void expr(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void factorvars(Ttoken* tk, FILE* file, char* c, int* row, int* col, bool* coleql);
void vars(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void block(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void func(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void program(Ttoken* tk, FILE* file, char* c, int* row, int* col);
void parser(FILE* file);
#endif
