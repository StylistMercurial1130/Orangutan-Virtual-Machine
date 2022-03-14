#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "errors.h"

#define MAX_STACK_SIZE 1024

typedef enum {

    INSTRUCTION_TYPE_PUSH = 0,
    INSTRUCTION_TYPE_POP,
    INSTRUCTION_TYPE_ADD,
    INSTRUCTION_TYPE_SUBTRACT

} instruction_type;

typedef struct {

    instruction_type    instruction_type;
    int                 operand;

} instruction;


typedef struct {

    int         program_counter;
    int         stack[MAX_STACK_SIZE];
    int         stack_size;
    int         stack_position;
    instruction current_instruction;

} virtual_machine;

program_errors execute(virtual_machine* machine);
void set_current_instruction(virtual_machine* machine,instruction inst);

#endif
