#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

/*
* Implemenation of kill(), makes shell exit and shutsdown
*/

int main(int argc, char *argv[]) {
  if(kill(getppid(), 0)==0)
  {
    printf("Exiting\n");
    kill(getppid(), 1);
  }
}