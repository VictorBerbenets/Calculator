
#include "..//descend.h"
#include "..//Validator.h"
#include "..//colors.h"
#include <sys/stat.h>
#include <sys/types.h>


size_t GetFileSize (const char *file) { 
    
    Validator(!file, "invalid file name", exit(EXIT_FAILURE););

    struct stat buf = {};
    if (stat(file, &buf)) {

        fprintf(stderr, "\n" Red "error" Gray "!!!\nFile <%s>: in function <%s>,  in line '%d' - error in function \"stat\"\n\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
        return -1;
    }
    return buf.st_size;
}