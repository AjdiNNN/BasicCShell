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

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported
  
// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")
  
// Greeting shell during startup
void init_shell()
{
    clear();
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    host_entry = gethostbyname(hostbuffer);
    char* username = getenv("USER");
    printf("%s@%s", hostbuffer, username);
    sleep(1);
    clear();
}
  
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
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}
  
// Function where the piped system commands is executed
void execArgsPiped(char** parsed, char** parsedpipe)
{
    // 0 is read end, 1 is write end
    int pipefd[2]; 
    pid_t p1, p2;
  
    if (pipe(pipefd) < 0) {
        printf("\nPipe could not be initialized");
        return;
    }
    p1 = fork();
    if (p1 < 0) {
        printf("\nCould not fork");
        return;
    }
  
    if (p1 == 0) {
        // Child 1 executing..
        // It only needs to write at the write end
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    } else {
        // Parent executing
        p2 = fork();
  
        if (p2 < 0) {
            printf("\nCould not fork");
            return;
        }
  
        // Child 2 executing..
        // It only needs to read at the read end
        if (p2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
        } else {
            // parent executing, waiting for two children
            wait(NULL);
            wait(NULL);
        }
    }
}
  
// Help command builtin
void openHelp()
{
    puts("\nList of Commands supported:"
        "\n$exit"
        "\n$rm"
        "\n$cat"
        "\n$clear");
    return;
}
  
// Function to execute builtin commands
int ownCmdHandler(char** parsed)
{
    int NoOfOwnCmds = 6, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;

    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "help";
    ListOfOwnCmds[2] = "rm";
    ListOfOwnCmds[3] = "cat";
    ListOfOwnCmds[4] = "clear";
    ListOfOwnCmds[5] = "cowsay";
    
    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }
    if(switchOwnArg == 0)
        printf("Command not found use help\n");
    switch (switchOwnArg) {
    case 1:
        printf("\nGoodbye\n");
        exit(0);
    case 2:
        openHelp();
        return 1;
    case 3:
        if(parsed[1]=="") return printf("rm -filename\n");
        int ret;
        ret = remove(parsed[1]);
        if(ret == 0) {
            printf("%s is deleted successfully\n", parsed[1]);
        } else {
            printf("Error: unable to delete the file\n");
        }
        return 1;
    case 4: ;
        int i=1;
        for (i = 1; i < MAXLIST; i++) 
        {
            if (parsed[i] == NULL)
                break;
            if (strlen(parsed[i]) == 0)
                break;
            if(parsed[i][0]!='>')
            {
                FILE *fp;
                char c;
                fp = fopen(parsed[i], "r");
                if (fp == NULL)
                {
                    printf("Cannot open file \n");
                    exit(0);
                }
            
                // Read contents from file
                c = fgetc(fp);
                while (c != EOF)
                {
                    printf ("%c", c);
                    c = fgetc(fp);
                }
            
                fclose(fp);
                printf("\n");
            }
            else
            {
                FILE *fp;
                char* filename = parsed[i] + 1;
                fp = fopen (filename, "w");
            }
        }
        return 1;
    case 5:
        clear();
        return 1;
    case 6: 
        printf(" ");
        for (int i = 1; i < MAXLIST; i++) 
        {
            if (parsed[i] == NULL)
                break;
            if (strlen(parsed[i]) == 0)
                break;
            for(int j=0; j < strlen(parsed[i])+1; j++)
            {
                printf("-");
            }
        }
        printf("\n(");
        for (int i = 1; i < MAXLIST; i++) 
        {
            if (parsed[i] == NULL)
                break;
            if (strlen(parsed[i]) == 0)
                break;
            printf("%s ",parsed[i]);
        }
        printf(")\n");
        printf(" ");
        for (int i = 1; i < MAXLIST; i++) 
        {
            if (parsed[i] == NULL)
                break;
            if (strlen(parsed[i]) == 0)
                break;
            for(int j=0; j < strlen(parsed[i])+1; j++)
            {
                printf("-");
            }
        }
        printf("\n");
        printf("     \\  ^__^\n");
        printf("      \\ (oo)\\_____\n");
        printf("        (__)\\     )\\/\\\n");
        printf("           ||----w |\n");
        printf("           ||     ||\n");
        return 1;
    default:
        break;
    }

    return 0;
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
  
    if (ownCmdHandler(parsed))
        return 0;
    else
        return 1 + piped;
}
  
int main()
{
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char* parsedArgsPiped[MAXLIST];
    int execFlag = 0;
    init_shell();
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    host_entry = gethostbyname(hostbuffer);
    char* username = getenv("USER");
    while (1) {
        printf("%s@%s:~$", hostbuffer, username);
        // take input
        if (takeInput(inputString))
            continue;
        // process
        execFlag = processString(inputString,
        parsedArgs, parsedArgsPiped);
        // execflag returns zero if there is no command
        // or it is a builtin command,
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