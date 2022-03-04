#include <stdio.h>
#include <stdlib.h>

int main(){
  int n=0;
  
  printf("Enter a number, any number:\n");
  scanf("%d",&n);

  printf("Add 9 to that number --- %d\n",n+9);
  printf("\n");
  printf("Multiply the result above by 2 --- %d\n",(n+9)*2);
  printf("\n");
  printf("Subtract 4 --- %d\n",((n+9)*2)-4);
  printf("\n");
  printf("Divide by 2 --- %d\n",(((n+9)*2)-4)/2);
  printf("\n");
  printf("Subtract the original number --- %d\n",((((n+9)*2)-4)/2)-n);
  printf(".\n");
  printf(".\n");
  printf("Your answer is ... 7\n");

  
}
