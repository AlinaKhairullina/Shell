shell.o: shell.h fncs.c
	gcc -c fncs.c -o shell.o
res: shell.o Shell.c
	gcc Shell.c shell.o -o res
run: res
	./res
