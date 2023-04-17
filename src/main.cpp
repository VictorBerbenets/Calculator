#include "..//descend.h"


int main (int argc, char** argv) {
    
    if (argc > 2) {
        printf("Too many file names, there can be only one:)\n");
        return -1;
    }    

    char* save_alloc_addr = GetData(argv[1]);
    char* string = save_alloc_addr;

    printf("( %s ) = %lg\n", save_alloc_addr, GetG(&string));

    free(save_alloc_addr);
    return 0;
}
