#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
/*
* Cat command with support to create files with ex. cat >newfilename
*/



ssize_t safe_read(int fd, void *buf, size_t count)
{
	ssize_t n;

	do {
		n = read(fd, buf, count);
	} while (n < 0 && errno == EINTR);

	return n;
}

int main(int argc, char *argv[]) {
  FILE *file;
  int chr;
  int count=1;
  int number = 0;
  int s = 0;
  for(count; count < argc; count++) {
    if(strcmp(argv[count],"-n")!=0 && strcmp(argv[count],"-s")!=0)
    {
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
      int counter = 1;
      if(s == 1)
        printf("Start of file\n");
      if(number)
      {
          printf("%d  ",counter);
          counter++;
      }
      fflush(stdout);
      while((chr = getc(file)) != EOF)
      {

        fprintf(stdout, "%c", chr);
        if(number == 1 && chr == 10)
        {
          printf("%d  ",counter);
          counter++;
        }
      }
      if(s == 1)
        printf("\nEnd of file\n");  
      fclose(file);
    }
    else if (strcmp(argv[count],"-n")==0)
      number = 1;
    else
      s = 1;
  }
  exit(0);
}

