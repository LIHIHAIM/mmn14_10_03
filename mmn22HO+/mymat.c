
/* [mmn 22 - mymat.c file (main)]
This file implements the user - matrix calculator interface.  
The proccesing of the command-line (inserted by the user) and the cheking of it are 
taking place here.
The user enters the command in the form: functionName param1, param2 ... paramN
If the command was no inserted correctly a correlated error will be printed and 
the user could insert the next command.

# If a memory allocation failes the program will terminate imidiately
  after sending an error message to the user.

Author: Uri K.H.    ID: 215105321    
Tutor: Danny        Date: 31.12.2020 */

#include <ctype.h> 
#include <string.h> 
#include <float.h> /* for DBL_MAX (the maximum double value) */
#include "mat.h" 

#define MAXPRM SIZE * SIZE /* Maximum numeric parameters in read_mat()*/
#define CMD_LINE_LEN 250 /* The command-line length*/
#define FOREVER 1

typedef char* string;
typedef int boolean;

enum {NO, YES}; /* If the current character is a comma */
enum {FALSE, TRUE}; /* The boolean values */

static int comma, cmdInd; /* if the character is a comma (flag), and the command line array index*/
static string cmdln; /* The command-line array */

/* Prototypes of the functions in this file */
static void printArr(string *);
static boolean isOnlySpaces(void);
static string getFuncName(void);
static string getMatName(void);
static int isValid_funcName(string, string *);
static int isValid_matName(string, string *);
static boolean isThereComma(void);
static boolean isExterText(void);
static double getScalar(int);
static double *getParams(void);
static int *getTripleMatsParams(string *);
static boolean areConsecutiveCommas(void);


