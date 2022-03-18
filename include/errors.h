#ifndef __ERRORS_H__
#define __ERRORS_H__

typedef enum {

    ERR_STACK_OVERFLOW = 0,
    ERR_STACK_UNDERFLOW,
    ERR_UNKOWN_INSTRUCTION,
    ERR_SEGMENTATION_FAULT,
    ERR_INSTRUCTION_OK,
    ERR_INSTRUCTION_REGISTER_BOUND_UNKOWN

} program_errors;

const char* err_to_string(program_errors err);

#endif