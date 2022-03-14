#include "system.h"
#include <stdio.h>

typedef program_errors (*instruction_list) (virtual_machine*);

static program_errors add(virtual_machine* machine);
static program_errors subtract(virtual_machine* machine);
static program_errors push(virtual_machine* machine);
static program_errors pop(virtual_machine* machine);


static instruction_list inst_list[] = {
    
    [INSTRUCTION_TYPE_PUSH]     =   push,
    [INSTRUCTION_TYPE_POP]      =   pop,
    [INSTRUCTION_TYPE_ADD]      =   add,
    [INSTRUCTION_TYPE_SUBTRACT] =   subtract

};


void set_current_instruction(virtual_machine* machine,instruction inst){

    machine->current_instruction = inst;

}

static program_errors _exeucte(virtual_machine* machine){

    return inst_list[machine->current_instruction.instruction_type](machine);

}

program_errors execute(virtual_machine* machine){

    return _exeucte(machine);

}


static program_errors push(virtual_machine* machine){

    machine->stack_position++;
    machine->stack[machine->stack_position] = machine->current_instruction.operand;
    machine->program_counter++;

    return ERR_INSTRUCTION_OK;

}

static program_errors subtract(virtual_machine* machine){

    
    if(machine->stack_position != -1 && machine->stack_position >= 1){
        
        machine->stack[machine->stack_position - 1] -= machine->stack[machine->stack_position];
        
        machine->stack_position--;
        machine->program_counter++;

        return ERR_INSTRUCTION_OK;

    } 

    return ERR_SEGMENTATION_FAULT;


}

static program_errors add(virtual_machine* machine){

    if(machine->stack_position != -1 && machine->stack_position >= 1){
        
        machine->stack[machine->stack_position - 1] += machine->stack[machine->stack_position];
        
        machine->stack_position--;
        machine->program_counter++;

        return ERR_INSTRUCTION_OK;

    } 

    return ERR_SEGMENTATION_FAULT;

}

static program_errors pop(virtual_machine* machine){

    if(machine->stack_position == -1){

        return ERR_STACK_UNDERFLOW;

    }

    machine->stack[machine->stack_position--];

    machine->program_counter++;

    return ERR_INSTRUCTION_OK;

}