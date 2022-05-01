#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if(kill(getppid(), 0)==0)
  {
    printf("Exiting\n");
    kill(getppid(), 1);
  }
}