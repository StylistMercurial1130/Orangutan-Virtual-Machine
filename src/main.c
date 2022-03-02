#include <stdio.h>
#include <stdint.h> 

#define STACK_SIZE 1024
#define SIZE_OF(arr) (sizeof(arr)/sizeof(arr[0]))

typedef enum {

    INSTRUCTION_TYPE_PUSH = 0,
    INSTRUCTION_TYPE_ADD,
    INSTURCTION_TYPE_SUBTRACT,
    INSTRUCTION_TYPE_JUMP,
    INSTRUCTION_TYPE_POP,
    INSTRUCTION_TYPE_JLT,
    INSTRUCTION_TYPE_JGT,
    INSTRUCTION_TYPE_INC,
    INSTRUCTION_TYPE_DEC,
    INSTRUCTION_TYPE_SELECT_REGISTER,
    INSTRUCTION_TYPE_STORE_REGISTER,
    INSTRUCTION_TYPE_ADD_REGISTER,
    INSTRUCTION_TYPE_SUBTRACT_REGISTER

} instruction_type;

typedef enum{

    ERR_EMPTY_STACK = 0,
    ERR_INSTRUCTION_OK,
    ERR_INSUFICIENT_OPERAND_AVIALABLE,
    ERR_SEGMENTATION_FAULT,
    ERR_UNKNOWN_INSTRUCTION,
    ERR_REGISTER_DOES_NOT_EXIST
    
} err;

typedef struct {

    uint64_t operand;
    instruction_type type;

} instruction;



typedef struct {

    int stack_pos;
    uint64_t stack[STACK_SIZE];
    int program_counter;
    int registers[10];
    int current_register;
    instruction current_instruction;

} virtual_machine;

virtual_machine machine = {.stack_pos = -1 , .program_counter = 0};

instruction inst_list[] = {

    {.operand = 1 , .type = INSTRUCTION_TYPE_SELECT_REGISTER},
    {.operand = 10 , .type = INSTRUCTION_TYPE_STORE_REGISTER}
    
};

err execute_instructions(instruction *inst){

    switch(inst->type){
        case INSTRUCTION_TYPE_PUSH:

            machine.stack[++machine.stack_pos] = inst->operand;
            machine.program_counter++;

            break;

        case INSTRUCTION_TYPE_POP:

            if(machine.stack_pos == -1){

                return ERR_EMPTY_STACK;

            }

            machine.stack_pos--;
            machine.program_counter++;

            break;

        case INSTRUCTION_TYPE_ADD:

            if(machine.stack_pos < 1){

                return ERR_INSUFICIENT_OPERAND_AVIALABLE;

            }

            machine.stack[machine.stack_pos - 1] += machine.stack[machine.stack_pos];
            machine.stack_pos--;
            machine.program_counter++;

            break;
        case INSTURCTION_TYPE_SUBTRACT:

            if(machine.stack_pos < 1){

                return ERR_INSUFICIENT_OPERAND_AVIALABLE;

            }

            machine.stack[machine.stack_pos - 1] -= machine.stack[machine.stack_pos];
            machine.stack_pos--;
            machine.program_counter++;

            break;

        case INSTRUCTION_TYPE_JUMP:

            if(inst->operand > machine.program_counter){
                
                return ERR_SEGMENTATION_FAULT;

            } 

            if(inst->operand < 0){

                return ERR_SEGMENTATION_FAULT;

            } 

            machine.program_counter = machine.current_instruction.operand;

            break;

        case INSTRUCTION_TYPE_INC:

            if(inst->operand > machine.stack_pos){

                return ERR_SEGMENTATION_FAULT;

            } 

            if(inst->operand < 0){

                return ERR_SEGMENTATION_FAULT;

            }

            machine.stack[inst->operand]++;
            machine.program_counter++;

            break;

        case INSTRUCTION_TYPE_DEC:
        
            
            if(inst->operand > machine.stack_pos){

                return ERR_SEGMENTATION_FAULT;

            } 

            if(inst->operand < 0){

                return ERR_SEGMENTATION_FAULT;

            }

            machine.stack[inst->operand]--;
            machine.program_counter++;

            break;
        
        case INSTRUCTION_TYPE_JGT:


            if(inst->operand > (SIZE_OF(inst_list) - 1) ){

                return ERR_UNKNOWN_INSTRUCTION;

            }

            if(machine.stack_pos < 1){

                return ERR_INSUFICIENT_OPERAND_AVIALABLE;

            }

            if(machine.stack[machine.stack_pos - 1] > machine.stack[machine.stack_pos]){

                machine.program_counter = inst->operand;

            }else {

                machine.program_counter++;

            }

            break;
        
        case INSTRUCTION_TYPE_JLT:


            if(inst->operand > (SIZE_OF(inst_list) - 1) ){

                return ERR_UNKNOWN_INSTRUCTION;

            }

            if(machine.stack_pos < 1){

                return ERR_INSUFICIENT_OPERAND_AVIALABLE;

            }

            if(machine.stack[machine.stack_pos - 1] < machine.stack[machine.stack_pos]){

                machine.program_counter = inst->operand;

            } else {

                machine.program_counter++;

            }

            break;
        case INSTRUCTION_TYPE_SELECT_REGISTER:
            
            if(inst->operand > 9){

                return ERR_REGISTER_DOES_NOT_EXIST;

            }

            machine.current_register = inst->operand;

            machine.program_counter++;

            break;
        case INSTRUCTION_TYPE_STORE_REGISTER:

            machine.registers[machine.current_register] = inst->operand;

            machine.program_counter++;

            break;
        case INSTRUCTION_TYPE_ADD_REGISTER:

            machine.registers[machine.current_register] += inst->operand;

            machine.program_counter++;
            break;
        case INSTRUCTION_TYPE_SUBTRACT_REGISTER:

            machine.registers[machine.current_register] -= inst->operand;

            machine.program_counter++;
            break;
            
    }

    return ERR_INSTRUCTION_OK;

}

  
void virtual_machine_dump(){

    for(int i = 0;i <= machine.stack_pos;i++){

        fprintf(stderr,"\t%d \n",machine.stack[i]);

    }

}


