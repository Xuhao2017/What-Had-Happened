#ifndef W2H_FORMAT_H
#define W2H_FORMAT_H

#include "inc.h"


struct w2h_format_s{
	char *name;
	char *logfile_name;
	char *time;
	char *data;
	char *tag;
	char *app_name;
};
typedef struct w2h_format_s w2h_format_t;


extern w2h_format_t *w2h_format_create(void);
extern void w2h_format_init(w2h_format_t *format);
extern void w2h_format_add_lfn(w2h_format_t *format,const char *logfile_name);
extern void w2h_format_add_time(w2h_format_t *format,const char *time);
extern void w2h_format_add_data(w2h_format_t *format,const char *data);
extern void w2h_format_add_tag(w2h_format_t *format,const char *tag);
extern void w2h_format_add_an(w2h_format_t *format,const char *app_name);
extern void w2h_format_add_name(w2h_format_t *format,const char *name);
extern void w2h_format_del(w2h_format_t *format);

#endif 

