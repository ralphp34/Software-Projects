#include <stdio.h>
#include <stdlib.h>

#include <string.h>

int main(int argc, char * argv[]){
  int i;
  char hello[] = "Hello World!";

  //simple copy routine
  char * str = (char *) malloc(strlen(hello) + 1);
  for(i = 0; i < strlen(hello) + 1; i ++)
  {
    str[i] = hello[i];
  }

  printf("%s\n", str);

  free(str);
  return 0;
}