const char* err_to_string(err error){

    switch (error)
    {
        case ERR_EMPTY_STACK : return "ERR_EMPTY_STACK";
        case ERR_INSTRUCTION_OK : return "ERR_INSTRUCTION_OK";
        case ERR_INSUFICIENT_OPERAND_AVIALABLE : return "ERR_INSUFICEINT_OPERAND_AVAILABLE";

    }

}

void fetch(){ machine.current_instruction = inst_list[machine.program_counter];  }

void print_inst(instruction inst){

    switch(inst.type){

        case INSTRUCTION_TYPE_PUSH:
            fprintf(stderr,"%s %d \n","PUSH",inst.operand);
            break;
        case INSTRUCTION_TYPE_ADD:
            fprintf(stderr,"%s \n","ADD");
            break;
        case INSTURCTION_TYPE_SUBTRACT:
            fprintf(stderr,"%s \n","SUB");
            break;
        case INSTRUCTION_TYPE_POP:
            fprintf(stderr,"%s \n","POP");
            break;
        case INSTRUCTION_TYPE_JUMP:
            fprintf(stderr,"%s %d \n","JUMP",inst.operand);
            break;
        case INSTRUCTION_TYPE_INC:
            fprintf(stderr,"%s %d\n","INC",inst.operand);
            break;
        case INSTRUCTION_TYPE_DEC:
            fprintf(stderr,"%s %d\n","DEC",inst.operand);
            break;
        case INSTRUCTION_TYPE_JGT:
            fprintf(stderr,"%s %d\n","JGT",inst.operand);
            break;
        case INSTRUCTION_TYPE_JLT:
            fprintf(stderr,"%s %d\n","JLT",inst.operand);
            break;
        case INSTRUCTION_TYPE_SELECT_REGISTER:
            fprintf(stderr,"%s %d\n","SLCTREG",inst.operand);
            break;
        case INSTRUCTION_TYPE_STORE_REGISTER:
            fprintf(stderr,"%s %d\n","STR",inst.operand);
            break;
    }

}

int main(){

    while(machine.program_counter >= 0 && machine.program_counter < SIZE_OF(inst_list)){

        fetch();

        print_inst(machine.current_instruction);

        err error = execute_instructions(&machine.current_instruction);

        fprintf(stderr,"%s\n","Stack:");

        if(error != ERR_INSTRUCTION_OK){

            fprintf(stderr,"%s\n",err_to_string(error));
            break;

        }

        virtual_machine_dump();

    }

    return 0;

}