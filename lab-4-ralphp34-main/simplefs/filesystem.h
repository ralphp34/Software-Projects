#ifndef FILESYSTEM_H
#define FILESYSTEM_H

/**
 * Structure for a file
 **/
struct file{

  char * fname; //name of file
  time_t last; //last modified

  struct file * next_file;
  
};

//typedef to make it easier
typedef struct file file_t;


/**
 * Structure for a diretory
 **/
typedef struct{
  
  file_t * flist; //pointer to first file_t in the linked list or the
		  //head of the list

  int nfiles;    //number of files currently stored

} dir_t;  

/**
 *Create a new directory structure initialized properly
 *
 *@return: pointer to newly allocated directory
 **/
dir_t * simplefs_mkdir();

/**
 *Remove and deallocate the directory structure at dir.  
 *
 *@arg dir:  pointer to a directory structure
 **/
void simplefs_rmdir(dir_t * dir);

/**
 *Update the timestamp for the file fname or create the file fname if
 *it doesn't exist
 *
 *@arg dir: pointer to a directory structure
 *@arg fname: string, the name of the file
 **/
void  simplefs_touch(dir_t * dir, char *fname);

/**
 *Remove and Deallocate a file_t by fname
 *
 *@arg dir: pointer to a directory structure
 *@arg fname: string, the name of the file
 *@return int: positive integer if remove success, else negative on failur
 **/
int simplefs_rm(dir_t * dir, char * fname);


/**
 * Remove and Deallocate a file_t by file pointer
 * 
 * @arg file: pointer to the file_t to deallocate and remove
 **/
void simplefs_rmfile(file_t * file);

/**
 * List the contents of the directory dir
 *
 *@arg dir: pointer to a directory structure
 **/
void simplefs_ls(dir_t * dir);

/**
 *List the contents of the directory in time sorted order
 *
 *@arg dir: pointer to a directory structure
 **/
void simplefs_ls_sorttime(dir_t * dir);

/**
 *List the contents of the directory in file name sorted order
 *
 *@arg dir: pointer to a directory structure
 **/
void simplefs_ls_sortname(dir_t * dir);


#endif





