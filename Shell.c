#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "shell.h"
// #define LINESIZE 256
// #define sep ";"
// #define space " "
// #define conv "|"
// void split_line1(char * line);
// void split_line2(char * token);
// char * brack(char * s);
// int b_cd (char * arg);
// int token_is_conv(char *s);
// int execute_cmd(char * s);
// int conveer(char *s);
// int b_cd (char * arg)//команда  cd
// {
//     char current[70];
//     getcwd(current, 70);
//     while (*arg == ' ')
//     arg++;
//     if (*arg != '.')
//     {
//         current[(strlen(current))] = '/'; // здесь не всегда правильно вставляет /
//         current[(strlen(current))] = '\0'; 
//         strcat(current, arg);
//         return chdir(current);
//     }
//     else 
//     {
//         arg++;
//         if ((*arg == '.') && (((*(arg + 1)) == ' ') || ((*(arg + 1)) == '\0'))) // if cd ..\0
//         {
//             *(arg + 1) = '\0';
//             char str[5] = "/../";
//             strcat(current, str);
//             return chdir(current);
//         }
//         if ((*arg) == '/') // cd ./smth
//         {
//             char * tmp = arg;
//             while ((*tmp != ' ') && (*tmp != '\0')) tmp++;
//             *tmp = '\0';
//             strcat(current, arg);
//             return chdir(current);
//         }
//         if ((*arg == '.') && ((*(arg + 1)) != '\0')) // if cd ../smth
//         {
//             arg--;
//             char * tmp = arg;
//             while ((*tmp != ' ') && (*tmp != '\0')) tmp++;
//             *tmp = '\0';
//             current[(strlen(current))] = '/';
//             current[(strlen(current)) ] = '\0';
//             strcat(current, arg);
//             return chdir(current);
//         }
//         else printf("Неверные аргументы для команды cd\n");
//     }
//     return 1;
// }
// char * read_line()
// {
//     unsigned size = LINESIZE;
//     char * line = malloc(sizeof(char)*size);
//     if (!line) 
//     {
//         perror("Ошибка при выделении памяти: ");
//         exit(1);
//     }
//     int i = 0;
//     int c;
//     while (1)
//     {
//         c = getchar();

//         if ((c == EOF) || (c == '\n'))
//         {
//             line[i] = '\0';
//             return line;
//         }
//         else 
//         {
//             line[i] = c;
//         }
//         i++;
//         if (i >= size)
//         {
//             size += LINESIZE;
//             line = realloc(line, size * sizeof(char));
//             if (!line) 
//             {
//                 perror("Ошибка при выделении памяти: ");
//                 exit(1);
//             }
//         }
//     }
// }
// int token_is_conv(char *s)
// {
//     for (int i = 0; i < strlen(s); i++)
//     {
//         if ((s[i] == '|') && (s[i + 1] != '|')) return 1;
//     }
//     return 0;
// }
// int execute_cmd(char * s)
// {
//     char ** args = malloc(sizeof(char*)*LINESIZE);
//     int pozition = 0;
//     int in = 0;
//     int out = 0;
//     int fd1, fd2;
//     while (*s == ' ')
//     {
//         s++;
//     }
//     char *c = s;
//     int counter = 0;
//     int status;
//     pid_t pid1;
//     char  *end;
//         if (*c == '(')
//         {
//             counter++;
//             c++;
//             s++;
//             while(1)
//             {
//                 if (*c == '(') counter++;
//                 if (*c == ')') counter--;
//                 if (counter == 0)
//                 {
//                     end = c;
//                     *end = '\0';
//                     c = s;
//                     while(*c != '\0')
//                     {
//                         if (*c == ':')
//                         *c = ';';
//                         if ((*c == '$') && (*(c + 1) == '$'))
//                         {
//                             *c = '&';
//                             *(c + 1) = '&';
//                             c++;
//                         }
//                         if ((*c == '!') && (*(c + 1) == '!'))
//                         {
//                             *c = '|';
//                             *(c + 1) = '|';
//                             c++;
//                         } 
//                         c++;
//                     }
//                     if ((pid1 = fork()) == 0)
//                     {
//                         char * new;
//                         new = brack(s);
//                         split_line1(new);
//                         exit(0);
//                     }
//                     waitpid(pid1, &status, 0);
//                     return status;

