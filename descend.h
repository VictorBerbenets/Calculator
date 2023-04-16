#ifndef recursive_descend
#define recursive_descend

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


typedef double elem_t;

typedef struct {
    elem_t data   = 0;
    int err_flag  = 0;
}value;

enum Errors {

    DIVISION_BY_ZERO      = 1,
    MISSING_CLOSE_BRACKET = 2,
    UNEXPECTED_SYMBOL     = 3,
};

elem_t GetG();
value  GetE();
value  GetT();
value  GetP();
value  GetN();

void SkipSpaces(const char** string);

char* GetData (const char *file);

int IsEqual(elem_t num1, elem_t num2);

void PrintError(int err_id);
#endif