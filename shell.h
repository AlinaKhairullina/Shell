#define LINESIZE 256
#define sep ";"
#define space " "
#define conv "|"
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
char * read_line();
void split_line1(char * line);
void split_line2(char * token);
char * brack(char * s);
int b_cd (char * arg);
int token_is_conv(char *s);
int execute_cmd(char * s);
int conveer(char *s);
int b_cd (char * arg);