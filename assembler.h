#include <ctype.h> /* for isspace() */ 

#define MAX_RAM_SIZE 4096
#define REGISTERS 8
#define LINE 81

typedef enum {FALSE /* 0 */, TRUE /* 1 */} boolean;
typedef enum {blank, comment, directive, order} senType; /* the different sentences types */
enum wordType {mainWord = 1, address, num};

senType getSenType(char *);
int jumpSpaces(char *, int);

typedef union{
     enum wordType type;
     struct{
          unsigned int dest:2;
          unsigned int source:2;
          unsigned int funct:4;
          unsigned int opcode:4;
     } mainWord;

     struct{
          unsigned int address:12;
          int num:12;
     } scndWord;
} word;

typedef struct{
     int r:12;
} reg;

reg regs[REGISTERS];
char line[LINE];
boolean compSuc;
int IC, DC, lineInd;