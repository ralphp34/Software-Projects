#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check1(char * str);
int check2(char * str);

int check1(char *str){
  //TODO
  int len = strlen(str);
  for (int i = 0; i < len; i++)
  {
    if (str[i] != str[len - 1 - i])
    {
      return 0;
    }
  }
  return 1;
}

int check2(char *str){
  //TODO

  int len = strlen(str);
  char copy[len];


  for (int i = 0; i < len; i++)
  {
    copy[len - 1 - i] = str[i];
  }

  copy[strlen(str)] = '\0';
  for (int i = 0; i < len; i++)
  {
    if (copy[i] != str[i])
    {
      return 0;
    }
  }
  return 1;
}

int main(int argc, char * argv[]){

  char str[1024];

  printf("Enter a string:\n");

  scanf("%1023s",str);

  //TODO

  if(check1(str))
  {
    printf("Palindrome according to check 1\n");
  }
  else
  {
    printf("NOT a palindrome according to check 1\n");
  }

  if(check2(str))
  {
    printf("Palindrome according to check 2\n");
  }
  else
  {
    printf("NOT a palindrome according to check 2\n");
  }

}
