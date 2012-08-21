#ifndef W2H_LOG_H
#define W2H_LOG_H

#include "w2h_list.h"
#include "w2h_queue.h"
#include "w2h_shm.h"
#include "w2h_rules.h"
#include "w2h_format.h"
#include "inc.h"
#include "w2h_lua.h"

w2h_list_t *config_class_a;
w2h_list_t *config_id_a;
w2h_list_t *config_class_b;
w2h_list_t *config_id_b;

w2h_queue_t *inqueue;

void *mem;
pid_t ch_pid;

extern  int w2h_init(char *config_file);
extern int w2h_log(char *classes,char *id,char *fmt,...);
extern void w2h_finish();

#endif
