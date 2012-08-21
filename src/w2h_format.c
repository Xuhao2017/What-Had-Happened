#include "w2h_format.h"


w2h_format_t *w2h_format_create(void)
{
	w2h_format_t *format= malloc(sizeof(w2h_format_t));
	w2h_format_init(format);
	return format;
}

void w2h_format_init(w2h_format_t *format)
{
	if (NULL == format)	
		return ;
	format->logfile_name = NULL;
	format->time= NULL;
	format->data= NULL;
	format->tag= NULL;
	format->app_name= NULL;
}

void w2h_format_add_lfn(w2h_format_t *format,const char *logfile_name)
{
	if (NULL == format)
		return ;
	if (NULL == logfile_name){
		format->logfile_name = NULL;
		return ;
	}		
	format->logfile_name = malloc((strlen(logfile_name)+1)*sizeof(char));
	memcpy(format->logfile_name , logfile_name,strlen(logfile_name));
	*((char *)format->logfile_name + strlen(logfile_name)) = '\0';
}

void w2h_format_add_name(w2h_format_t *format,const char *name)
{
	if (NULL == format)
		return ;
	if (NULL == name){
		format->name = NULL;	
		return ;
	}
	format->name = malloc((strlen(name)+1)*sizeof(char));
	memcpy(format->name,name,strlen(name));
	*((char *)format->name+ strlen(name)) = '\0';
}

void w2h_format_add_time(w2h_format_t *format,const char *time)
{
	if (NULL == format)
		return ;
	if (NULL == time){
		format->time = NULL;	
		return ;
	}
	format->time= malloc((strlen(time)+1)*sizeof(char));
	memcpy(format->time, time,strlen(time));
	*((char *)format->time+ strlen(time)) = '\0';
}

void w2h_format_add_data(w2h_format_t *format,const char *data)
{
	if (NULL == format)
		return ;
	if (NULL == data){
		format->data  = NULL;	
		return ;
	}
	format->data= malloc((strlen(data)+1)*sizeof(char));
	memcpy(format->data,data ,strlen(data));
	*((char *)format->data+ strlen(data)) = '\0';
}

void w2h_format_add_tag(w2h_format_t *format,const char *tag)
{
	if (NULL == format)
		return ;
	if (NULL == tag){
		format->tag = NULL;	
		return ;
	}
	format->tag= malloc((strlen(tag)+1)*sizeof(char));
	memcpy(format->tag,tag,strlen(tag));
	*((char *)format->tag+ strlen(tag)) = '\0';
}

void w2h_format_add_an(w2h_format_t *format,const char *app_name)
{
	if (NULL == format)
		return ;
	if (NULL == app_name){
		format->app_name = NULL;	
		return ;
	}
	format->app_name= malloc((strlen(app_name)+1)*sizeof(char));
	memcpy(format->app_name,app_name,strlen(app_name));
	*((char *)format->app_name+ strlen(app_name)) = '\0';
}

void w2h_format_del(w2h_format_t *format)
{
	if (NULL == format)
		return ;
	free(format->logfile_name);
	free(format->time);
	free(format->data);
	free(format->tag);
	free(format->app_name);
	free(format);
}
