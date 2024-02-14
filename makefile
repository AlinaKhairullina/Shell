shell.o: shell.h fncs.c
	gcc -c fncs.c -o shell.o
res: shell.o Shell.c
	gcc main.c shell.o -o res
run: res
	./res
