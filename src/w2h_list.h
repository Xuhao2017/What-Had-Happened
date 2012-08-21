/**
* @author gotaly
* @data	2012-08-13
* @email gotawork@163.com
* @file w2h_list.h
* List for w2h.
* API of List for w2h
*/

#ifndef W2H_LIST_H
#define W2H_LIST_H

#include "inc.h"

/**
* type of element's iterator in list.
*/
typedef struct list_iter_s *list_iter_t;
struct list_iter_s{
	char *data;
	list_iter_t prev;	
	list_iter_t next;
};

struct w2h_list_s {
	list_iter_t cur;
	list_iter_t right;
	list_iter_t left;
	size_t num_elem;
};
typedef struct w2h_list_s w2h_list_t;

/**
* user define function of find
*/
typedef int (*suitable_fun_t)(void *data,void *dst);
/**
* user define function of foreach
*/
typedef void (*deal_fun_t)(void *data);

/** 
* create a list.
* after using ,user should free it ,or may cause memory lost.
* @return a list point  
*/
extern w2h_list_t *w2h_list_creat(void);

/** 
* if list is empty return true(1) or return 0
*/
extern int w2h_list_empty(w2h_list_t *list);

/**
* init a list 
*/
extern void w2h_list_init(w2h_list_t *list);

/**
* add a item after head.
* @param list: list to add to
* @param data: data to be insert into a item of list
* @param size :size of data
* @return iterator of which just insert to 
*/
extern list_iter_t w2h_list_append(w2h_list_t *list,void *data,size_t size); 

extern void w2h_list_free(w2h_list_t *list);
extern void w2h_list_del(w2h_list_t *list);
extern list_iter_t w2h_list_find(void *data);
extern list_iter_t w2h_list_iter_find(w2h_list_t *list,list_iter_t data_iter);
extern list_iter_t w2h_list_user_find(w2h_list_t *list,void *dst,suitable_fun_t fun);
extern void w2h_list_foreach(w2h_list_t *list,deal_fun_t fun);
extern void *w2h_list_containof(list_iter_t iter);


#endif