int main() {     
     enum {READ, PRINT, ADD, SUB, MUL, MUL_SCALAR, TRANS, STOP}; /*names of possible operations on matrices*/
     
     /* The matrices which the calculator will operate on */ 
     mat MAT_A = {0}, MAT_B = {0}, MAT_C = {0}, MAT_D = {0}, MAT_E = {0}, MAT_F = {0};  
     string matNames[] = {"MAT_A", "MAT_B", "MAT_C", "MAT_D", "MAT_E", "MAT_F", NULL};
     /* The valid names of the functions which the user might insert */
     string funcNames[9] = { 
          "read_mat", "print_mat", "add_mat", 
          "sub_mat", "mul_mat", "mul_scalar", 
          "trans_mat", "stop", NULL
     };
     /* Assigning the matrices adresses into an array */
     mat *mats[7]; 
     mats[0] = &MAT_A, mats[1]= &MAT_B, mats[2] = &MAT_C;
     mats[3] = &MAT_D, mats[4] = &MAT_E, mats[5] = &MAT_F, mats[6] = NULL;

     printf("\n\t\t\t\t~~ This is a matrix calculator ~~\n");
     printf("\tInstractions: \n\t1. Insert an operation name on matrices from the list below:\n\t");
     printArr(funcNames);
     printf("\n\t2. Eneter the matrix/ces name/s on which the function will operate:\n\t");
     printArr(matNames);
     printf("\n\t* The parameters for every function shall be separated by commas.\n");
     printf("\t* Every command line will be %d characters long and shall be writen in one line.\n\n", CMD_LINE_LEN);

     while(FOREVER){
          string funcName; /* the function name*/
          int isValidFunc, i = 0;
          cmdln = (char *)calloc(CMD_LINE_LEN, sizeof(char)); /* allocating memory for a new command line*/
          cmdInd = 0; /* the first index of the inserted command line */
          comma = NO; /* there is no comma */

          if(!cmdln){
               printf("[error while allocating memory for a new command line]\n");
               exit(0);
          }
          printf("\n>>> ");
          fgets(cmdln,CMD_LINE_LEN,stdin);

          if(cmdln[0] == '\0'){ /* if the input was EOF */
               printf("\n EOF (ctrl + d) command is not allowed:\n");
               printf(" If you wish to terminate the program use the command 'stop'\n");
               exit(0);
          }
          if(isOnlySpaces() == TRUE)
               continue;
          printf("\n [Command is:] %s", cmdln);

          funcName = getFuncName();
          if(funcName == NULL)
               continue;

          isValidFunc = isValid_funcName(funcName, funcNames);
          if(isValidFunc == -1) /* if function name is not valid */
               continue;
          /* checking if there is a comma between the name of the function to it's parameters */
          i = cmdInd;
          while(isspace(cmdln[i]))
               i++;
          if(cmdln[i] == ','){
               free(funcName);
               printf("Ilegal comma\n");
               continue;
          }

          switch(isValidFunc){ 
               case READ: /* read_mat() */
                    {
                         string matName = getMatName();
                         int matInd; /* the matrix index in the mat names array */
                         if(matName == NULL) /* if the matrix is not semi valid */
                              break;
                         matInd = isValid_matName(matName, matNames);
                         if(matInd != -1){ /* if the mat name is valid */ 
                              double *params = getParams();
                              if(params == NULL){
                                   free(matName);
                                   break;
                              }
                              read_mat(mats[matInd], params);
                              free(params);
                         }
                         free(matName);
                    }                      
                    break;
               case PRINT: /* print_mat() */
                    {
                         string matName = getMatName();
                         int matInd;
                         if(matName == NULL) /* if the matrix is not semi valid */
                              break;
                         matInd = isValid_matName(matName, matNames);
                         if(matInd != -1){ /* if the mat name is valid */
                              if(isExterText() == TRUE){
                                   free(matName);
                                   break;
                              }
                              print_mat(mats[matInd]);
                         }
                         free(matName);
                    }
                    break;
               case ADD: /* add_mat() */
                    {
                         /* getting an array which containes the indexes of three matrices */
                         int *matsInds = getTripleMatsParams(matNames); 
                         if(matsInds != NULL)
                              add_mat(mats[matsInds[0]], mats[matsInds[1]], mats[matsInds[2]]);
                         free(matsInds);
                    }
                    break;
               case SUB: /* sub_mat() */
                    {
                         /* getting an array which containes the indexes of three matrices */
                         int *matsInds = getTripleMatsParams(matNames);
                         if(matsInds != NULL)
                              sub_mat(mats[matsInds[0]], mats[matsInds[1]], mats[matsInds[2]]);
                         free(matsInds);
                    }
                    break;
               case MUL: /* mul_mat() */
                    {
                         /* getting an array which containes the indexes of three matrices */
                         int *matsInds = getTripleMatsParams(matNames);
                         if(matsInds != NULL)
                              mul_mat(mats[matsInds[0]], mats[matsInds[1]], mats[matsInds[2]]);
                         free(matsInds);
                    }
                    break;
               case MUL_SCALAR: /* mul_scalar() */
                    {
                         string matName1, matName2;
                         int matInd1, matInd2;
                         double scalar;

                         matName1  = getMatName();
                         if(matName1 == NULL) /* if the matrix is not semi valid */
                              break;
                         matInd1 = isValid_matName(matName1, matNames);
                         if(matInd1 != -1){ /* if the matrix name is valid */
                              scalar = getScalar(0);
                              if(scalar == DBL_MAX){ /* if couldn't get a scalar */
                                   free(matName1); 
                                   break;
                              }
                              if(isThereComma() != TRUE || areConsecutiveCommas() != FALSE){ 
                                   free(matName1); 
                                   break;
                              }
                              matName2  = getMatName();
                              if(matName2 == NULL){ /* if the matrix is not semi valid */
                                   free(matName1); 
                                   break;
                              }
                              matInd2 = isValid_matName(matName2, matNames);
                              if(matInd2 != -1){ /* if the matrix name is valid */
                                   if(isExterText() == FALSE)
                                        mul_scalar(mats[matInd1], scalar, mats[matInd2]);
                              }
                         }
                         free(matName1); 
                         free(matName2);
                    }
                    break;
               case TRANS: /* trans_mat() */
                    {
                         string matName1, matName2;
                         int matInd1, matInd2;

                         matName1 = getMatName();
                         if(matName1 == NULL)  /* if the matrix is not semi valid */
                              break;
                         matInd1 = isValid_matName(matName1, matNames);
                         if(matInd1 != -1){ /* if the matrix name is valid */
                              if(isThereComma() != TRUE || areConsecutiveCommas() != FALSE){
                                   free(matName1); 
                                   break;
                              }
                              matName2 = getMatName();
                              if(matName2 == NULL){  /* if the matrix is not semi valid */
                                   free(matName1); 
                                   break;
                              }
                              matInd2 = isValid_matName(matName2, matNames);
                              if(matInd2 !=-1){ /* if the matrix name is valid */
                                   if(isExterText() == FALSE)
                                        trans_mat(mats[matInd1], mats[matInd2]);
                              }
                         }
                         free(matName1);
                         free(matName2);
                    }
                    break;
               case STOP: /* stop() */
                    {
                         if(isExterText() == FALSE)
                              stop();
                    }
                    break;
          }
          free(cmdln);
          free(funcName);
     }
     return 0; /*end of main*/
}

