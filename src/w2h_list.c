/**
* @author gotaly
* @data	2012-08-13
* @email gotawork@163.com
*/

#include "w2h_list.h"


w2h_list_t *w2h_list_creat(void)
{
	w2h_list_t * list  = (w2h_list_t *) malloc(sizeof(struct w2h_list_s));
	list->cur = NULL;
	list->right = NULL;
	list->left = NULL;
	list->num_elem = 0;

	return list;
}


void w2h_list_init(w2h_list_t *list)
{
	list->cur = NULL;
	list->right = NULL;
	list->left = NULL;
	list->num_elem = 0;
}

int w2h_list_empty(w2h_list_t *list)
{
	return (list->cur == NULL);
}

list_iter_t w2h_list_append(w2h_list_t *list,void *data,size_t size)
{
	if (NULL == data)
		return NULL;
	list_iter_t tmp;
	tmp = (list_iter_t) malloc(sizeof(struct list_iter_s));
	if (NULL == tmp)
		return NULL;
	tmp->data = (void *)malloc(size);
	memcpy(tmp->data,data,size);
	if (NULL == list->cur){
		list->cur = tmp;	
		list->right = list->left = list->cur;
	} else {
		list->cur->next = tmp;	
	}
	tmp->next = list->right;
	tmp->prev = list->cur;
	list->right->prev = tmp;
	list->cur = tmp;

	list->right = list->cur->next;
	list->left = list->cur->prev;
	list->num_elem++;
	return tmp;
}

void w2h_list_free(w2h_list_t *list)
{
	if (NULL == list)
		return ;
	list_iter_t tmp;
	while (NULL != list->cur){
		tmp  = list->cur->next;
		list->cur->next = tmp->next;
		if (tmp == list->cur)
			list->cur = NULL;
		free(tmp->data);
		tmp->prev = tmp->next = NULL;
		free(tmp);
		tmp = NULL;
		
	}
	w2h_list_init(list);
}

void w2h_list_del(w2h_list_t *list)
{
	if (NULL == list)
		return ;
	w2h_list_init(list);
	free(list);
}

list_iter_t w2h_list_user_find(w2h_list_t *list,void *dst,suitable_fun_t fun)
{
	if (NULL == list)
		return NULL;
	if (w2h_list_empty(list))
		return NULL;

	if ((*fun)(list->cur->data,dst))	
		return list->cur;
	if ((*fun)(list->right->data,dst))	
		return list->right;
	if ((*fun)(list->left->data,dst))	
		return list->left;

	list->cur = list->right;
	while (list->cur->next !=list-> left){
		if ((*fun)(list->cur->data,dst)){
			list->right = list->cur->next;
			list->left = list->cur->prev;
			return list->cur;
		}	
		list->cur = list->cur->next;
	}
	return NULL;
}


list_iter_t w2h_list_find(void *data)
{
	/** to do **/
	return NULL;
}
list_iter_t w2h_list_iter_find(w2h_list_t *list,list_iter_t data_iter)
{
	/** to do **/
	return NULL;
}

void *w2h_list_containof(list_iter_t iter)
{
/** user shoul control data structure **/
	return iter->data;
}

void w2h_list_foreach(w2h_list_t *list,deal_fun_t fun)
{
	if (NULL == list)
		return ;
	if (w2h_list_empty(list))
		return ;
	list_iter_t tmp;
	tmp = list->cur;
	while (tmp != list->left){
		(*fun)(tmp->data);	
		tmp = tmp->next;
	}
	(*fun)(list->left->data);	
}
