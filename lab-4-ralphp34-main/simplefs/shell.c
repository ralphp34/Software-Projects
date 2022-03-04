#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>


#include "filesystem.h"


int main(int argc, char * argv[]){

  dir_t * curdir = NULL;
  char * line, * tok, *arg;


  rl_bind_key('\t', rl_abort);

  curdir = simplefs_mkdir();
  
  while(1){
    
    line = readline("simplefs > ");
    
    if( line == NULL){

      if (curdir){
	simplefs_rmdir(curdir);
      }

      printf("\n");
      break;
    }


    if(0 == strtok(line, "")){
      continue;
    }

    add_history(line);

    tok = strtok(line, " ");
      
    if (0 == strcmp(tok, "ls")){
      
      simplefs_ls(curdir);

    }else if (0 == strcmp(tok, "ltime")){
      
      simplefs_ls_sorttime(curdir);
      
    }else if (0 == strcmp(tok, "lname")){
      
      simplefs_ls_sortname(curdir);
      
    }else if (0 == strcmp(tok, "rm")){
      
      while( (arg = strtok(NULL, " ")) != NULL){
	simplefs_rm(curdir, arg);
      }
      
    }else if (0 == strcmp(tok, "touch")){
      
      while( (arg = strtok(NULL, " ")) != NULL){
	simplefs_touch(curdir, arg);
      }
      
    }else if (0 == strcmp(tok, "exit")){
      
      simplefs_rmdir(curdir);
      free(line);
      break;
      
    } else{
      fprintf(stderr, "ERROR: Unkown command `%s'\n",tok);
      fprintf(stderr, "Available Commands: ls, touch, rm, lsname, lstime, exit\n");
    }
    
    free(line);
  }

  return 0;
}
