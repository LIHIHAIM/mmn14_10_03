#include <stdio.h>
#include "interface.h"

int main(int argc, char *argv[]){
     int i = 1;
     while(argv[i]){
          if(!compile(argv[i]))
               fprintf(stderr, "could not compile Assembly file: \"%s\"\n",argv[i]);
          i++;
     }
     return 0;
}