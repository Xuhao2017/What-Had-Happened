
#ifndef W2H_RULES_H
#define W2H_RULES_H

#include "inc.h"

struct w2h_rules_format_s{
	char *logfile_name;
	char *time;
	char *data;
	   
};
typedef struct w2h_rules_format_s w2h_rules_format_t;


struct w2h_rules_s{
	w2h_rules_format_t format;
	char *logfile_name; /**< file name of log */
	char *tag;
	char *app_name;
	char *time;
	char *msg;
	char *data;
	pid_t pid;
};
typedef struct w2h_rules_s w2h_rules_t;

extern void w2h_rules_init(w2h_rules_t *rules);
extern int w2h_rules_fill_time(w2h_rules_t *rule,time_t time);
extern int w2h_rules_fill_logfile_name(w2h_rules_t *rule);
extern int w2h_rules_fill_data(w2h_rules_t *rule);
extern void w2h_rules_free(w2h_rules_t *rule);


#endif
