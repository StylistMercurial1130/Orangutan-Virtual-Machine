#include <stdio.h>
#include "vm.h"
#include "system.h"
#include "errors.h"
#include "tools.h"


virtual_machine machine = {.program_counter = 0 , .stack_position = -1};

instruction _inst_list [] = {

    {.instruction_type = INSTRUCTION_TYPE_PUSH, .operand = 2},
    {.instruction_type = INSTRUCTION_TYPE_PUSH , .operand = 1}

};

void instruction_to_string(instruction inst){

    switch(inst.instruction_type){

        case INSTRUCTION_TYPE_PUSH : printf("PUSH %d \n",inst.operand);
        break;
        case INSTRUCTION_TYPE_POP : printf("POP \n",inst.instruction_type);
        break;
    }

}

int vm_main() {

    printf(
        "Virtual Machine \n"
        "virtual machine running \n"
    );

    size_t size_of_inst_list = sizeof(_inst_list) / sizeof(_inst_list[0]);

    for(int i = machine.program_counter;i < size_of_inst_list;i++){

        machine.current_instruction = _inst_list[i];
        program_errors err = execute(&machine);

        print_stack(0,machine.stack_position,machine.stack);


    }

}
