/**
* @author gotaly
* @data	2012-08-10
* @email gotawork@163.com
*/

#ifndef W2H_RULES_H
#define W2H_RULES_H

#include "inc.h"

/** 
* format of a log record
*/
struct w2h_rules_format_s{
	char *logfile_name;
	char *time;
	char *data;
	   
};
typedef struct w2h_rules_format_s w2h_rules_format_t;

/**
* data of a log record to be stroe
*/
struct w2h_rules_s{
	w2h_rules_format_t format;
	char *logfile_name; /**< file name of log */
	char *tag;
	char *app_name;
	char *time;
	char *msg; /**< user give in w2h_log funciton */
	char *data;
	pid_t pid;
};
typedef struct w2h_rules_s w2h_rules_t;

/**
* init a w2h_rules_t dynamicly
* @param rules: to be inited
*/
extern void w2h_rules_init(w2h_rules_t *rules);
/**
* add time to log record
* @param rule : a log record
* @param time : time when produced 
* @return : 0 on success
*/
extern int w2h_rules_fill_time(w2h_rules_t *rule,time_t time);
/**
* add name of logfile to log record
* @param rule : a log record
* @param time : add name of logfile 
* @return : 0 on success
*/
extern int w2h_rules_fill_logfile_name(w2h_rules_t *rule);
/**
* add all log data to log record
* @param rule : a log record
* @param time :all log data 
* @return : 0 on success
*/
extern int w2h_rules_fill_data(w2h_rules_t *rule);
/**
* free rules's memory 
* @param rule:to be free
*/
extern void w2h_rules_free(w2h_rules_t *rule);


#endif