/* printArr: Prints a visual representation of a String array closed up with [] 
 parameters: an array of strings 
 returns: void */
static void printArr(string *arr){
     int i = 0;
     printf("[ %s", arr[i]);
     i++;
     while(arr[i] != NULL){
          printf(", %s",arr[i]);
          i++;
     }
     printf(" ]\n");
     return;
}

/* isOnlySpaces: Returns if the command line is only with spaces and return TRUE (1) if yes,
 end FALSE (0) if not. */
static boolean isOnlySpaces(void){
     int i = 0;
     while(isspace(cmdln[i])){
          if(cmdln[i] == '\n')
               return TRUE;
          i++;
     }
     return FALSE;
}

/* getFunName: Scans the command line for a function name and returns it as a string (with a '\0' in the end). 
 If detected a 'enter' then the returned value will be NULL. Also, if could not detect 
 a semi valid function name a suitable error will be printed and NULL will be returned. */
static string getFuncName(void){
     int funcSize = 1, tempInd;
     string funcName = (string)calloc(funcSize, sizeof(char));

     if(!funcName){
          printf("[error: while allocating memory for the function name]\n");
          exit(0);
     }

     while(isspace(cmdln[cmdInd]))
          cmdInd++;
     tempInd = cmdInd;
     while(isalpha(cmdln[cmdInd]) || cmdln[cmdInd] == '_') {
          funcName = (string)realloc(funcName,funcSize * sizeof(char));
          if(!funcName){
               printf("[error: while allocating memory for the function name]\n");
               exit(0);
          }
          funcName[funcSize-1] = cmdln[cmdInd];
          funcSize++;
          cmdInd++;
     }

     if(tempInd == cmdInd){
          free(funcName);
          printf(" Undefined command name\n");
          return NULL;
     }

     funcName = (string)realloc(funcName, (++funcSize) * sizeof(char));
     if(!funcName){
          printf("[error while allocating memory for the function name]\n");
          exit(0);
     }
     funcName[funcSize-1] = '\0';
     return funcName;
}

/* getMatName: Scans the command line for a matrix name in the form: MAT_[A-F]
 If a compatible name has been found then it will be returned as a String (with '\0' in the end).
 Else, a suitable error will be printed. */
static string getMatName(void){
     int nameSize = 1, tempInd;
     string matName = (string)calloc(nameSize, sizeof(char));

     if(!matName){
          printf("[error while allocating memory for the mat name]\n");
          exit(0);
     }
     while(isspace(cmdln[cmdInd]))
          cmdInd++;
     tempInd = cmdInd;
     while(isalpha(cmdln[cmdInd]) || cmdln[cmdInd] == '_'){
          matName = (string )realloc(matName, nameSize * sizeof(char));
          if(!matName){
               printf("[error while allocating memory for the mat name]\n");
               exit(0);
          }
          matName[nameSize-1] = cmdln[cmdInd];
          cmdInd++;
          nameSize++;
     }
     if(tempInd == cmdInd){ /* if there is no matrix name where expected */
          free(matName);
          printf(" Missing argument\n");
          return NULL;
     }
     if(cmdln[cmdInd] != ',' && !isspace(cmdln[cmdInd])){ /* if after the matrix name ther is no comma or space 
     then the matrix name is not valid */
          free(matName);
          printf(" Undefined matrix name\n");
          return NULL;
     }
     comma = NO; 
     if(cmdln[cmdInd] == ',')
          comma = YES;
     matName = (string)realloc(matName, (++nameSize) * sizeof(char));
     if(!matName){
          printf("[error while allocating memory for the mat name]\n");
          exit(0);
     }
     matName[nameSize-1] = '\0'; /* adding EOF to end of the char array to form a string*/
     return matName;
}

