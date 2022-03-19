#include "file.h"
#include <string.h>
#include <stdio.h>


int file_checker(const char * file){
    
    const char* file_extension = "orangutan";
    int index = -1;

    size_t str_size = sizeof(file) / sizeof(file[0]);
    
    for(int i = 0;i < str_size;i++){
        if(file[i] == '.'){
            index = i;
            break; 
        }
    }
    
    if(index == -1) return index;

    int file_extenstion_character_window = 0;
    for(int i = index + 1;i < str_size;i++)
        if(file[i] != file_extension[file_extenstion_character_window]) return -1;

    return 1;

}