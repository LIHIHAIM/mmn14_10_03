#include "filesAndMem.h"

int isAlloc(void *p){
    if(!p){
        fprintf(stderr,"error : memory allocation failed\n");
        return 0;
    }
    return 1;
}

symbol *newSymTable(char *name, int val, char *attrib){
    symbol *symTab = malloc(sizeof(symbol));
    return symTab;
}