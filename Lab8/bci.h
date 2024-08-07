/*
 * CS 11, C track, lab 8
 *
 * FILE: bci.h
 *       Header file for the bytecode interpreter.
 *
 */

#ifndef BCI_H
#define BCI_H

#include <stdio.h>

/*
 * The instruction set.  Each instruction fits into a single byte.
 *
 * Glossary:
 * --------
 *   TOS: "top of the stack".
 *   Sn:  contents of stack position n (S1 == TOS)
 *   <n>: integer
 *   <i>: instruction
 *   <r>: register
 *
 * Notes:
 * -----
 *
 * 1) All operations that take their operands from the stack
 *    (i.e. ADD, SUB, MUL, DIV) pop these operands from the stack
 *    before putting the result back to the TOS.  STORE, JZ, JNZ,
 *    and PRINT also pop the TOS after they do their work.
 *
 * 2) Many operations take additional arguments from the instruction
 *    stream: PUSH, LOAD, STORE, JMP, JZ, JNZ.  These arguments
 *    are NOT found on the stack but are read in from the bytecode.
 *    They have the following lengths:
 *
 *    a) integers:     4 bytes (signed)
 *    b) instructions: 2 bytes (unsigned)
 *    c) registers:    1 byte (unsigned)
 *
 * 3) LOAD operations DO NOT erase the contents of a register.
 *
 */

/* --------------------- usage: ----------------------------------- */
#define NOP     0x00  /* NOP: do nothing.                           */
#define PUSH    0x01  /* PUSH <n>: push <n> to TOS.                 */
#define POP     0x02  /* POP: pop TOS.                              */
#define LOAD    0x03  /* LOAD <r>: load register <r> to TOS.        */
#define STORE   0x04  /* STORE <r>: store TOS to register <r>
                         and pop the TOS.                           */
#define JMP     0x05  /* JMP <i>: go to instruction <i>.            */
#define JZ      0x06  /* JZ <i>: if TOS is zero,
                         pop TOS and go to instruction <i>;
                         else just pop TOS.                         */
#define JNZ     0x07  /* JNZ <i>: if TOS is nonzero,
                         pop TOS and go to instruction <i>;
                         else just pop TOS.                         */
#define ADD     0x08  /* ADD: S2 + S1 -> TOS                        */
#define SUB     0x09  /* SUB: S2 - S1 -> TOS                        */
#define MUL     0x0a  /* MUL: S2 * S1 -> TOS                        */
#define DIV     0x0b  /* DIV: S2 / S1 -> TOS                        */
#define PRINT   0x0c  /* PRINT: print TOS to stdout and pop TOS.    */
#define STOP    0x0d  /* STOP: halt the program.                    */


/*
 * The virtual machine (VM).
 *
 * The VM contains a stack upon which arithmetic expressions are
 * evaluated, registers which hold results of computations, and
 * an instruction buffer which is where bytecode instructions are
 * located after being read in from disk.
 */

#define NREGS      16       /* Number of registers. */
#define MAX_INSTS  65536    /* Maximum number of instructions. */
#define STACK_SIZE 256      /* Size of the stack. */

typedef struct
{
    int stack[STACK_SIZE];           /* The stack.           */
    unsigned char sp;                /* The stack pointer.   */
    int reg[NREGS];                  /* Registers.           */
    unsigned char inst[MAX_INSTS];   /* Instructions.        */
    unsigned short ip;               /* Instruction pointer. */
} vm_type;

/* Declare the VM 'extern' so all files can access the same VM. */
extern vm_type vm;

/* Function to initialize the VM. */
void init_vm(void);

/*
 * Utility function to convert byte streams of varying widths
 * to integers.
 */
int read_n_byte_integer(int n);

/*
 * Functions that implement the machine operations.
 */

void do_push(int n);
void do_pop(void);
void do_load(int n);
void do_store(int n);
void do_jmp(int n);
void do_jz(int n);
void do_jnz(int n);
void do_add(void);
void do_sub(void);
void do_mul(void);
void do_div(void);
void do_print(void);


/*
 * Stored program execution.
 */

void load_program(FILE *fp);
void execute_program(void);
void run_program(char *filename);


#endif  /* BCI_H */



