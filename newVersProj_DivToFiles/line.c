#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "line.h"

#define MAX_DIR_COM_LEN 8 /* maximum length of a directive command */ 
#define DIR_COMS 4 /* the directive commands */

char *dirCommands[DIR_COMS] =  {".data", ".string", ".entry", ".extern"}; /* the directive commands */

static boolean jumpSpaceComma(char *);

/* get the optional label before the sentence */
boolean getOptLabel(char *label, char *line, int *lInd){
     int temp, i;
     char curr;
     boolean firstColon = FALSE;

     *lInd = jumpSpaces(line,*lInd);
     temp = *lInd;
     while(!isspace(curr = line[lInd]) && curr != '\0'){
          if(*lInd-temp > LABEL_SIZE && firstColon == FALSE){
               printf("error : label is too long, maximum label length is %d\n",LABEL_SIZE);
               return FALSE;
          }
          if(temp == *lInd && !isalpha(curr)){ /* label does not start with a letter */
               printf("error : label must start with an alphabetic character\n");
               return FALSE;
          }
          if(curr != ':' && firstColon == TRUE && line[*lInd+1] != '\0' && !isspace(line[*lInd+1])){
               printf("error : after label must be at list one space\n");
               return FALSE;
          }
          if(!isalnum(curr) && curr != ':'){ /* label include a not alphabetical or numberical characters or a colon */ 
               printf("error : label must include only alphbetical and numerical characters\n");
               return FALSE;
          }
          /*if(curr == ':' && firstColon == TRUE){
               fprintf(stderr,"error: to many colons in label name, label must be in the form \" label: \"\n");
               return FALSE;
          }*/
          if(curr == ':')
               firstColon = TRUE;
          else 
               label[*lInd-temp] = curr;
          (*lInd)++;
     }

     label[*lInd-temp] = '\0';
     if(temp == *lInd)
          label = NULL;
     return TRUE;
}

int getDirCom(char *command, char *line, int *lInd){
     int /*i = *ind,*/ temp;
     int i;
     char curr;

     *lInd = jumpSpaces(line,*lInd);
     temp = *lInd;
     while((curr = line[*lInd]) != '\0' && !isspace(curr)){ /* reading the command */
          command[*lInd-temp] = curr;
          (*lInd)++;
     }
     command[*lInd-temp] = '\0';
     
     for(i = 0; i < DIR_COMS; i++){
          if(strcmp(command,dirCommands[i]))
               return i;
     }
     printf("error : directive command - %s , is not valid.",command);
     printf("Command must be: %s / %s / %s / %s\n",dirCommands[data],dirCommands[string],dirCommands[entry],dirCommands[external]);
     return -1;
}

char **getParms(char *line){
     enum status{IN, COMMA, HASH, LQ, RQ, NUM, OUT};
     enum status state = IN;
     char **params = calloc(1,sizeof(char*));
     int i = 0, j = 0, sizeI = 1, sizeJ = 1;
     char curr;

     if(!isAlloc(params))
          return NULL;
     params[0][0] = '1'; /* not null value */
     lInd = jumpSpaces(line, lInd);

     while((curr = line[lInd]) != '\n'){
          switch(state){
               case IN:
                    if(curr == '\n'){
                         state = OUT;
                         break;
                    }
                    if(curr == '#')
                         state = HASH;
                    else if(curr == '\"')
                         state = LQ;
                    else
                         state = NUM;
               case HASH:
                    if(curr == '#')
                         break;
                    if(isspace(curr) && line[lInd-1] != '#'){
                         state = COMMA;
                         break;
                    }
                    if(line[lInd-1] != '#'){
                         printf("error : no numerical number inserted after '#' label\n");
                         return NULL;
                    }
                    if(!isdigit(curr)){
                         printf("error : decimal number must include only numerical digits\n");
                         return NULL;
                    }
                    if(line[lInd-1] != '#' && (curr == '+' || curr == '-')){
                         printf("error : negative or positive sign must be in the start of the number\n");
                         return NULL;
                    }
                    params[i][j] = curr;
                    params[i] = realloc(params[i], (++sizeJ) * sizeof(char));
                    if(!isAlloc(params[i]))
                         return NULL;
                    j++;
                    break;
               break;
               case COMMA:
                    if(!jumpSpaceComma(line))
                         return NULL;
                    sizeI++;
                    state = IN;
               break;
               case LQ:

               case OUT:
                    return params;
          }
          lInd++;
     }
}

static boolean jumpSpaceComma(char *line){
     int firstComma = 0;
     char curr;
     while((curr = line[lInd]) != '\0' && (isspace(curr) || curr == ',')){
          if(curr == ',')
               firstComma++;
          if(firstComma > 1){
               printf("error : between parameters must seperate one comma only\n");
               return FALSE;
          }
          lInd++;
     }
     if(firstComma == 0){
          printf("error : between parameters must seperate one comma\n");
          return FALSE;
     }
     return TRUE;
}

int jumpSpaces(char *line, int ind){
     char curr;
     while((curr = line[ind]) != '\0' && isspace(curr))
          ind++;
     return ind;
}