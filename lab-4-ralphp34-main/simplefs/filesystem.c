#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <time.h>

#include "filesystem.h"

dir_t * simplefs_mkdir(){

  dir_t * dir = malloc(sizeof(dir_t));    //allocate the directory, initialize size
  dir->nfiles = 0;                        //no files stores
  dir->flist = NULL;                      //point to NULL since no items in list
  return dir;
}

void simplefs_rmdir(dir_t * dir){
  file_t * cur_f, * next_f;

  //start cur_f pointing to start of list
  cur_f = dir->flist;
  
  while(cur_f != NULL){        //iterate until end of list, indicated by NULL
    
    next_f = cur_f->next_file; //save the pointer to the next file

      
    simplefs_rmfile(cur_f);       //remove the current file (you will implemenmt this function)

    cur_f = next_f;           //move to the next file
  }

  free(dir);                 //deallocate the directory itself
}
 


void simplefs_ls(dir_t * dir){

  file_t * cur_f;

  cur_f = dir->flist;
  while( cur_f != NULL){
    printf("  %s\t%s", cur_f->fname, ctime(&(cur_f->last)));
    cur_f = cur_f->next_file;
  }
  
}

/**************************************************************************
 *Code to complete is below
 **************************************************************************/

void simplefs_touch(dir_t * dir, char *fname){
  if(fname == NULL){
    fprintf(stderr, "ERROR: touch: require filename");
  }


  //TODO: Complete the touch command
  //
  // There are three cases you need to consider:
  //
  //   (1) It's an empty list of files, which means that 
  //
  //          dir->nfiles == 0 and dir->flist == NULL
  // 
  //       Then the only thing you need to do is create a new file and
  //       make it the head of the list, that is what dir->flist references
  //
  //   (2) The file name already exists, which means that you should
  //       update the timestamp of the file by doing the following:
  //    
  //          cur_f->last = time(NULL);
  //
  //
  //   (3) The file name does not exist, which means that you add a
  //       new file to the end of the list. 


  if(dir->nfiles == 0 || dir-> flist == NULL){ 
    //Case (1) it's an empty list
    file_t * new_file = malloc(sizeof(file_t));
    new_file->fname = malloc(sizeof(fname));
    strcpy(new_file->fname, fname);
    new_file->last = time(NULL);
    dir->flist = new_file;
    dir->nfiles++;
    new_file->next_file = NULL;
    return;
  }

  file_t * cur_f;

  cur_f = dir->flist;
  while(cur_f != NULL)
  {

    //Case (2) the file already exists in the list, update its time stamp
    if(strcmp(cur_f->fname,fname) == 0)
    {
      cur_f->last = time(NULL);
      return;

    }
    if (cur_f->next_file == NULL)
    {
      break;
    }
    cur_f = cur_f->next_file;

  }

  //Case (3) The file does not exist, create a new file
  
  file_t * last_file = malloc(sizeof(file_t));
  last_file->fname = strdup(fname);
  strcpy(last_file->fname, fname);
  last_file->last = time(NULL);
  last_file->next_file = NULL;
  dir->nfiles++;
  cur_f->next_file = last_file;

  return;
}


void simplefs_rmfile(file_t *file){ 
  //TODO: Complete file dealocation 
  //      (note this is called by simplefs_rmdir() to deallocate individual files)
  free(file->fname);
  free(file);
}


int simplefs_rm(dir_t * dir, char *fname){
  if(fname == NULL){
    fprintf(stderr, "ERROR: rm: require file name\n");
    return 0;
  }

  if(dir->flist == NULL){
    fprintf(stderr, "ERROR: empty file list\n");
    return 0;
  }

  file_t * cur_f; //pointer for the current node
  file_t ** prev_f; //to reference previous nodes next_file pointer

  prev_f = &(dir->flist);  //pointer to previous pointer location 
  cur_f = dir->flist;      //head of list
  while(cur_f != NULL){
    
    //TODO: Find the file, and properly dealocate it
    //     
    //When removing a file be sure to realign the pointers so that the
    //file pointer reference the file to be deleted now references the
    //next_file of the deleted file.
    //
    //      .-----------.       .-----------.       .-----------.
    //  .-> | fname     |   .-> | fname     |   .-> | fname     |   .->
    // -'   | next_file +---'   | next_file +---'   | next_file +---'
    //      '-----------'       '-----------'       '-----------'
    //                       (deleting this file)
    //                                 
    //
    //                      .-----------------.
    //      .-----------.   |   xXXXXXXXXXXXx |     .-----------.
    //  .-> | fname     |   |   x *****     x '---> | fname     |   .->
    // -'   | next_file +---'   x ********  x       | next_file +---'
    //     '-----------'        xXXXXXXXXXXXx       '-----------'
    //          (need to have
    //                next_file point to the deleted files's next file)
    //

    if (strcmp(cur_f->fname, fname) == 0)
    {
      * prev_f = cur_f->next_file;
      simplefs_rmfile(cur_f);
      return 1;
    } 

    prev_f = &(cur_f->next_file); //address of previous node next_file pointer
    cur_f = cur_f->next_file;     //iterate to the next file
  }
  
  fprintf(stderr, "ERROR: rm: no file `%s'\n",fname);
  return 0; //file not found
}




void simplefs_ls_sorttime(dir_t * dir){
  //TODO: Complete for extra credit


}
void simplefs_ls_sortname(dir_t * dir){
  //TODO: Complete for extra credit

}

