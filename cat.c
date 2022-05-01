#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
 
int main(int argc, char *argv[]) {
  FILE *file;
  int chr;
  int count;
 
  for(count = 1; count < argc; count++) {
    if((file = fopen(argv[count], "r")) == NULL ) {
    
      if(argv[count][0] != '>')
      {
      fprintf(stderr, "%s: %s : %s\n", argv[0], argv[count],
        strerror(errno));
      }
      else
      {
        char* filename = argv[count] + 1;
        file = fopen (filename, "w");
      }
    continue;
    }
    while((chr = getc(file)) != EOF)
      fprintf(stdout, "%c", chr);
    fclose(file);
  }
  exit(0);
}