#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
/*
* Forkbomb creates new child procceses until memory is full, tested works got all 16GB filled up
*/
int main()
{
    while(1)
       fork();   
    return 0;
}