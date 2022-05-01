#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/*
* Basic cowsay outputs cowsay with text bubble above
*/

int main(int argc, char *argv[]) {
    printf(" ");
    for (int i = 1; i < argc; i++) 
    {
        if (argv[i] == NULL)
            break;
        if (strlen(argv[i]) == 0)
            break;
        for(int j=0; j < strlen(argv[i])+1; j++)
        {
            printf("-");
        }
    }
    printf("\n(");
    for (int i = 1; i < argc; i++) 
    {
        if (argv[i] == NULL)
            break;
        if (strlen(argv[i]) == 0)
            break;
        printf("%s ",argv[i]);
    }
    printf(")\n");
    printf(" ");
    for (int i = 1; i < argc; i++) 
    {
        if (argv[i] == NULL)
            break;
        if (strlen(argv[i]) == 0)
            break;
        for(int j=0; j < strlen(argv[i])+1; j++)
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
    exit(0);
}