#include <stdio.h>
#include "vm.h"
#include "file.h"

int main(int argc, char ** argv){

    if(argc == 1){

        printf(
        "ora-vm v0.0.1 (2022-2023)" 
        "development \n"
        "ora-vm error : file not specified \n"
        "usage :  ora-vm <file_name> \n");

        return 0;

    }
    
    int result = file_checker(argv[1]);

    if(result == -1){
        
        printf(
        "ora-vm v0.0.1 (2022-2023) development \n"
        "ora-vm error : file is not of the type *.orangutan \n");

        return 0;

    }

    vm_main();

    return 0;

}