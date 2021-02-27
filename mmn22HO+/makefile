mymat: mymat.o mat.o mat.h
	gcc -g -Wall -ansi -pedantic  mymat.o mat.o -o mymat
mymat.o: mymat.c mat.h
	gcc -c -Wall -ansi -pedantic  mymat.c -o mymat.o
mat.o: mat.c mat.h
	gcc -c -Wall -ansi -pedantic  mat.c -o mat.o
	
clean:
	rm -f *.o
