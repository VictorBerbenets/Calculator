#ifndef recursive_descend
#define recursive_descend

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef double elem_t;

typedef struct {
    elem_t data   = 0;
    int err_flag  = 0;
}value;


elem_t GetG();
value  GetE();
value  GetT();
value  GetP();
value  GetN();

void SkipSpaces(const char** string);

size_t GetFileSize (const char *file);

#endif