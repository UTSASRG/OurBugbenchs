#include <stdio.h>
#include <stdlib.h>

/*
 * Read 4 bytes from "fd" and turn them into an int, MSB first.
*/
  int get4c(FILE *fd)
  {
        /* Use unsigned rather than int otherwise result is undefined
        * when left-shift sets the MSB. */
        unsigned n;

        n = (unsigned)getc(fd);
        n = (n << 8) + (unsigned)getc(fd);
        n = (n << 8) + (unsigned)getc(fd);   
        n = (n << 8) + (unsigned)getc(fd);
        return (int)n;
  }

int main(){
    FILE *inFile = fopen("en.utf-8.add", "r");
    if (!inFile) printf("Error opening input file\n");
    else{
        long len = get4c(inFile);
        printf("Length is %ld\n", len);
    }
    return 0;
    }
