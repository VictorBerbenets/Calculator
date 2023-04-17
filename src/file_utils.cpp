#include "..//descend.h"
#include "..//Validator.h"
#include "..//colors.h"
#include <sys/stat.h>
#include <sys/types.h>

static const int MAX_FILE_SIZE = 1111;

char* GetData (char *file) { 
    Validator(!file, "invalid file name", exit(EXIT_FAILURE););

    FILE* data_file = fopen(file, "r");

    char* ret_string = (char*) calloc(MAX_FILE_SIZE, sizeof(char));
    fgets(ret_string, MAX_FILE_SIZE, data_file);
    ret_string[strlen(ret_string)] = '\0';
    fclose(data_file);

    return (char*) ret_string;
}