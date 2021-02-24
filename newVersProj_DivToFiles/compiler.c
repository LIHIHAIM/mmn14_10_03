#include <stdlib.h>
#include <string.h>
#include "ineterface.h"
#include "files.h"
#include "line.h"
#include "memory.h"
#include "statmentType.h"

#define FOREVER 1
#define LINE 81

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
     statType type;
     boolean thereIsLable = FALSE;
     boolean compSuc = TRUE;

     int symTabSize = 1;
     symbolTable *symTab = calloc(symTabSize,sizeof(symbolTable));

     if(!isAlloc(symTab))
          return FALSE;
     
     if(!fd)
          return FALSE;
     while(FOREVER){
          char line[LINE]; /* array for handling a line of assembly code */
          int *lInd = calloc(1,sizoef(int)); /* the Line-Index */
          char *optLabel = calloc(LABEL_SIZE,sizeof(char));
          if(!isAlloc(optLabel) || !isAlloc(lInd))
               return FALSE;
          tempLine = readLine(fd,LINE);
          if(*tempLine == '\0')
              break;
          strcpy(line,tempLine);
          free(tempLine);

          if(!getOptLabel(optLabel)){ /* could not get a lable */
               compSuc = FALSE;
               continue;
          }
          if(optLabel) /* there is a lable */
               thereIsLable = TRUE;
          type = getStatType(line);

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
                              if(thereIsLable == TRUE){
                                   if(wasDefined(symTab, optLabel, symTabSize)){ /* if label was all ready defined */
                                        printf("error: label is already defined in this program");
                                        compSuc = FALSE;
                                        continue;
                                   }
                                   if(!addToSymTab(symTab, optLabel, DC, ".data",symTabSize))
                                        return FALSE;
                                   symTabSize++;
                                   /*DC++;*/
                              }
                              params = getParams();
                              pushParams(params/*, DC*/);
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
int main(){
     if(compile("test.txt") == TRUE)
          printf("compiled sucssesfuly\n");
     else
          printf("could not compile\n");    
     return 0;
}