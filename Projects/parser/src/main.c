#include "file_handler.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    struct stat st;
    stat(argv[1], &st);
    char* str = load_c_file(argv[1]);
    remove_string(str,st.st_size);
    printf("%s\n",str);
}
