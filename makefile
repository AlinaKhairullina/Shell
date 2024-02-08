shell.o: shell.h fncs.c
	gcc -c fncs.c shell.o
res: shell.o shell.c
	gcc Shell.c shell.o -o res
run: res
	./res