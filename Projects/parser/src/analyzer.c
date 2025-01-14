#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>


char* tokenizer(char* path_to_cfile){
    struct stat file_info;
    FILE* f_ptr = fopen(path_to_cfile, "r");
    int fd = fileno(f_ptr);
    stat(path_to_cfile,&file_info);
    char* c_file = (char*)mmap(
            NULL,
            file_info.st_size,
            PROT_READ,
            MAP_PRIVATE,
            fd,
            0
            );
    char* ctokens = strtok(c_file, " ");
    while(ctokens != NULL){
        
        printf("%s\n",ctokens);
        ctokens = strtok(NULL, " \t\n");
    }
    return ctokens;
}