/* isValid_funcName: Gets a function name and a list of the valid function names. 
 If the function name appears on the list then the index which it appears int will be returned.
 Else a suitable error will be printed and -1 will be returned. */
static int isValid_funcName(string funcName, string *nameList){
     int i;
     
     for(i = 0; nameList[i] != NULL; i++){    
          if(strcmp(funcName,nameList[i]) == 0)
               return i;          
     }
     printf(" Undefined command name\n");
     return -1;
}

/* isValid_matName: Gets a matrix name and a list of the valid matrix names. 
 If the matrix name appears on the list then the index which it appears int will be returned.
 Else a suitable error will be printed and -1 will be returned. */
static int isValid_matName(string matName, string *nameList){
     int i;

     for(i = 0; nameList[i] != NULL; i++){
          if(strcmp(matName,nameList[i]) == 0)
               return i;
     }
     printf(" Undefined matrix name\n");
     return -1;
}

/* isThereComma: Checks if there is a comma in the cmdln (checking from the current index).
 If yes, the index will grow in 1, comma will be YES and TRUE (1) will be returned.
 Else FALSE (0) will be returned and a suitable error will be printed. */
static boolean isThereComma(void){
     while(isspace(cmdln[cmdInd])){
          cmdInd++;
     }
     if(cmdln[cmdInd] == ','){
          cmdInd++;
          comma = YES;
          return TRUE;
     }
     printf(" Missing comma\n");
     return FALSE;
}

/* isExterText: Checks if there is any text after the current index in the command line.
 If there is a suitable error will be printed and TRUE (1) will be returned.
 Else FALSE (0) will be returned. */
static boolean isExterText(void){
     while(cmdln[cmdInd] != '\0'){
          if(!isspace(cmdln[cmdInd])){
               printf(" Extraneous text after end of command\n");
               return TRUE;
          }
          cmdInd++;
     }
     return FALSE;
}

/* getScalar: Scans the command line for a decimal number. If an error acurred while scanning, the 
 suitable error will be printed and the maximum decimal (double) value will be returned. If a decimal
 number was found it will be returned. */
static double getScalar(int readOrMul){
     int strNumSize = 1, i = 0, curr, tempInd;
     double scalar;
     string strNum = (string)calloc(strNumSize, sizeof(char));
     boolean doubleDec = FALSE; /* There are two decimal points in the same number */
     boolean doubleMin = FALSE; /* There are two minus signs in the same number */
     
     if(!strNum){
          printf("[error: while allocating memory for a param]\n");
          exit(0);
     }
     if(isThereComma() != TRUE || areConsecutiveCommas() != FALSE)
          return DBL_MAX;
     while(isspace(cmdln[cmdInd]) && cmdln[cmdInd] != '\0')
          cmdInd++;
     tempInd = cmdInd;
     while(!isspace(cmdln[cmdInd]) && cmdln[cmdInd] != '\0' && cmdln[cmdInd] != ','){
          if(isdigit(cmdln[cmdInd]) || cmdln[cmdInd] == '.' || cmdln[cmdInd] == '-'){
               curr = cmdln[cmdInd];
               if(curr == '.' && doubleDec == FALSE)
                    doubleDec = TRUE;
               else if(curr == '-' && doubleMin == FALSE)
                    doubleMin = TRUE;
               else if(curr == '.' || curr == '-'){ /* There are more than two minus signs or decimal points in this number */
                    if(readOrMul == 0) /* the method is mul_scalr*/
                         printf(" Argument is not a scalar\n");
                    else /* the method is read_mat */
                          printf(" Argument is not a real number\n");
                    
                    return DBL_MAX;
               }
               strNum = (char *)realloc(strNum, (++strNumSize)*sizeof(char));
               if(!strNum){
                    printf("[error: while allocating memory for a param]\n");
                    exit(0);
               }
               strNum[i] = curr;
               i++;
               cmdInd++;
          }
          else{ /* The number included a differnt character from '.' / '-' / '0-9' */
               if(readOrMul == 0) /* the method is mul_scalr*/
                    printf(" Argument is not a scalar\n");
               else /* the method is read_mat */
                    printf(" Argument is not a real number\n");
               return DBL_MAX;
          }
     }
     if(cmdInd == tempInd){ /* If there weren't any numbers in the command line */
          free(strNum);
          printf(" Missing argument\n");
          return DBL_MAX;
     }
     strNum[i] = '\0';
     scalar = atof(strNum);
     comma = NO; /* a decimal number was found so there is no comma in those indexes */
     return scalar;                              
}

