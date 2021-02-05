#include <string.h> /* for strcpy() */ 

#include "filesAndMem.h" /* for openf(), readLine(), LINE, <stdio.h> */
#include "assembler.h" /* memory building */
#include "interface.h" /* contacting main */

#define FOREVER 1
#define MAX_DIR_COM_LEN 8 /* maximum length of a directive command */ 
#define LABEL_SIZE 31
#define DIR_COMS 4 /* the directive commands */

boolean getOptLabel(char *);
int getDirCom(char *);
boolean executeCom(char *);

char* dirCommands[DIR_COMS] =  {".data", ".string", ".entry", ".extern"}; /* the directive commands */
enum cmds {data, string, entry, external};

IC = 100, DC = 0, lineInd = 0;

/* compile(): The function compiles an Assembly file and make one to three files in addition:
 file.ob - a binary file, which includes the memory....
 file.ent - an "entry" file, which includes the names of all the variable which other files can see and
            their address in the RAM.
 file.ext - an "extern" file, which includes the names of all the external variables (from other files) 
            and their calling address in the RAM.
*/
boolean compile(char *fileName){
     FILE *fd = openf(fileName,"r");
     char *tempLine;
     senType type;
     boolean symbol = FALSE;

     compSuc = TRUE;

     if(!fd)
          return FALSE;
     while(FOREVER){
          char *optLabel = calloc(LABEL_SIZE,sizeof(char));
          if(!isAlloc(optLabel))
               return FALSE;
          tempLine = readLine(fd,LINE);
          if(*tempLine == '\0')
              break;
          strcpy(line,tempLine);
          free(tempLine);

          if(!getOptLabel(optLabel)){
               compSuc = FALSE;
               continue;
          }
          if(optLabel)
               symbol = TRUE;
          type = getSenType(line);
          /* ---------------------------- must define symbols table! ----------------------- */
          switch(type){
               case blank:
               case comment:
               break;
               case directive:
                    int command = getDirCom(command);
                    switch(command){
                         case data:
                         case string:
                              char **params;
                              if(symbol == TRUE){
                                   if(/* search(optLabel) */){
                                        /* some error */
                                        compSuc = FALSE;
                                        continue;
                                   }
                                   /*push(".data", DC, optLabel)*/
                                   DC++;
                              }
                              params = getParams();
                              pushParams(params, DC);
                              continue;
                         case external:
                              if(/* search(optLabel) */){
                                   /* some error */
                                   compSuc = FALSE;
                                   continue;
                              }
                              /* push(".extern", 0, optLabel);*/
                              if(isThereLabel()){
                                   /* print some error */
                              }
                              continue;
                         case entry:
                              continue;
                    }
               break;
               case order:
                    int order;
                    /* Lihis enum */
                    if(symbol == TRUE){
                         if(/* search(optLabel) */){
                              /* some error */
                              compSuc = FALSE;
                              continue;
                         }
                         /*push(".code", IC, optLabel)*/
                         IC++;
                    }
                    int order = getOrder();
                    if(/*searchOrder(order) || !isValid(order) */){
                         /* some error */
                         compSuc = FALSE;
                         continue;
                    }
                    switch(order){
                         /* for every order */
                    }
               break;
          }
     }

     /* */
     while(FOREVER){}
}
     /*while(FOREVER){
          tempLine = readLine(fd,LINE);
          if(*tempLine == '\0')
               return compSuc;
          strcpy(line,tempLine);
          free(tempLine);
          type = getSenType(line);
          printf("line: %s",line);
          switch(type){
               case blank:
                    printf("blank\n");
               break;
               case comment:
               break;
               case directive:
               {
                    int *lind = calloc(1,sizeof(int)); /* index of current character in line 
                    char *optLabel = calloc(LABEL_SIZE,sizeof(char));
                    int command; /* = calloc(MAX_DIR_COM_LEN, sizeof(char))
                    printf("directive\n");
                    if(!isAlloc(lind) || !isAlloc(optLabel))
                         return FALSE;
                    if(!getOptLabel(optLabel,lind)){
                         compSuc = FALSE;
                         continue;
                    }
                    *lind = jumpSpaces(line,*lind);
                    /*if(optLabel){
                         return TRUE;
                    }
                    command = getDirCom(command, lind);
                    if(!command)
                         continue;
                    compSuc = executeCom(command);
                    free(lind);
                    free(optLabel);
                    free(command);
               }
               break;
               case order:
                    printf("order\n");              
               break;
          }
     }*/

