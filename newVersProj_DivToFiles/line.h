#include "bool.h"
#define LABEL_SIZE 31

enum cmds {data, string, entry, external}; 

boolean getOptLabel(char *, char *, int *);
int getDirCom(char *, char *, int *);
char **getParams(char *);
int jumpSpaces(char *, int);