/* getParams: Scans the command line for decimal numbers. If an error acurred while scanning, the 
 suitable error will be printed and NULL will be returned. The scaned numbers will be returned in
 an array. */
static double *getParams(void){
     int paramInd = -1;
     double *params = (double *)calloc(MAXPRM, sizeof(double));
     if(!params){
          printf("[error: while allocating memory for params]\n");
          exit(0);
     }

     while(cmdln[cmdInd] != '\0' && paramInd+1 < MAXPRM){
          if(isspace(cmdln[cmdInd]))
               cmdInd++;
          else {
               params[++paramInd] = getScalar(1);
               if(params[paramInd] == DBL_MAX){ /* if an error acurred while scanning a number */
                    free(params);
                    return NULL;
               }
          }
     }
     
     if(paramInd == -1){ /* If there weren't any numbers in the command line */
          free(params);
          printf(" Missing argument\n");
          return NULL;
     }
     return params;
}

/* getTripleMatsParams: Scans the command line for Three matrix names. 
 If an error acurred while scanning the command line the suitable error will be printed 
 and NULL will be returned. The scanned matrix names will be returned in an array in the
 form of their indexes in the matrix name list. */
static int *getTripleMatsParams(string *matNames){
     string matName1, matName2, matName3;
     int matInd1, matInd2, matInd3;

     matName1 = getMatName();
     if(matName1 == NULL){ /* if the matrix is not semi valid */
          free(matName1);
          return NULL;
     }
     matInd1 = isValid_matName(matName1, matNames);
     if(matInd1 != -1){ /* if the mat name is valid */
          if(isThereComma() != TRUE || areConsecutiveCommas() != FALSE){
               free(matName1);
               return NULL;
          }
          matName2 = getMatName();
          if(matName2 == NULL){ /* if the matrix is not semi valid */
               free(matName2);
               return NULL;
          }
          matInd2 = isValid_matName(matName2, matNames);
          if(matInd2 !=-1){ /* if the mat name is valid */
               if(isThereComma() != TRUE || areConsecutiveCommas() != FALSE){
                    free(matName1);
                    free(matName2);
                    return NULL;
               }
               matName3 = getMatName();
               if(matName3 == NULL){ /* if the matrix is not semi valid */
                    free(matName1);
                    free(matName2);
                    free(matName3);
                    return NULL;
               }
               matInd3 = isValid_matName(matName3, matNames);
               if(matInd3 != -1){ /* if the mat name is valid */
                    int *matsInds = (int *)calloc(3, sizeof(int));
                    if(!matsInds){
                         printf("error: while allocating memory to mats indeces array\n");
                         exit(0);
                    }
                    if(isExterText() == TRUE){
                         free(matName1);
                         free(matName2);
                         free(matName3);
                         return NULL;
                    }
                    matsInds[0] = matInd1;
                    matsInds[1] = matInd2;
                    matsInds[2] = matInd3;
                    return matsInds;
               }
          }
               
     }
     free(matName1);
     return NULL;
}

/* areConsecutiveCommas: Checks if there are two (or more) consecutive commas in the command line 
 (from the current index). If yes, then a suitable error will be printed and TRUE (1) will be returned. 
 Else, FALSE (0) will be returned. */
static boolean areConsecutiveCommas(void){
     while(isspace(cmdln[cmdInd]) || cmdln[cmdInd] == ','){
          if(cmdln[cmdInd] == ',' && comma == YES){
               printf(" Multiple consecutive commas\n");
               return TRUE;
          }
          cmdInd++;
     }
     return FALSE;
}