#define FUNCS 16

typedef enum {FALSE /* 0 */, TRUE /* 1 */} boolean;

typedef struct {
     char *name;
     int opcode;
     int funct;
} func;

func funcTable[FUNCS] = {
     {"mov",0,0},{"cmp",1,0},{"add",2,10},{"sub",2,11},
     {"lea",4,0},{"clr",5,10},{"not",5,11},{"inc",5,12},
     {"dec",5,13},{"jmp",9,10},{"bne",9,11},{"jsr",9,12},
     {"red",12,0},{"prn",13,0},{"rts",14,0},{"stop",15,0}
};

void getOpcode(char *funcName){
     
}