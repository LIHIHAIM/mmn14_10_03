#include <stdio.h>
#include "ineterface.h"

int main(int argc, char *argv[]){
     int i = 1;
     while(argv[i]){
          if(compile(argv[i] != FALSE)){
               strcat(argv[i],".as");
               printf("could not compile Assembly file: \"%s\"\n", argv[i]);
          }
          i++;
     }
     return 0;
}
