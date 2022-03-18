#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <stdint.h>
#include "errors.h"

#define MAX_STACK_SIZE 512 * 1000u

typedef enum {
    INSTRUCTION_TYPE_PUSH = 0,  
    INSTRUCTION_TYPE_POP,
    INSTRUCTION_TYPE_ADD,
    INSTRUCTION_TYPE_SUBTRACT,
    INSTRUCTION_SELECT_REGISTER,
    INSTRUCTION_STORE_REGISTER,
    INSTRUCTION_LESS_THAN,
    INSTRUCTION_EQUAL_TO,
    INSTRUCTION_GREATER_THAN,
    INSTRUCTION_JUMP,
    INSTRUCTION_JUMP_LESS_THAN,
    INSTRUCTION_JUMP_GREATER_THAN,
    INSTRUCTION_JUMP_EQUAL_TO,
    INSTRUCTION_ADD_TO_REG,
    INSTRUCTION_SUB_FROM_REG
} instruction_type;

typedef struct {

    instruction_type    instruction_type;
    int                 operand;

} instruction;


typedef union {

    struct{
        uint8_t less_than_flag;
        uint8_t greater_than_flag;
        uint8_t equal_to_flag;
        uint8_t dummy_flag_flag;
    };

}flag;

typedef struct {

    int         program_counter;
    int         stack[MAX_STACK_SIZE];
    int         stack_size;
    int         stack_position;
    int         reg[10];
    flag        flag_registers;
    int         current_register;
    instruction current_instruction;

} virtual_machine;

program_errors execute(virtual_machine* machine);
void set_current_instruction(virtual_machine* machine,instruction inst);

#endif
