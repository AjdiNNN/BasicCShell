// C Program to design a shell in Linux
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <netdb.h>
#include <errno.h>

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported
#define red() printf("\033[0;31m")
#define resetColor() printf("\033[0m")
#define purple() printf("\033[0;35m")

// Function to take input
int takeInput(char* str)
{
    char* buf;
    buf = readline("");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}

// Function where the system command is executed
void execArgs(char** parsed)
{
    // Forking a child
    pid_t pid = fork(); 
  
    if (pid == -1) {
        red();
        printf("\nFailed forking child..\n");
        resetColor();
        return;
    } else if (pid == 0) {
        if (execv(parsed[0], parsed) < 0) {
            red();
            printf("Could not execute command..\n");
            resetColor();
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}
#define WRITE_END 1 
#define READ_END 0
// Function where the piped system commands is executed
void execArgsPiped(char** parsed, char** parsedpipe)
{
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();

    if(pid==0)
    {
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[READ_END]);
        close(fd[WRITE_END]);
        execv(parsed[0], parsed);
        fprintf(stderr, "Failed to execute '%s'\n", parsed[0]);
        exit(1);
    }
    else
    { 
        pid=fork();

        if(pid==0)
        {
            dup2(fd[READ_END], STDIN_FILENO);
            close(fd[WRITE_END]);
            close(fd[READ_END]);
            execv(parsedpipe[0], parsedpipe);
            fprintf(stderr, "Failed to execute '%s'\n", parsedpipe[0]);
            exit(1);
        }
        else
        {
            int status;
            close(fd[READ_END]);
            close(fd[WRITE_END]);
            waitpid(pid, &status, 0);
        }
    }
}

// function for finding pipe
int parsePipe(char* str, char** strpiped)
{
    int i;
    for (i = 0; i < 2; i++) {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }
  
    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else {
        return 1;
    }
}
  
// function for parsing command words
void parseSpace(char* str, char** parsed)
{
    int i;
  
    for (i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");
  
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}
  
int processString(char* str, char** parsed, char** parsedpipe)
{
  
    char* strpiped[2];
    int piped = 0;
  
    piped = parsePipe(str, strpiped);
    if (piped) {
        parseSpace(strpiped[0], parsed);
        parseSpace(strpiped[1], parsedpipe);
    } else {
        parseSpace(str, parsed);
    }
    return 1 + piped;
}
  
int main()
{
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char* parsedArgsPiped[MAXLIST];
    int execFlag = 0;
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    host_entry = gethostbyname(hostbuffer);
    char* username = getenv("USER");
    while (1) {
        purple();
        printf("%s@%s:~$", hostbuffer, username);
        resetColor();
        // take input
        if (takeInput(inputString))
            continue;
        // process
        execFlag = processString(inputString,
        parsedArgs, parsedArgsPiped);
        // 1 if it is a simple command
        // 2 if it is including a pipe.
        // execute
        if (execFlag == 1)
            execArgs(parsedArgs);
  
        if (execFlag == 2)
            execArgsPiped(parsedArgs, parsedArgsPiped);
    }
    return 0;
}