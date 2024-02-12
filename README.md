# SHELL
***
## The following operations may be present on the command line (listed in descending order of priority):   

    |, >, >>, <
 
    &&, ||
  
    ;, &
  
## brackets and an arbitrary number of spaces are also acceptable in the command.

  ```|``` - same as "OR"

 ``` cmd1 | cmd2 | ... | cmdN``` - pipeline: the standard output of all commands except the last one is piped to standard input of the next pipeline command

  ```cmd1; cmd2``` - means that the commands will be executed sequentially

  ```cmd &``` - running a command in the background

  ```cmd1 && cmd2``` - execute cmd1, if successful, execute cmd2

  ```cmd1 || cmd2``` - execute cmd1, if not successful, execute cmd2
  
  ## I/O redirection:
  
  ``>`` - the file is used as standard input;
  
  ```<``` - the file is used as standard output;
  
  ```>>``` - if the file did not exist, it is created,
if the file already existed, then its old contents are retained and the recording is performed
to the end of the file

    Example: ps; ls; (cd namedir; ls; ps) && ls && ps

    The first and last "ls" will be executed in the current directory, "ls" in brackets will be executed in the directory
    namedir, "ps" in parentheses should indicate the presence of an additional Shell process.



