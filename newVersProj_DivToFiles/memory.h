#include "bool.h"

typedef struct{
     char *symbol;
     int address;
     char *attribute;
} symbolTable;

typedef struct{
     int wrd:12; 
} word;

typedef struct{
     enum dataType {intOrChar, reg, label};
     enum dataType type;
     word param;
} paramType;

boolean isAlloc(void *);
boolean addToSymTab(char *, int, char *);
boolean wasDefined(char *);
boolean isIlegalName(char *);
void delMem();