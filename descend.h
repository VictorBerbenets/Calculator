#ifndef recursive_descend
#define recursive_descend

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef double elem_t;
const int MaxFuncSize = 100;

typedef struct {
    elem_t data   = 0;
    int err_flag  = 0;
}value;

typedef struct {
    const char func_name[MaxFuncSize];
    int func_id;
} FuncInfo;

enum FUNCTIONS {
    SIN    = 0,
    COS    = 1,
    TG     = 2,
    CTG    = 3,
    SH     = 4,
    CH     = 5,
    TH     = 6,
    CTH    = 7,
    ARCSIN = 8,
    ARCCOS = 9,
    ARCTG  = 10,
    ARCCTG = 11,
    EXP    = 12,
    LN     = 13,
};

enum Errors {
    DIVISION_BY_ZERO           = 1,
    MISSING_CLOSE_BRACKET      = 2,
    UNEXPECTED_SYMBOL          = 3,
    INVALID_DATA               = 4,
    INVALID_FUNCTION_NAME_SIZE = 5,
};

elem_t GetG(char** string);
value  GetE(char** string);
value  GetT(char** string);
value  GetS(char** string);
value  GetP(char** string);
value  GetF(char** string);
value  GetN(char** string);

void SkipSpaces(char** string);

char* GetData (char *file);

int IsEqual(elem_t num1, elem_t num2);

void PrintError(int err_id, char* string);

int GetFuncId(char* func_name);

elem_t CalculateFunc(elem_t value, int func_id);

#endif