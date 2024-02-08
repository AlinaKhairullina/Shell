#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "shell.h"
int main()
{
    char current[1024];
    while (1) {
		getcwd(current,1024);
		printf("~%s$ ",current);
        char * line = read_line();
        char * line_new = brack(line);
        split_line1(line_new);
    }
    return 0;
}