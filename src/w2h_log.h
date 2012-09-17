/**
*    Head file of W2H
*    Copyright (c) 2012 Gotaly (gotawork@gmail.com)
*    License: GNU GPLv3
*/

#ifndef W2H_LOG_H
#define W2H_LOG_H

#include "w2h_list.h"
#include "w2h_queue.h"
#include "w2h_shm.h"
#include "w2h_rules.h"
#include "w2h_format.h"
#include "inc.h"
#include "w2h_lua.h"

/**
* list of config
* use two lists to resume config files
* @key config_class_x class list
* @key config_id_x class list
*/
w2h_list_t *config_class_a;
w2h_list_t *config_id_a;
w2h_list_t *config_class_b;
w2h_list_t *config_id_b;

/**
* Queue store IO data packet
*/
w2h_queue_t *inqueue;

/**
* a buf point
*/
void *mem;

pid_t ch_pid;

/**
* init w2h_log with config file
* @param config_file:config file
* @return 0 on success,negative number when failed 
*/
extern  int w2h_init(char *config_file);
/** 
* produce a log
* @param classess : classes name, splited by a space
* @param id:id name
* @param fmt:format of message
* @return 0 on success,negative number when failed 
*/ 
extern int w2h_log(char *classes,char *id,char *fmt,...);
/**
* finish w2h_log
* deal with memory and other things
*/
extern void w2h_finish();

#endif
