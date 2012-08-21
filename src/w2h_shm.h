/**
* @author gotaly
* @data	2012-08-13
* @email gotawork@163.com
* @file w2h_list.h
* Share Memory for w2h.
* API of Share Memory for w2h
*/
#ifndef W2H_SHM_H
#define W2H_SHM_H

#include "inc.h"

#define SHM_KEY 520


/**
* creat a shm_size bytes shared memory .
* @return on success it return char * which point sto shared memory
* return NULL when failed
**/
extern char *w2h_shm_create(size_t shm_size);

/**
* delete a shared memory  point by shm_addr .
* @param shm_addr : memory return by w2h_shm_create
* @return on success it return 0
* return -1 when failed
**/
extern int w2h_shm_del(char *shm_addr);

/** 
* clear system's shared memory created by me 
*/
extern int w2h_shm_clear(void);

#endif 
