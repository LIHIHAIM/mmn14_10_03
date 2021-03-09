#include <stdlib.h>
#include <string.h>
#include "ineterface.h"
#include "files.h"
#include "line.h"
#include "memory.h"
#include "statmentType.h"

#define FOREVER 1
#define LINE_LEN 81
#define MAX_SUFIX_LEN 4

char *addSufix(char *, char *);

/* compile(): The function compiles an Assembly file and make one to three files in addition:
 file.ob - a binary file, which includes the memory....
 file.ent - an "entry" file, which includes the names of all the variable which other files can see and
            their address in the RAM.
 file.ext - an "extern" file, which includes the names of all the external variables (from other files) 
            and their calling address in the RAM.
*/
boolean compile(char *fileName){
     /* files variables */
     FILE *fd;
     char *tempFileName = malloc(strlen(fileName) + MAX_SUFIX_LEN + 1);
     /* line variables */
     char line[LINE_LEN];             /* array for handling a line of assembly code */
     int *lInd = malloc(sizoef(int)); /* the Line-Index */
     char *tempLine, *optLabel;
     /* label and compilation variables and falgs */
     statType type;
     boolean labelExist = FALSE;
     boolean compSuc = TRUE;
     boolean pushed = TRUE;
     /* teh symbol-table varibles */
     int symTabSize = 1;

     if (!isAlloc(lInd) || !isAlloc(tempFileName)){
          free(lInd);
          free(tempFileName);
          return ERROR;
     }

     fd = openf(addSufix(fileName, ".as", tempFileName), "r");
     if (!fd)
          return TRUE;
     resetCounters(); /* setting IC to 100 and DC to 0 */
     while (FOREVER)
     {
          tempLine = readLine(fd, LINE_LEN); /* reading a line from the file */
          if (*tempLine == '\0')             /* end of file */
               break;
          strcpy(line, tempLine);
          free(tempLine);

          optLabel = malloc(LABEL_SIZE);
          if (!isAlloc(optLabel))
               return ERROR;
          if (!getOptLabel(optLabel, line, lInd)) /* could not get a lable */
               compSuc = FALSE;
          if (optLabel) /* there is a label (label is not NULL) */
               labelExist = TRUE;
          type = getStatType(line); /* finding the statment type (instruction/ directive/ balnk line/ comment) */

          switch (type)
          {
          case blank:
          case comment:
               continue;
          case directive:
               int command = getDirCom(command);
               switch (command){
               case data:
               case string:
                    if (labelExist){
                         if (isIlegalName(optLabel, symTab, symTabSize)) /* if label was all ready defined */
                              compSuc = FALSE;
                         else if (command == data){
                              if (!addToSymTab(symTab, optLabel, "data", symTabSize))
                                   return FALSE;
                         }
                         else if (command == string){
                              if (!addToSymTab(symTab, optLabel, "string", symTabSize))
                                   return FALSE;
                         }
                         symTabSize++;
                    }
                    if (!(pushed = pushData(line, lInd)))
                         compSuc = FALSE;
                    else if (pushed == ERROR)
                         return ERROR;
                    continue;
               case external:
                    if (labelExist){
                         isIlegalName(optLabel);
                         printf("warnning: a label before the directive .extern is meaningless\n");
                    }
                    if (!(pushed = pushExtern(line, lInd)))
                         compSuc = FALSE;
                    else if (pushed == ERROR)
                         return ERROR;
                    continue;
               case entry:
                    continue;
               }
               break;
          case order:
               int order;
               /* Lihis enum */
               if (thereIsLable == TRUE){
                    if (/* search(optLabel) */ 1){
                         /* some error */
                         compSuc = FALSE;
                         continue;
                    }
                    /*push(".code", IC, optLabel)*/
                    IC++;
               }
               int order = getOrder();
               if (/*searchOrder(order) || !isValid(order) */ 1){
                    /* some error */
                    compSuc = FALSE;
                    continue;
               }
               switch (order){
                    /* for every order */
               }
               break;
          }
     }
     if (compSuc == ERROR)

          /* */
          while (FOREVER){
          }
     fclose(fd);
     free(tempFileName);
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

char *addSufix(char *dest, char *suffix, char *tempNam){
     strcpy(tempNam, dest);
     strcat(tempNam, suffix);
     return tempNam;
}
