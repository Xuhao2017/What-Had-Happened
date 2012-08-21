/**
* @author gotaly
* @data	2012-08-14
* @email gotawork@163.com
*/

#include "w2h_queue.h"



w2h_queue_t *w2h_queue_create(char *mem,size_t mem_size)
{
	if (NULL == mem)
		return NULL;
	if (mem_size < sizeof(struct w2h_queue_s)) 
		return NULL;
	w2h_queue_t *queue = (w2h_queue_t *) mem;
	queue->head = 0;
	queue->tail = 0;
	queue->used = 0;
	queue->size = mem_size - sizeof(struct w2h_queue_s);
	queue->mem = mem+sizeof(struct w2h_queue_s);
	return queue;
}

int w2h_queue_enqueue(w2h_queue_t *queue,void *data,size_t len)
{
	
	size_t remain_mem;
	size_t item_head;
	size_t item_data;

	if (queue->head <= queue->tail)
		remain_mem = queue->size - (queue->tail - queue->head);
	else
		remain_mem = queue->size - (queue->head - queue->tail);
	if (remain_mem < len+sizeof(size_t))
		return -1;

	item_head = queue->tail;
	if (item_head+ sizeof(size_t) > queue->size){
		memcpy((char *)queue->mem + item_head,(char *)&len,queue->size - item_head);	
		memcpy(queue->mem,
			(char *)&len +(queue->size-item_head),
			sizeof(size_t)-(queue->size - item_head));
	} else {
		memcpy((char *)queue->mem + item_head,(char *)&len,sizeof(size_t));	
	}			
	item_data = (item_head+ sizeof(size_t)) % queue->size;
	if ((item_data+len) > queue->size){
		memcpy((char *)queue->mem + item_data,data,queue->size - item_data);	
		memcpy(queue->mem,
			(char *)data+(queue->size - item_data),
			len-(queue->size - item_data));
	} else {
		memcpy((char *)queue->mem + item_data,data,len);	
	}

	queue->used+= len;
	queue->tail =(queue->tail+len+sizeof(size_t))  % queue->size;
	return 0;
}


int w2h_queue_empty(w2h_queue_t *queue)
{
	return(queue->used == 0 && queue->head == queue->tail);
}

int w2h_queue_full(w2h_queue_t *queue)
{
	return(queue->used > 0 && queue->head == queue->tail);
}

int w2h_queue_dequeue(w2h_queue_t *queue,void **data,size_t *len)
{
	size_t item_length;
	size_t item_data;
	size_t item_head;

	if (w2h_queue_empty(queue))
		return -1;

	item_head = queue->head;
	if (item_head+ sizeof(size_t) > queue->size){
		memcpy(&item_length,(char *)queue->mem + item_head,queue->size-item_head);		
		memcpy((char *)&item_length+(queue->size-item_head),
			queue->mem,
			sizeof(size_t)-(queue->size - item_head));
	} else {
		memcpy(&item_length,(char *)queue->mem + item_head,sizeof(size_t));	
	}

	item_data = (item_head + sizeof(size_t) )% queue->size;
	if (*len < item_length)
		*data = realloc(*data,item_length);
	if ((item_data+ item_length)>queue->size){
		memcpy(*data,(char *)queue->mem+item_data,queue->size - item_data);	
		memcpy((char *)(*data)+(queue->size - item_data),
			queue->mem,
			item_length-(queue->size - item_data));
	} else {
		memcpy(*data,(char *)queue->mem + item_data,item_length);	
	}

	/* update head */
	queue->head = (queue->head +item_length+sizeof(size_t)) % queue->size;
	*len = item_length;
	queue->used -= *len;
	return 0;
}

