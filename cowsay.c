#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////
//Functions
//////
void printcow(void);
void displayhelp(void);
void displaycowlist(void);

////////////////
//Variables
//////
char eyes='o';
char upperbubble='\\';
char lowerbubble='\\';

unsigned int counter;
unsigned int argscharcount=0;
unsigned int nextarg;
unsigned short skiparg;
unsigned short thought=0;

int main(int argc, char *argv[]) {

    /*Handle Arguments*/
    if( argc == 1 ) {
        displayhelp();
        exit(EXIT_FAILURE);
    }
    for (counter=1; counter < argc; counter++) {
        if ( !strcmp(argv[counter], "-e") || !strcmp(argv[counter], "--eyes") ) {
            nextarg=(counter + 1);
            if ( strlen(argv[nextarg]) == 1 ) {
                strcpy(&eyes, argv[nextarg]);
            }
            else {
                displayhelp();
                exit(EXIT_FAILURE);
            }
        }
        else if ( !strcmp(argv[counter], "-t") || !strcmp(argv[counter], "--thought") ) {
            thought=1;
            upperbubble = 'O';
            lowerbubble = 'o';
        }
        else if ( !strcmp(argv[counter], "-h") || !strcmp(argv[counter], "--help") ) {
            displayhelp();
            exit(EXIT_SUCCESS);
        }
    }

    /* Count characters in non-flag arguments */
    for(counter=1; counter < argc; counter++) {
        skiparg=0;
        if ( !strcmp(argv[counter], "-c") || !strcmp(argv[counter], "--cow") || !strcmp(argv[counter], "-e") || !strcmp(argv[counter], "--eyes") ) {
            skiparg=1;
            counter++;
        }
        else if ( !strcmp(argv[counter], "-t") || !strcmp(argv[counter], "--thought") ) {
            skiparg=1;
        }
        else if (counter < argc && skiparg == 0) {
            argscharcount=(argscharcount + 1 + (strlen(argv[counter])));
        }
    }
    if (argscharcount == 0) {
        displayhelp();
        exit(EXIT_FAILURE);
    }
    argscharcount=argscharcount + 1;

    /* Display speech bubble */
    printf(" ");
    for(counter=1; counter <= argscharcount; counter++) {
        printf("_");
    }

    if ( thought == 0 ) {
        printf("\n< ");
    }
    else if ( thought == 1 ) {
        printf("\n( ");
    }

    for(counter=1; counter < argc; counter++) {
        skiparg=0;
        if ( !strcmp(argv[counter], "-e") || !strcmp(argv[counter], "--eyes") ) {
            skiparg=1;
            counter++;
        }
        else if ( !strcmp(argv[counter], "-t") || !strcmp(argv[counter], "--thought") ) {
            skiparg=1;
        }
        else if ( skiparg == 0 ) {
            printf("%s ", argv[counter]);
        }
    }

    if ( thought == 0 ) {
        printf(">\n ");
    }
    else if ( thought == 1 ) {
        printf(")\n ");
    }
    for(counter=1; counter <= argscharcount; counter++) {
        printf("-");
    }
    printf("\n");
    printcow();
    return 0;
}

void displayhelp(void) {
    printf("This program displays all of its arguments in a speech bubble.\n\
Usage:\n\
    The flags should be the first set of arguments.\n\
    ccowsay <flag(s)> Sentence to say\n\
\n\
Flags:\n\
    -h or --help    - Displays this help text\n\
    -e or --eyes    - Specify character used for the eyes. Must be ONE character!\n\
    -t or --thought - Thought bubble\n");
}

void printcow(void) {
printf("        %c   ^__^\n\
         %c  (%c%c)\\_______\n\
            (__)\\       )\\/\\\n\
                ||----w |\n\
                ||     ||\n", upperbubble, lowerbubble, eyes, eyes);
}