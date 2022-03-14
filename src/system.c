#include "system.h"
#include <stdio.h>

typedef program_errors (*instruction_list) (virtual_machine*);

static program_errors add(virtual_machine* machine);
static program_errors subtract(virtual_machine* machine);
static program_errors push(virtual_machine* machine);
static program_errors pop(virtual_machine* machine);
static program_errors select_registers(virtual_machine* machine);
static program_errors store_register(virtual_machine* machine);
static program_errors jump(virtual_machine* machine);
static program_errors less_than(virtual_machine* machine);
static program_errors greater_than(virtual_machine* machine);
static program_errors equal_to(virtual_machine* machine);
static program_errors jump_less_than(virtual_machine* machine);
static program_errors jump_greater_than(virtual_machine* machine);
static program_errors jump_equal_to(virtual_machine* machine);

static instruction_list inst_list[] = {
    
    [INSTRUCTION_TYPE_PUSH]         =   push,
    [INSTRUCTION_TYPE_POP]          =   pop,
    [INSTRUCTION_TYPE_ADD]          =   add,
    [INSTRUCTION_TYPE_SUBTRACT]     =   subtract,
    [INSTRUCTION_JUMP]              =   jump,
    [INSTRUCTION_EQUAL_TO]          =   equal_to,
    [INSTRUCTION_GREATER_THAN]      =   greater_than,
    [INSTRUCTION_LESS_THAN]         =   less_than,
    [INSTRUCTION_JUMP_LESS_THAN]    =   jump_greater_than,
    [INSTRUCTION_JUMP_EQUAL_TO]     =   jump_equal_to,
    [INSTRUCTION_JUMP_GREATER_THAN] =   jump_less_than

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

static program_errors select_registers(virtual_machine* machine){

    if(machine->current_instruction.operand >= 0 && machine->current_instruction.operand <=9){
        
        machine->current_register = machine->current_instruction.operand;

        return ERR_INSTRUCTION_OK;

    } 

    return ERR_INSTRUCTION_REGISTER_BOUND_UNKOWN;

}

static program_errors store_register(virtual_machine* machine){

    machine->reg[machine->current_register] = machine->current_instruction.operand;    

    return ERR_INSTRUCTION_OK;


}

static program_errors jump(virtual_machine* machine){

    if(machine->program_counter >= 0){

        machine->program_counter = machine->current_instruction.operand;

        return ERR_INSTRUCTION_OK;

    }

    return ERR_SEGMENTATION_FAULT;

}

static program_errors less_than(virtual_machine* machine){

    if(machine->reg[machine->current_register] < machine->current_instruction.operand){

        machine->flag_registers.less_than_flag = 1;

    } else {

        machine->flag_registers.less_than_flag = 0;

    }

    return ERR_INSTRUCTION_OK;

}

static program_errors greater_than(virtual_machine* machine){

    if(machine->reg[machine->current_register] > machine->current_instruction.operand){

        machine->flag_registers.greater_than_flag = 1;

    } else {

        machine->flag_registers.greater_than_flag = 0;

    }

    return ERR_INSTRUCTION_OK;

}

static program_errors equal_to(virtual_machine* machine){

    if(machine->reg[machine->current_register] == machine->current_instruction.operand){

        machine->flag_registers.equal_to_flag = 1;

    } else {

        machine->flag_registers.equal_to_flag = 0;

    }

    return ERR_INSTRUCTION_OK;

}

static program_errors jump_equal_to(virtual_machine* machine){

    if(machine->current_instruction.operand >= 0){

        if(machine->flag_registers.equal_to_flag){

            machine->program_counter = machine->current_instruction.operand;

        }

        return ERR_INSTRUCTION_OK;

    }

    return ERR_SEGMENTATION_FAULT;

}

static program_errors jump_greater_than(virtual_machine* machine){

    if(machine->current_instruction.operand >= 0){

        if(machine->flag_registers.greater_than_flag){

            machine->program_counter = machine->current_instruction.operand;

        }

        return ERR_INSTRUCTION_OK;

    }

    return ERR_SEGMENTATION_FAULT;

}

static program_errors jump_less_than(virtual_machine* machine){

    if(machine->current_instruction.operand >= 0){

        if(machine->flag_registers.less_than_flag){

            machine->program_counter = machine->current_instruction.operand;

        }

        return ERR_INSTRUCTION_OK;

    }

    return ERR_SEGMENTATION_FAULT;

}
