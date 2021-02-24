#include "bool.h"

typedef struct{
     char *symbol;
     int address;
     char *attribute;
} symbolTable; 

typedef struct{
     int wrd:12; 
} word;

boolean isAlloc(void *);
boolean addToSymTab(symbolTable *, char *, int, char *, int);
boolean wasDefined(symbolTable *, char *, int);
boolean isNameRegister(char *);
