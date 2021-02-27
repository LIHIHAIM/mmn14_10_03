#include <stdlib.h>
#include <string.h>
#include "ineterface.h"
#include "files.h"
#include "line.h"
#include "memory.h"
#include "statmentType.h"

#define FOREVER 1
#define LINE 81

typedef struct{
     enum dataType{intOrChar, reg, label};
     enum dataType type;
     union{
          word iOrCh; /* an integer or a character */ 
          word reg; /* register */
          word l; /* label */
     } param;
} paramType;

/* compile(): The function compiles an Assembly file and make one to three files in addition:
 file.ob - a binary file, which includes the memory....
 file.ent - an "entry" file, which includes the names of all the variable which other files can see and
            their address in the RAM.
 file.ext - an "extern" file, which includes the names of all the external variables (from other files) 
            and their calling address in the RAM.
*/
boolean compile(char *fileName){
     FILE *fd = openf(fileName,"r");
     char line[LINE]; /* array for handling a line of assembly code */
     int *lInd = calloc(1,sizoef(int)); /* the Line-Index */
     char *tempLine, *optLabel;
     
     statType type;
     boolean labelExist = FALSE;
     boolean compSuc = TRUE;

     int symTabSize = 1;
     symbolTable *symTab = calloc(symTabSize,sizeof(symbolTable));

     if(!isAlloc(symTab) || !isAlloc(lInd))
          return FALSE;
     
     if(!fd)
          return FALSE;
     while(FOREVER){
          resetCounters(); /* setting IC to 100 and DC to 0 */
          tempLine = readLine(fd,LINE); /* reading a line from the file */
          if(*tempLine == '\0') /* end of file */
              break;
          strcpy(line,tempLine);
          free(tempLine);

          optLabel = calloc(LABEL_SIZE,sizeof(char));
          if(!isAlloc(optLabel))
               return FALSE;
          if(!getOptLabel(optLabel)){ /* could not get a lable */
               compSuc = FALSE;
               continue;
          }
          if(optLabel) /* there is a lable */
               labelExist = TRUE;
          type = getStatType(line); /* finding the statment type (instruction/ directive/ balnk line/ comment) */

          switch(type){
               case blank: /* if the statment is a blank line or a comment then skip to the next line */
               case comment:
               continue;
               case directive:
                    int command = getDirCom(command);
                    switch(command){
                         case data:
                         case string:
                              char **params;
                              if(labelExist){
                                   if(isIlegalName(optLabel, symTab, symTabSize))  /* if label was all ready defined */
                                        compSuc = FALSE;
                                   else if(command == data){
                                        if(!addToSymTab(symTab, optLabel, ".data", symTabSize))
                                             return FALSE;
                                   }
                                   else if(command == string){
                                        if(!addToSymTab(symTab, optLabel, ".string", symTabSize))
                                             return FALSE;
                                   }
                                   symTabSize++;
                              }
                              params = getParams();
                              pushParams(params);
                              continue;
                         case external:
                              if(/* search(optLabel) */1){
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
                    if(thereIsLable == TRUE){
                         if(/* search(optLabel) */1){
                              /* some error */
                              compSuc = FALSE;
                              continue;
                         }
                         /*push(".code", IC, optLabel)*/
                         IC++;
                    }
                    int order = getOrder();
                    if(/*searchOrder(order) || !isValid(order) */1){
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

int main(){
     if(compile("test.txt") == TRUE)
          printf("compiled sucssesfuly\n");
     else
          printf("could not compile\n");    
     return 0;
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

