#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    for(int i=1 ; i<argc ; i++)
    {
        int ret;
        ret = remove(argv[i]);
        if(ret == 0) {
            printf("%s is deleted successfully\n", argv[i]);
        } else {
            fprintf(stderr, "%s: %s : %s\n", argv[0], argv[i],
            strerror(errno));
        }
    }   
    exit(0);
}