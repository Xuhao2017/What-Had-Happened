/**
* @author gotaly
* @data	2012-08-10
* @email gotawork@163.com
*/
#ifndef W2H_FORMAT_H
#define W2H_FORMAT_H

#include "inc.h"

/** 
* format of  a record in config file
*/
struct w2h_format_s{
	char *name; /**<  */ 
	char *logfile_name; /**< name of logfile to be produced */
	char *time; /**< time of log when produced */
	char *data; /**< format of a record */
	char *tag; /**< name of tag */
	char *app_name; /**< name of application */
};
typedef struct w2h_format_s w2h_format_t;

/**
* create a w2h_format 
* @return a w2h_format_t point on success,NULL on failed
*/
extern w2h_format_t *w2h_format_create(void);
/**
* init a w2h_format_t 
* @param format:which to be inition
*/
extern void w2h_format_init(w2h_format_t *format);
/**
* copy logfile name to format
* @param format: add to 
* @param logfile_name: name of logfile
*/
extern void w2h_format_add_lfn(w2h_format_t *format,const char *logfile_name);
/**
* copy time to format
* @param format: add to 
* @param time: time when produce the log 
*/
extern void w2h_format_add_time(w2h_format_t *format,const char *time);
/**
* copy all log data to format
* @param format: add to 
* @param time:all log data format 
*/
extern void w2h_format_add_data(w2h_format_t *format,const char *data);
/**
* copy tag to format
* @param format: add to 
* @param time:tag 
*/
extern void w2h_format_add_tag(w2h_format_t *format,const char *tag);
/**
* copy name of application to format
* @param format: add to 
* @param time:name of application 
*/
extern void w2h_format_add_an(w2h_format_t *format,const char *app_name);
/**
* copy name of config class or id 
* @param format: add to 
* @param time:name of class or in in config file such as class.DEBUG 
*/
extern void w2h_format_add_name(w2h_format_t *format,const char *name);
/**
* delete a format 
* release all memory 
* @param format: to be deleted 
*/
extern void w2h_format_del(w2h_format_t *format);

#endif 