/* get the optional label before the sentence */
boolean getOptLabel(char *label/*, int *ind*/){
     int temp;
     char curr;
     boolean firstColon = FALSE;

     lineInd = jumpSpaces(line,lineInd);
     temp = lineInd;    
     while(!isspace(curr = line[lineInd]) && curr != '\0'){
          if(lineInd-temp > LABEL_SIZE && firstColon == FALSE){
               fprintf(stderr,"error : label is too long, maximum label length is %d\n",LABEL_SIZE);
               return FALSE;
          }
          if(temp == lineInd && !isalpha(curr)){ /* label does not start with a letter */
               fprintf(stderr,"error : label must start with an alphabetic character\n");
               return FALSE;
          }
          if(curr != ':' && firstColon == TRUE && line[lineInd+1] != '\0' && !isspace(line[lineInd+1])){
               fprintf(stderr, "error : after label must be at list one space\n");
               return FALSE;
          }
          if(!isalnum(curr) && curr != ':'){ /* label include a not alphabetical or numberical characters or a colon */ 
               fprintf(stderr,"error : label must include only alphbetical and numerical characters\n");
               return FALSE;
          }
          /*if(curr == ':' && firstColon == TRUE){
               fprintf(stderr,"error: to many colons in label name, label must be in the form \" label: \"\n");
               return FALSE;
          }*/
          if(curr == ':')
               firstColon = TRUE;
          else 
               label[lineInd-temp] = curr;
          lineInd++;
     }
     label[lineInd-temp] = '\0';
     if(temp == lineInd)
          label = NULL;
     /**ind = i;*/
     return TRUE;
}

int getDirCom(char *command/*, int *ind*/){
     int /*i = *ind,*/ temp;
     int i;
     char curr;

     lineInd = jumpSpaces(line,lineInd);
     temp = lineInd;
     while((curr = line[lineInd]) != '\0' && !isspace(curr)){ /* reading the command */
          command[lineInd-temp] = curr;
          lineInd++;
     }
     command[lineInd-temp] = '\0';
     /**ind = lineInd;*/
     
     for(i = 0; i < DIR_COMS; i++){
          if(strcmp(command,dirCommands[i]))
               return i;
     }
     fprintf(stderr, "error : directive command - %s , is not valid.",command);
     fprintf(stderr, "Command must be: %s / %s / %s / %s\n",dirCommands[data],dirCommands[string],dirCommands[entry],dirCommands[external]);
     return -1;
}

/* ---------------------------- NEW -------------------------- */
static char **getParms(char *line){
     enum status{IN, COMMA, HASH, LQ, RQ, NUM, OUT};
     enum status state = IN;
     char **params = calloc(1,sizeof(char*));
     int i = 0, j = 0, sizeI = 1, sizeJ = 1;
     char curr;

     if(!isAlloc(params))
          return NULL;
     params[0][0] = '1'; /* not null value */
     *ind = jumpSpaces(line, *ind);

     while((curr = line[*ind]) != '\n'){
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
                    if(isspace(curr) && line[*ind-1] != '#'){
                         state = COMMA;
                         break;
                    }
                    if(line[*ind-1] != '#'){
                         fprintf(stderr, "error : no numerical number inserted after '#' label\n");
                         return NULL;
                    }
                    if(!isdigit(curr)){
                         fprintf(stderr, "error : decimal number must include only numerical digits\n");
                         return NULL;
                    }
                    if(line[*ind-1] != '#' && (curr == '+' || curr == '-')){
                         fprintf(stderr, "error : negative or positive sign must be in the start of the number\n");
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
                    if(!jumpSpaceComma(line,ind))
                         return NULL;
                    sizeI++;
                    state = IN;
               break;
               case LQ:

               case OUT:
                    return params;
          }
          (*ind)++;
     }
}

boolean jumpSpaceComma(char *line){
     int firstComma = 0;
     char curr;
     while((curr = line[*ind]) != '\0' && (isspace(curr) || curr == ',')){
          if(curr == ',')
               firstComma++;
          if(firstComma > 1){
               fprintf(stderr, "error : between parameters must seperate one comma only\n");
               return FALSE;
          }
          (*ind)++;
     }
     if(firstComma == 0){
          fprintf(stderr, "error : between parameters must seperate one comma\n");
          return FALSE;
     }
     return TRUE;
}

int main(){
     if(compile("test.txt") == TRUE)
          printf("compiled sucssesfuly\n");
     else
          printf("could not compile\n");    
     return 0;
}