//                 }
//                 c++;
//             }
//         }
//     if ((*s == 'c') && (*(s + 1) == 'd'))
//     {
//         return b_cd(s + 2); //cd должен вернуть 0 в случае успеха
//     }
//     char *arg = strtok(s, space);
//     while(arg)
//     {
//         while(*arg == ' ')
//         arg++;
//         args[pozition] = arg;
//         if ((*arg == '>') || (*arg == '<'))
//         {
//             if (*arg == '>') in = pozition;
//             if (*arg == '<') out = pozition;
//         }
//         pozition++;
//         arg = strtok(NULL, space);
//     }
//     pid_t pid;
//     int stat;
//     if ((pid = fork()) == 0)
//     {
//         if (in || out) 
//         {
//             switch (*args[in])
//             {
//                 case '>':
//                     if (*(args[in] + 1) != '>') // > 
//                     fd1 = open(args[in + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
//                     else
//                     if (*(args[in] + 1) == '>') // >>
//                     fd1 = open(args[in + 1], O_WRONLY | O_APPEND | O_CREAT, 0666);
//                     dup2(fd1, 1);
//                     args[in] = NULL;
//                     args[in + 1] = NULL;
//                     break;
//                     default :
//                                 break;
//             }
//             switch (*args[out])
//             {
//                 case '<':
//                     fd2 = open(args[out + 1], O_RDONLY);
//                     dup2(fd2, 0);
//                     args[out] = NULL;
//                     args[out + 1] = NULL;
//                     break;
//                 default :
//                                 break;

//             }
//         }
//         execvp(args[0], args);
//         exit(1);
//     }
//     else{
//         waitpid(pid, &stat, 0);
//         if (stat) printf("status of %s : %d\n", args[0], stat);
//     }
//     return stat;
// }
// int conveer(char *s)
// {
//     int pozition = 0;
//     char ** args = malloc(sizeof(char*) * LINESIZE); //аргументы команд конвеера
//     char * arg = strtok(s, conv);
//     while(arg)
//     {
//         while (*arg == ' ') arg++;
//         args[pozition] = arg;
//         pozition++;
//         arg = strtok(NULL, conv);
//     }
//     int fd[pozition - 1][2]; // каналы
//     pid_t pid[pozition]; // для сыновей
//     for (int i = 0; i < pozition ; i++)
//     {
//         if (i != (pozition - 1)) pipe(fd[i]);
//         if ((pid[i] = (fork())) == 0)
//         {
//             char ** cmds = malloc(sizeof(char*)*LINESIZE); //аргументы команды
//             int k = 0;
//             char * cmd;
//             int in = 0, out = 0, f_in, f_out;
//             while (*args[i] == ' ' ) args[i]++;
//             cmd = strtok(args[i], space);
//             while(cmd)
//             {
//                 while(*cmd == ' ')
//                 cmd++;
//                 if ((*cmd == '>') || (*cmd == '<'))
//                 {
//                     if (*cmd == '>') in = k;
//                     if (*cmd == '<') out = k;
//                 }
//                 cmds[k] = cmd;
//                 k++;
//                 cmd = strtok(NULL, space);
//             }
//             if (in || out)
//                 {
//                     switch(*cmds[in])
//                     {
//                         case '>':
//                             if (*(cmds[in] + 1) == '\0') // > 
//                             {
//                                 f_in = open(cmds[in + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
//                                 dup2(f_in, 1);
//                                 cmds[in] = NULL;
//                                 cmds[in + 1] = NULL;
//                                 break;
//                             }
//                             else if (*(cmds[in] + 1) == '>') // >>
//                             {
//                                 f_in = open(cmds[in + 1], O_WRONLY | O_APPEND | O_CREAT, 0666);
//                                 dup2(f_in, 1);
//                                 cmds[in] = NULL;
//                                 cmds[in + 1] = NULL;
//                                 break;
//                             }
//                         default :
//                             break;

//                     }
//                     switch (*cmds[out])
//                     {
//                         case '<': // <
//                             {
//                                 f_out = open(cmds[out + 1], O_RDONLY);
//                                 dup2(f_out, 0);
//                                 cmds[out] = NULL;
//                                 cmds[out + 1] = NULL;
//                                 break;

