CFLAGS = -O1

static:list.c main.c
	gcc $(CFLAGS) -c  -Wall list.c -o list.o
	ar rcs liblist.a list.o
	gcc -Wall -g main.c -static -L. -llist -o main

shared:list.c main.c
	gcc $(CFLAGS) -fPIC -shared list.c -o liblist.so
	gcc main.c -L. -llist -o main

dynamic:
	gcc -fPIC -shared list.c -o liblist.so
	gcc main.c -L. -llist -o main
	gcc  maindynamic.c -ldl -o maindynamic
	LD_LIBRARY_PATH=. ./maindynamic

run-static:
	./main

run-shared: shared
	LD_LIBRARY_PATH=. ./main


.PHONY:clean
clean:
	rm -f *.o *.a *.so
