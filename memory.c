#include "filesAndMem.h"

int isAlloc(void *p){
    if(!p){
        fprintf(stderr,"error : memory allocation failed\n");
        return 0;
    }
    return 1;
} 