#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//useful constants if you want them
#define LETTERS 26
#define MAX_WORD_LEN 1024


int main(int argc, char * argv[]){
  FILE * text_f, * key_f;
  char sub[LETTERS];  
  if( argc < 3){
    fprintf(stderr, "ERROR: require input file and substitution file\n");
    exit(1);
  }

  if( (key_f = fopen(argv[1],"r")) == NULL){
    perror("substitution file");
    exit(1);
  }

    if( (text_f = fopen(argv[2],"r")) == NULL){
    perror("text file");
    exit(1);
  }

  char word[MAX_WORD_LEN];
  char key[4];

  //TODO
  while (fscanf(key_f, "%s", key) != EOF)
  {
    //printf("%c, %c, %d\n", key[0], key[2], key[0] - 'A');
    sub[key[0] - 'A'] = key[2];
  }
  while (fscanf(text_f, "%s", word) != EOF)
  {
    for (int i = 0; i < strlen(word); i++)
    {
      if (isalpha(word[i]))
      {
        word[i] = toupper(word[i]);
        printf("%c", sub[word[i] - 'A']);
      }
      else 
      {
        printf("%c", word[i]);
      }
    }
    printf(" ");
  }

  fclose(text_f);
  fclose(key_f);
}

