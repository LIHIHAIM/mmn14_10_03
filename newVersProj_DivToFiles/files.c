#include <stdlib.h>
#include "files.h"

/* openf(): Open a given file in a given status and returns the pointer to the file. */
FILE *openf(char *file, char *status){
     FILE *fd = fopen(file, status);
     if(!fd)
          printf("error : could not open file: \"%s\"\n",file);
     return fd;
}

/* readLine(): Reads a line (length 80 characters) from a given file pointer - fd, 
 to a dinamic array and returns the array. */
char *readLine(FILE *fd, int len){
     char *line = calloc(len,sizeof(char));
     fgets(line,len,fd);
     return line;
}