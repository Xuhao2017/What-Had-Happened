#include "w2h_log.h"


static void fill_msg(w2h_rules_t *rules,char *fmt,va_list va)
{
	char buf[MSG_BUF_SIZE];
	vsnprintf(buf,MSG_BUF_SIZE,fmt,va);
	rules->msg = malloc(strlen(buf)+sizeof(char));
	memcpy(rules->msg,buf,strlen(buf)+sizeof(char));
}

static int suitable_format(void *data,void *dst)
{
	int res;
	w2h_format_t *format= data;
	char *name = dst;
	res = memcmp(format->name,name,strlen(name));
	return !res;
}


static void cpy_fmt(w2h_rules_t *rules,w2h_format_t *fmt)
{
	if (NULL == fmt )
		return ;
	if (NULL != fmt->logfile_name){
		rules->format.logfile_name = malloc(strlen(fmt->logfile_name) + sizeof(char));
		memcpy(rules->format.logfile_name,fmt->logfile_name,strlen(fmt->logfile_name) + sizeof(char));
	}
  
  	if (NULL != fmt->time){
		rules->format.time= malloc(strlen(fmt->time) + sizeof(char));
		memcpy(rules->format.time,fmt->time,strlen(fmt->time) + sizeof(char));
	}

	if (NULL != fmt->data){
		rules->format.data= malloc(strlen(fmt->data) + sizeof(char));
		memcpy(rules->format.data,fmt->data,strlen(fmt->data) + sizeof(char));
	}

	if (NULL != fmt->tag){
		rules->tag = malloc(strlen(fmt->tag) + sizeof(char));
		memcpy(rules->tag,fmt->tag,strlen(fmt->tag) + sizeof(char));
	}

	if (NULL != fmt->app_name){
		rules->app_name= malloc(strlen(fmt->app_name) + sizeof(char));
		memcpy(rules->tag,fmt->tag,strlen(fmt->tag) + sizeof(char));
	}

	rules->pid  = getpid();
}

static void add_classes(w2h_rules_t *rules,char *classes)
{
	char class[MAX_NAME_LEN];
	int word = 0;

	while (word < strlen(classes) +sizeof(char) +1){
		int word_len = 0;
		while(' ' != *(classes+word+word_len) || '\0' != *(classes+word+word_len))
			word_len++;
		memcpy(class,classes+word,word_len);
		*(class+word_len +1) = '\0';

		list_iter_t fmt_i = w2h_list_user_find(config_id_a,class,suitable_format);  
		w2h_format_t *fmt = (w2h_format_t *)fmt_i->data;
		cpy_fmt(rules,fmt);

		word += word_len+1;
	}
}

static void add_id(w2h_rules_t *rules,char *id)
{
	list_iter_t fmt_i = w2h_list_user_find(config_id_a,id,suitable_format);  
	if (NULL == fmt_i)
		return ;
	w2h_format_t *fmt = (w2h_format_t *)fmt_i->data;
	cpy_fmt(rules,fmt);
}

void *pack_rules(w2h_rules_t *rules,size_t *size)
{
	size_t file_name_len;
	void *pack_buf;

	file_name_len = strlen(rules->logfile_name) + sizeof(char);
	*size = sizeof(size_t);
	*size += strlen(rules->logfile_name) + sizeof(char);
	*size += strlen(rules->data) +sizeof(char);

	pack_buf = malloc(*size * sizeof(char));
	memcpy(pack_buf,&file_name_len,sizeof(size_t));
	memcpy((char *)pack_buf+sizeof(size_t),rules->logfile_name,file_name_len);
	memcpy((char *)pack_buf+sizeof(size_t)+file_name_len,rules->data,*size-sizeof(size_t)-file_name_len);
	return pack_buf;
}

int w2h_log(char *classes,char *id,char *fmt,...)
{
	w2h_rules_t rules;
	w2h_rules_init(&rules);
	void *data;
	size_t size;

	if (NULL != classes)
		add_classes(&rules,classes);
	if (NULL != id)
		add_id(&rules,id);
	va_list va;
	va_start(va,fmt);
	fill_msg(&rules,fmt,va);
	va_end(va);

	w2h_rules_fill_time(&rules,time(NULL));
	w2h_rules_fill_logfile_name(&rules);
	w2h_rules_fill_data(&rules);

	data = pack_rules(&rules,&size);
	w2h_queue_enqueue(inqueue,data,size);

	w2h_rules_free(&rules);
	free(data);

	return 0;
}
