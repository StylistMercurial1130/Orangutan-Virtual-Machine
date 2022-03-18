#include <stdio.h>
#include "vm.h"
#include "system.h"
#include "errors.h"
#include "tools.h"


virtual_machine machine = {.program_counter = 0 , .stack_position = -1};

instruction _inst_list [] = {

    {.instruction_type = INSTRUCTION_TYPE_PUSH, .operand = 2},
    {.instruction_type = INSTRUCTION_TYPE_PUSH , .operand = 1},
    {.instruction_type = INSTRUCTION_TYPE_ADD , .operand = 0},
    {.instruction_type = INSTRUCTION_SELECT_REGISTER, .operand = 3 },
    {.instruction_type = INSTRUCTION_STORE_REGISTER, .operand = 4},
    {.instruction_type = INSTRUCTION_GREATER_THAN, .operand = 3},
    {.instruction_type = INSTRUCTION_JUMP_GREATER_THAN, .operand = 0}

};

void instruction_to_string(instruction inst){

    switch(inst.instruction_type){

        case INSTRUCTION_TYPE_PUSH : printf("PUSH %d \n",inst.operand);
        break;
        case INSTRUCTION_TYPE_POP : printf("POP \n");
        break;
        case INSTRUCTION_TYPE_ADD : printf("ADD \n");
        break; 
        case INSTRUCTION_TYPE_SUBTRACT : printf("SUBTRACT \n");
        break; 
        case INSTRUCTION_SELECT_REGISTER : printf("SLCT_REG %d\n",inst.operand);
        break;
        case INSTRUCTION_STORE_REGISTER : printf("STR_REG %d\n",inst.operand);
        break;
        case INSTRUCTION_GREATER_THAN : printf("GT %d\n",inst.operand);
        break;
        case INSTRUCTION_LESS_THAN : printf("LT %d\n",inst.operand);
        break;
        case INSTRUCTION_EQUAL_TO : printf("ET %d\n",inst.operand);
        break;
        case INSTRUCTION_JUMP_EQUAL_TO : printf("JEQ %d\n",inst.operand);
        break;
        case INSTRUCTION_JUMP_GREATER_THAN : printf("JGT %d\n",inst.operand);
        break;
        case INSTRUCTION_JUMP_LESS_THAN : printf("JLT %d\n",inst.operand);
        break;
    }

}

int vm_main() {

    printf(
        "Virtual Machine \n"
        "virtual machine running \n"
    );


    size_t size_of_inst_list = sizeof(_inst_list) / sizeof(_inst_list[0]);

    while(machine.program_counter < size_of_inst_list){
        machine.current_instruction = _inst_list[machine.program_counter];

        instruction_to_string(machine.current_instruction);

        program_errors err = execute(&machine);

        for(int i = 0;i < 10;i++)
            printf(" reg : %d value : %d \n",i,machine.reg[i]);

        print_stack(0,machine.stack_position,machine.stack);


    }

}
