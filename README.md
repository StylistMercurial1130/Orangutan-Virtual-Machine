# Orangutan Virtual Machine

There are 2 major components to the architecture of this virtual machine. 

- The stack
- The registers (10 registers)

## The Stack

The Stack could be seen as a array of the size 1024 , i.e an array of integers of the size 1024. 

**Todo : Dynamically allocated stack**


## The Registers

There are 10 registers in total that can be used in this virtual machine. 

## ISA (Instruction Set Architecture)

There are total of 14 instructions in this virtual macine 

- Add Stack instruction
- Subtract Stack instruction
- Pop Stack instruction
- Push stack instruction
- Select registers instruction
- Store register value instruction
- Jump instruction
- Less than instruction
- Greater than instruction
- Equal to instruction
- Jump Less than instruction
- Jump Greater than instruction
- Jump Equal to instruction
- Add to registers instruction
- Subtract from registers

# TODO list

- Dynamically growing stack
- Generating Byte Code from orangutan file
- Processing the Byte code and loading it onto the vm

