#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// given n pointers to strings, pack copies of them
// into a single malloc'd block that can be accessed 
// using bracket syntax
char **
packStrings(size_t n, char *s[])
{
  size_t length = 0;
  
  // compute total length including nulls
  for(size_t i = 0; i < n; i++) {
    length += strlen(s[i]) + 1;
  }
  
  // allocate a block big enough for pointers and strings
  char **s2 = malloc(sizeof(char *) * n + length);
  
  // this is a pointer to where the strings are copied
  // after the n pointers
  char *top = (char *) (s2 + n);
  
  // copy the strings and fill in the pointer array
  for(size_t i = 0; i < n; i++) {
    strcpy(top, s[i]);
    s2[i] = top;
    top += strlen(s[i]) + 1;
  }
  
  return s2;
}

void
freePackedStrings(char **s)
{
    free(s);
}

int
main(int argc, char **argv)
{
    // pack argv, then print it out from the copied version
    char **argv2 = packStrings(argc, argv);

    for(int i = 0; i < argc; i++) {
        puts(argv2[i]);
    }

    freePackedStrings(argv2);

    return 0;
}
