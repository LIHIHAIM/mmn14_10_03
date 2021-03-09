#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "label.h"

char *readLabel(char *line, int *lInd){
     char curr;
     int size = 1;
     char *label = malloc(size);
     if(!isAlloc(label))
          return NULL;
     while((curr = line[*lInd]) != '\0' && !isspace(curr)){
          label = realloc(label, ++size);
          label[size-1] = curr;
          (*lInd)++;
     }
     if(size == 1)
          return "\0";
     label[size] = '\0'; 
     return label;
}

boolean isValidLabel(char **label){
     boolean valid = TRUE;
     int i = 0;

     if(!isAlpha((*label)[i])){
          printf("error in label: label must start with an alphabetic character\n");
          valid = FALSE;
     }
     if(strlen(*label) > LABEL_SIZE){
          printf("error in label: the maximum label length is %d characters\n", LABEL_SIZE);
          valid = FALSE;
     }
     for(i = 1; i < strlen(*label); i++){
          if((*label)[i] == ':' && i != strlen(label)-1){
               printf("error in label: after end of label must be at least one space\n");
               valid = FALSE;
               break;
          }
          if(!isalnum((*label)[i])){
               printf("error in label: the label must include only alphabetical and numerical characters\n");
               valid = FALSE;
          }
     }
     (*label)[strlen(*label)-1] = '\0';
     return valid;
}