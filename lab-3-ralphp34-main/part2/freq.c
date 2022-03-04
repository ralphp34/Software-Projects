#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//useful constants if you want them
#define LETTERS 26
#define MAX_WORD_LEN 1024

int letter_count[26] = {0};
int total_count = 0;
char alph[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
double freq;


int main(int argc, char * argv[]){

  FILE * input_f;
  input_f = fopen(argv[1], "r");
  
  if (argc < 2)
  {
    fprintf(stderr, "ERROR: require input file\n");
    exit(1);
  }

  if ((input_f = fopen(argv[1],"r")) == NULL)
  {
    perror("input file");
    exit(1);
  }
  
  char word[MAX_WORD_LEN];

  //TODO
  while (fscanf(input_f, "%s", word) != EOF)
  {
    for (int i = 0; i < strlen(word); i++)
    {
      //printf("%c\n", toupper(word[i]));
      if(isalpha(word[i]))
      {
        letter_count[toupper(word[i]) - 'A'] = letter_count[toupper(word[i]) - 'A'] + 1;
        total_count++;
      }

    }
  }
  for (int i = 0; i < LETTERS; i++)
  {
    freq = ((double)letter_count[i] / total_count) * 100;
    printf("%c: %d (%.2f%%)\n", alph[i], letter_count[i], freq);
  } 
  fclose(input_f); 

  

}
