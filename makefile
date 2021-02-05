assemble: compiler.o files.o sentenceType.o memory.o filesAndMem.h assembler.h 
	gcc -g -ansi -Wall -pedantic compiler.o files.o memory.o sentenceType.o -o assemble
compiler.o: compiler.c filesAndMem.h assembler.h
	gcc -c -ansi -Wall -pedantic compiler.c -o compiler.o
files.o: files.c filesAndMem.h
	gcc -c -ansi -Wall -pedantic files.c -o files.o
sentenceType.o: sentenceType.c assembler.h
	gcc -c -ansi -Wall -pedantic sentenceType.c -o sentenceType.o
memory.o: memory.c filesAndMem.h
	gcc -c -ansi -Wall -pedantic memory.c -o memory.o