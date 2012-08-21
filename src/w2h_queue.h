/**
* @file w2h_queue.h
* @author gotaly
* @data	2012-08-14
* @email gotawork@163.com
* Queue for w2h.
* API of Queue for w2h
*/

#ifndef W2H_QUEUE_H
#define W2H_QUEUE_H

#include "inc.h"

/**
* struct of queue.
*/
struct w2h_queue_s{
	size_t head;
	size_t tail;
	size_t size;
	size_t used;
	char *mem;
};
typedef struct w2h_queue_s w2h_queue_t;

/**
* use memory mem which has size bytes memory to creat a queue.
* @param mem: memory for queue
* @param size: size of queue
* @return a w2h_queue_t *queue
*/
extern w2h_queue_t *w2h_queue_create(char *mem,size_t size);

/** 
* enqueue a item data with len length into queue.
* @param queue : queue to be enqueue
* @param data : data to enqueue
* @param len : length of data
* @return 0 on sucess ,-1 on failed
*/
extern int w2h_queue_enqueue(w2h_queue_t *queue,void *data,size_t len);

/** 
* dequeue a item from queue to address **data and store item's length into *len.
* at first ,*len is length of *data,if it is smaller than the length of which to 
* be dequeue,*data will be expanded and *len will be changed togethor.
* @param queue:queue to be dequeue
* @param len :len of *data
* @param data : dequeued item will be store in *data
* @return 0 on sucess ,-1 on failed
*/
extern int w2h_queue_dequeue(w2h_queue_t *queue,void **data,size_t *len);

/**
* if queue is empty return true(1) or return 0
*/
extern int w2h_queue_empty(w2h_queue_t *queue);

/** 
* if queue is full return true(1) or return 0
*/
extern int w2h_queue_full(w2h_queue_t *queue);

#endif
