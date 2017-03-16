static:list.c main.c
	gcc -c  -Wall list.c -o list.o
	ar rcs liblist.a list.o
	gcc -Wall -g main.c -static -L. -llist -o main

shared:list.c main.c
	gcc -fPIC -shared list.c -o liblist.so
	gcc main.c -L. -llist -o main

run-static:
	./main

run: shared
	LD_LIBRARY_PATH=. ./main


.PHONY:clean
clean:
	rm -f *.o *.a *.so