//                             }
//                         default : break;
//                     }
//                 }
//             if (i == 0) //1st cmd
//             {
//                 if (in == 0) dup2(fd[i][1],1);
//                 close(fd[i][0]);
//                 execvp(cmds[0], cmds);
//                 exit(1);
//             }
//             else if (i != pozition - 1) //other sons
//             {
//                 if (in == 0) dup2(fd[i][1],1);
//                 if (out == 0) dup2(fd[i - 1][0], 0);
//                 close(fd[i][0]);
//                 close(fd[i - 1][1]);
//                 for (int j = 0; j < i - 1 ; j++)
//                 {
//                     close (fd[j][0]);
//                     close (fd[j][1]);
//                 }
//                 execvp(cmds[0], cmds);
//                 exit(1);
//             }
//            else if (i == pozition - 1) //last cmd
//            {
//                 if (out == 0) dup2(fd[i - 1][0], 0);
//                 close(fd[i - 1][1]);
//                 for (int j = 0; j < i - 1 ; j++)
//                 {
//                     close (fd[j][0]);
//                     close (fd[j][1]);
//                 }
//                 execvp(cmds[0], cmds);
//                 exit(1);
//            }
//         }
//     }
//     int status_last;
//     for (int i = 0; i < pozition; i++)
//             {
//                 if (i != pozition - 1) 
//                 {
//                     close(fd[i][0]);
//                     close(fd[i][1]);
//                 }
//                 waitpid(pid[i], &status_last, 0);
//             }
//     return status_last;
// }
// void split_line2(char * token) // && ||
// {
//     char * c = token;
//     char *tmp;
//     int flg = 0;
//     while (*c != '\0')
//     { 
//         c = token;
//         while (*c == ' ') c++;
//         token = c;
//         if ((strcmp(token , "exit")) == 0) exit(0);
        
//         while (*c != '\0')
//         {
//             if ((*c == '&') && (*(c + 1) == '&')) //
//             {
//                 *(c ) = '\0'; 
//                 c += 2;
//                 break;
//             }
//             if ((*c == '|') && (*(c + 1) == '|')) //
//             {
//                 *(c ) = '\0'; 
//                 c += 2;
//                 break;
//             }
//             c++;
//         }
//         tmp = c;
//         int k = token_is_conv(token);
//         if (k)
//         {
//            if  (!(conveer(token)))
//             token = tmp;
//         }
//         else 
//         {
//             flg = execute_cmd(token);
//             if ((!flg) &&  (*(tmp - 1) != '|')) //выполнилось
//             {
//                 token = tmp;
//             }
//             else
//             if ((flg) &&  (*(tmp - 1) == '|')) // если не выполнилось и ||
//             {
//                 token = tmp;
//             }
//             else
//             break;
//         }
//     }
//     return;
// }
// void split_line1(char * line) //разделяем все команды перечисленные через ;
// {
//     int pozition = 0;  
//     char ** tokens = malloc(sizeof(char*)*LINESIZE);
//     char *str = strtok(line, sep);
//     while(str)
//     {
//         tokens[pozition] = str;
//         pozition++;
//         str = strtok(NULL, sep);
//     }
//     for (int i = 0; i < pozition; i++)
//     {
//         char * tmp = tokens[i];
//         int fon  = 0, j = 0, counter = 0;
//         while(*tmp != '\0')
//         {
//             if (*tmp == '(') counter++;
//             if (*tmp == ')') counter--;
//             if ((*tmp == '&') && (*(tmp + 1) != '&') && (*(tmp - 1) != '&') && (counter == 0) )
//             {
//                 fon = j;
//             }
//             j++;
//             tmp++;
//         }
//         if (fon)
//         {
//             char * tmp2 = tokens[i] + fon;
//             tmp2++;
//             tokens[i][fon] = '\0';
//             pid_t pid1, pid2;
//             if ((pid1 = fork()) == 0)
//             {
//                 if ((pid2 = fork()) == 0)
//                 {
//                     signal(SIGINT, SIG_IGN);
//                     int fd = open("/dev/null", O_RDONLY);
//                     dup2(fd, 0);
//                     close(fd);
//                     split_line2(tokens[i]);
//                     exit(0);
//                 }
//                 exit(0);
//             }
//             split_line2(tmp2);
//             waitpid(pid1, NULL, 0);
//         }
//         else split_line2(tokens[i]);
//     }
//     return;
// }
// char * brack(char * s)
// {
//     int counter = 0;
//     char *line = s;
//     while(*line != '\0')
//     {
//         if (*line == '(')
//             counter++;
//         if (*line == ')')
//             counter--;
//         if ((*line ==  ';') && (counter > 0))
//             *line = ':';
//         if ((*line ==  '&') && (*(line + 1) ==  '&') && (counter > 0))
//             {*line = '$'; *(line + 1) = '$';}
//         if ((*line ==  '|')&& (*(line + 1) ==  '|') && (counter > 0))
//             {*line = '!'; *(line + 1) = '!';}
//         line++;
//     }
//     return s;
// }
int main()
{
    char current[1024];
    while (1) {
		getcwd(current,1024);
		printf("~%s$ ",current);
        char * line = read_line();
        //printf("%s\n", line);
        char * line_new = brack(line);
        split_line1(line_new);
    }
    return 0;
}
