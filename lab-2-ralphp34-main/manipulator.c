#include <stdio.h>
#include <stdlib.h>

//TODO PART 2: complete the print_array function to have the right output
//prints out the array in the desired format, for exmaple:
// { 0 1 2 3 4 }
void print_array(int a[], int len)
{
  //printf("PRINTING THE ARRAY\n");
  printf("{ ");
  for (int i = 0; i < len; i++)
  {
    printf("%d ", a[i]);
  }
   printf("}\n\n");
}

//TODO PART 3: compete the reverse_array function
// hint: you'll need a tmp variable for swaps
void reverse_array(int a[], int len)
{
  //printf("REVERSING THE ARRAY\n");
  int b[len];
  
  for (int i = 0; i < len; i++)
  {
    b[len - 1 - i] = a[i];
  }

  for (int i = 0; i < len; i++)
  {
    a[i] = b[i];
  }
  print_array(a, len);
}

//TODO PART 4: complete the randomize array function
// hint: random() returns a random number, but you want it to be in
//       the range of the length of the array. Try using modulo
// hint: try randomnly swapping all index with some other index
void randomize_array(int a[], int len)
{
  //printf("RANDOMIZING THE ARRAY\n");
  for (int i = 0; i < len; i++)
  {
    int j = random() % len;
    int temp = a[j];
    a[j] = a[i];
    a[i] = temp;
  }
  print_array(a, len);
}

//TODO PART 5: complete the sort_arry function (smallest to biggest)
// hint: you'll probably need two for loops 
// hint: Check out insertion sort on wikipedia (it's ok to use that source)
void sort_array(int a[],int len)
{
  //printf("SORTING THE ARRAY\n");
  for (int i = 0; i < len; i++)
  {
    for (int j = i; (j>0) && (a[j]<a[j-1]); j--)
    {
      int temp = a[j];
      a[j] = a[j-1];
      a[j-1] = temp;
    }
  }
  print_array(a, len);
}

int main(int argc, char *argv[]){

  int len=0;    //store the length of the array, initially 0 but will change
  int res;      //store the result of scanf() operations
  int choice;   //store the user choice for operations
  int i;        //an interator for loops


  srandom(1845);//seed random number generator

  printf("Enter the length:\n");

  //TODO PART 1: Requst how many numbers
  // hint: don't forget to return 1 on error


  res = scanf("%d", &len);
  if(res == 0)
  {
    printf("ERROR: Invalid input");
    return 0;
  }



  int array[len]; //declare array now that we know its size


  printf("Enter %d numbers (space separated):\n",len);

  //TODO PART 1: Read in desired numbers
  // hint: don't forget to return 1 on error


  for (i = 0; i < len; i++)
  {
    res = scanf("%d", &array[i]);
    if (res == 0)
    {
      printf("ERROR: Invalid input");
      return 0;
    }
  }




  //while loop for operations, run until exit or EOF
  while(1){
    printf("Choose an operation:\n");
    printf("(0) : exit\n");
    printf("(1) : print array\n");
    printf("(2) : reverse array\n");
    printf("(3) : randomize array\n");
    printf("(4) : sort array\n");
    res = scanf("%d",&choice);

    //error check
    if(res == 0){
      char c;
      printf("ERROR: Invalid input. Choose again.\n");

      scanf("%c",&c);//clear stdin and continue
      continue;
    }else if(res == EOF){
      break;
    }
      

    //TODO PART 1,3-5: Complete based on choice
    //      - properly want to use an if/else if/else block (or a case switch)
    //  
    //      - each choice should call an appropriate function
    //
    //      - print_array(), reverse_array(), randomize_array(), sort_array()
    //
    //      - remember arrays and pointers are the same, so you can
    //        pass a pointer to the array to the functions.
    //
    //      - becasue you don't length ahead of time, you'll also need
    //       to pass the length of the arry as an argument
    //
    //      - should refresh your memory of loop control, e.g., break and continue

    if (choice == 0)
    {
      break;
    } //add more else if blocks for other choices, e.g., 1, 2, 3, and 4
    else if(choice == 1)
    {
      print_array(array, len);
    }
    else if(choice == 2)
    {
      reverse_array(array, len);
    }
    else if(choice == 3)
    {
      randomize_array(array, len);
    }
    else if(choice == 4)
    {
      sort_array(array, len);
    }
    else{
      printf("ERROR: Invalid number. Choose again.\n\n");
      continue;
    } 
  }
  return 0; //return 0 on success
}
