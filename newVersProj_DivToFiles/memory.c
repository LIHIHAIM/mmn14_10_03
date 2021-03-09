#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "memory.h"
#include "label.h"

#define OS_MEM 100
#define RAM_SIZE 4096
#define FUNCT_SIZE 4
#define DEST_SIZE 2
#define SOURCE_SIZE 2
#define LABEL_SIZE 31
#define REGISTERS 8
#define COMMANDS 4
#define INSTRUCTIONS 16

#define MAKE_STRING(str) #str /* making a string */
#define REGISTER_NAME(reg) MAKE_STRING(r##reg) /* making a register name (string starts with 'r' and then a number) */

static word registers[REGISTERS+1]; /* general registers (8) + the PSW register */
static int IC, DC; /* Instructions-Counter, Data-Counter (index) */
static word *instImage, *dataImage;
static symbolTable *symTab;
static int symSize;

boolean pushData(char *line, int *lInd){
    int size = 1, i = 0, j;
    word *params = calloc(size, sizeof(word));
    boolean error = FALSE;

    if(!isAlloc(params))
        return ERROR;

    while(line[*lInd] != '\0'){
        word *scaned;
        params = realloc(params, (++size) * sizeof(paramType));

        if(!isAlloc(params))
            return ERROR; 
        if(!isThereComma(line, lInd))
            return FALSE;
        if(!(scaned = scanDataParams(line, lInd))) /* scanning data from the line */
            error = TRUE;
        if(error == TRUE)
            continue;

        j = 0;
        while(scaned[j] != NULL){
            if(DC == OS_MEM) /* pushing the data to the data image */ 
                dataImage = calloc(1, sizeof(word));
            else
                dataImage = realloc(dataImage, (DC - OS_MEM) * sizeof(word));
            if(!isAlloc(params))
                return ERROR;
            dataImage[DC - OS_MEM] = newData;
            DC++;
            j++;
        }
    }
    return TRUE;
}

boolean pushExtern(char *line, int *lInd){
    int temp, size = 1, curr;
    char curr;
    char **label = malloc(sizeof(*char));
    if(!isAlloc(label))
        return ERROR; 

    while(isspace(line[*lInd]))
        (*lInd)++;

    *label = readLabel(line, lInd);
    if(!isValidLabel(label))
        return FALSE;
    label[size-1] = '\0';
    if(isIlegalName(*label))
        return FALSE;
    if(!addToSymTab(*label, 0, "external"))
        return FALSE;
    return TRUE;
}

/* label */
boolean addToSymTab(char *name, int val, char *attrib){
    static int size = 0;
    if(size == 0)
        symTab = malloc(sizeof(symbolTable));
    else
        symTab = realloc(symTab, (size++) * sizeof(symbolTable));
    if(!isAlloc(*symTab) || isIlegalName(label, size))
        return FALSE;
    symTab[size].symbol = name;
    symTab[size].address = val;
    symTab[size].attribute = attrib;
    size++;
    return TRUE;
}

boolean wasDefined(char *sym){
    int i;
    for(i = 0; i < size; i++){
        if(strcmp(symTab[i].symbol, sym))
            return TRUE;
    }
    return FALSE;
}

boolean isIlegalName(char *label){
    int i;
    boolean error = FALSE;
    char directives[COMMANDS] = {".data",".string",".extern",".entry"};
    char *instructions[INSTRUCTIONS] = {"mov", "cmp", "add", "sub", "lea",
                                        "clr", "not", "inc", "dec", "jmp", 
                                        "bne", "jsr", "red", "prn", "rts",
                                        "stop"};

    for(i = 0; i < REGISTERS; i++){
        if(strcmp(REGISTER_NAME(i), label){
            printf("error: label should not be named as a register\n");
            return TRUE;
        }
        if(i <= COMMANDS){
            if(strcmp(directives[i], label)){
                printf("error: label should not be named as a directive\n");
                return TRUE;
            }
        }
    }
    for(i = 0; i < INSTRACTIONS; i++){
        if(strcmp(instructions[i], label)){
            printf("error: label should not be named as an instruction\n");
            return TRUE;
        } 
    }
    if(wasDefined(label)){
        printf("error: label has been already defined\n");
        return TRUE;
    }
    return FALSE;
}

/* memory allocation */
boolean isAlloc(void *p){
    if(!p){
        printf("error : memory allocation failed, could not continue the compilation process\n");
        return FALSE;
    }
    return TRUE;
}

boolean isOverFlow(void){
    if(IC + DC > RAM_SIZE){
        printf("error: memory over flow\n")
        return TRUE;
    }
    return FALSE;
}

/* conters and memory images */
void delMem(){
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

word buildMainWord(int opcode, int funct, int source, int dest){
    word w;
    word w.wrd = source + dest << SOURCE_SIZE + 
                funct << (DEST_SIZE + SOURCE_SIZE) + 
                opcode << (FUNCT_SIZE + DEST_SIZE + SOURCE_SIZE);
    return w;
}

word buildRegWord(char *reg){
    word w;
    word w.wrd = 1 << (atoi(reg[1]) - 1);
    return w;
}