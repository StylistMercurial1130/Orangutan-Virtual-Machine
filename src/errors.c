#include "errors.h"

const char* err_to_string(program_errors err){

    switch(err){

        case ERR_STACK_OVERFLOW : return "ERR_STACK_OVERFLOW";
        case ERR_STACK_UNDERFLOW : return "ERR_STACK_UNDERFLOW";
        case ERR_UNKOWN_INSTRUCTION : return "ERR_UNKOWN_INSTRUCTION";
        case ERR_SEGMENTATION_FAULT : return "ERR_SEGMENTATION_FAULT";
        case ERR_INSTRUCTION_OK : return "ERR_INSTRUCTION_OK";

    }

}