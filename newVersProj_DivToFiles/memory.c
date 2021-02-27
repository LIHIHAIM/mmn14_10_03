#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h"

#define REGISTERS 8
#define OS_MEM 100
#define RAM_SIZE 4096
#define COMMANDS 4
#define FUNCT_SIZE 4
#define DEST_SIZE 2
#define SOURCE_SIZE 2



#define MAKE_STRING(str) #str /* making a string */
#define REGISTER_NAME(reg) MAKE_STRING(r##reg) /* making a register name (string starts with 'r' and then a number) */

word registers[REGISTERS+1]; /* general registers (8) + the PSW register */
int IC, DC; /* Instructions-Counter, Data-Counter (index) */
word *instImage, *dataImage;
word *RAM;

boolean isAlloc(void *p){
    if(!p){
        printf("error : memory allocation failed\n");
        return FALSE;
    }
    return TRUE;
}

boolean addToSymTab(symbolTable *symTab, char *name, char *attrib, int *size){
    if(size == 0)
        symTab = calloc(1, sizeof(symbolTable));
    else
        symTab = realloc(symTab,(*size)++ * sizeof(symbolTable));
    if(!isAlloc(symTab) || size-1 >= RAM_SIZE || isIlegalName(label, symTab, size))
        return FALSE;
    (*size)++
    symTab[*size-1].symbol = name;
    symTab[*size-1].address = DC;
    symTab[*size-1].attribute = attrib;
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

boolean isIlegalName(char *label, symbolTable* symTab, int size){
    int i;
    boolean error = FALSE;
    char commands[COMMANDS] = {".data",".string",".extern",".entry"};

    for(i = 0; i < REGISTERS; i++){
        if(strcmp(REGISTER_NAME(i), label){
            printf("error: label should not be named as a register\n");
            return TRUE;
        }
        if(i <= COMMANDS){
            if(strcmp(commands[i], label)){
                printf("error: label should not be named as a directive\n");
                return TRUE;
            }
        }
    }
    if(wasDefined(symTab, label, size)){
        printf("error: label has been already defined\n");
        return TRUE;
    }
    return FALSE;
}

void delTabAndCnts(symbolTable *symTab){
    free(symTab);
    free(instImage);
    free(dataImage);
    return;
}

void resetCounters(){
    IC = OS_MEM;
    DC = 0;
    return;
}

void pushInstruction(word newInst){
    if(IC == OS_MEM)
        instImage = calloc(1, sizeof(word));
    else
        instImage = realloc(instImage, (IC-OS_MEM) * sizeof(word));
    if(!isAlloc(instImage)){
        printf("error: cannot push more words to memory, memory allocation failed\n");
        return;
    }
    instImage[IC-OS_MEM] = newInst;
    IC++;
    return;
}

void pushData(word newData){
    if(DC == OS_MEM)
        dataImage = calloc(1, sizeof(word));
    else
        dataImage = realloc(dataImage, (DC-OS_MEM) * sizeof(word));
    if(!isAlloc(dataImage)){
        printf("error: cannot push more words to memory, memory allocation failed\n");
        return;
    }
    
    instImage[DC-OS_MEM] = dataInst;
    DC++;
    return;
}

void pushToRAM(){
    RAM = calloc(IC+DC, sizeof(word));
}

void fileExternals(){}
void fileEntrys(){}
void fileObjext(){}

word buildMainWord(int opcode, int funct, int source, int dest){
    word w;
    word w.wrd = source + dest<<SOURCE_SIZE + funct<<(DEST_SIZE+SOURCE_SIZE) + opcode<<(FUNCT_SIZE+DEST_SIZE+SOURCE_SIZE);
    return w;
}

word buildWord(){}