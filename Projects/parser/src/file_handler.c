#include "file_handler.h"
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>

#define KEY_COUNT 7

char* load_c_file(const char* path_to_cfile){
    
    struct stat file_info;
    FILE* f_ptr = fopen(path_to_cfile, "r+");
    int fd = fileno(f_ptr);
    stat(path_to_cfile,&file_info);
    char* c_file = (char*)mmap(
            NULL,
            file_info.st_size,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE,
            fd,
            0
            );
    return c_file;
}


char* tokenizer(char* path_to_cfile){
    struct stat file_info;
    FILE* f_ptr = fopen(path_to_cfile, "r+");
    int fd = fileno(f_ptr);
    stat(path_to_cfile,&file_info);
    char* c_file = (char*)mmap(
            NULL,
            file_info.st_size,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE,
            fd,
            0
            );
    char *keywords[KEY_COUNT] = {"int", "printf", "char", "struct", "if", "for","while"};
    int count = 0;
    char* ctokens = strtok(c_file, " ");
    while(ctokens != NULL){
        for(int i = 0; i < KEY_COUNT; i++){
            if (!strcmp(keywords[i], ctokens)){
                count++;
            }
        }
        printf("%s\n",ctokens);
        ctokens = strtok(NULL, " \t\n{}()");
    
    }
    printf("%d\n",count);
    return ctokens;
    
}

void remove_string(char* str, size_t size){
    int i = 0;
    char state;
    while(i < size){
        if(str[i] == '"'){
            switch (state) {
                case 0:{
                    str[i] = '\0';
                    state = 1;
                    i++;           
                }   break;
                case 1:{
                    str[i] = '\0';
                    state = 0;
                    i++;
                }   break;
            }
        }
        else{
            if(state == 0){i++;}else{
                str[i] = '\0';
                i++;
            }
        }
    }
}
