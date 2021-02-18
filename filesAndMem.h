#include <stdio.h>
#include <stdlib.h>

FILE *openf(char *, char *);
char *readLine(FILE *, int);
int isAlloc(void *);

typedef struct{
     char *sym;
     int val;
     char *attrib;
}symbol; 