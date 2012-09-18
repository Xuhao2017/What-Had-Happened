/**
* @author gotaly
* @data	2012-08-9
* @email gotawork@163.com
*/
#ifndef W2H_DIR_H
#define W2H_DIR_H

#include "inc.h"

#define OPEN_MODE  O_APPEND | O_WRONLY | O_CREAT

/**
* if file exist return 1 , if not reutrn 0.
*/
extern int w2h_file_exist(char *file);

/**
* return a stirng of path of file
*/
extern char *w2h_get_dir(char *file);

/**
* use system command "mkdir -p " to make direction
* @return 0 on success ,-1 when failed
*/
extern int w2h_make_dir(char *path);

/** 
* open file,
* @return same as open
*/
extern int w2h_file_open(char *file);

/**
* close fd if it's not 1
*/
extern void w2h_file_close(int fd);


#endif 
