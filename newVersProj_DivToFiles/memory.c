#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h"

#define REGISTERS 8
#define MAKE_STRING(str) #str /* making a string */
#define REGISTER_NAME(reg) MAKE_STRING(r##reg) /* making a register name (string starts with 'r' and then a number) */

word registers[REGISTERS+1]; /* general registers (8) + the PSW register */
int IC, DC; /* Instructions-Counter, Data-Counter*/

boolean isAlloc(void *p){
    if(!p){
        printf("error : memory allocation failed\n");
        return FALSE;
    }
    return TRUE;
}

boolean addToSymTab(symbolTable *symTab, char *name, int add, char *attrib, int *size){
    symTab = realloc(symTab,(*size)++ * sizeof(symbolTable));
    if(!isAlloc(symTab))
        return FALSE;
    symTab[size].symbol = name;
    symTab[size].address = add;
    symTab[size].attribute = attrib;
    return TRUE;
}

boolean wasDefined(symbolTable *symTab, char *sym, int size){
    int i;
    for(i = 0; i < size; i++){
        if(strcmp(symTab[i].symbol, sym))
            return TRUE;
    }
    return FALSE;
}

boolean isNameRegister(char *label){
    int i;
    for(i = 0; i < REGISTERS; i++){
        if(strcmp(REGISTER_NAME(i), label)){
            printf("error: label can not be named as a register\n");
            return FALSE;
        }
    }
    return TRUE;
}