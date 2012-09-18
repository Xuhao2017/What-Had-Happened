
#include "w2h_rules.h"

void w2h_rules_init(w2h_rules_t *rules)
{
	rules->format.logfile_name = NULL;
	rules->format.time = NULL;
	rules->format.data= NULL;

	rules->logfile_name = NULL;
	rules->tag= NULL;
	rules->app_name= NULL;
	rules->time= NULL;
	rules->msg= NULL;
	rules->data= NULL;
	rules->pid= -1;
}

int w2h_rules_fill_time(w2h_rules_t *rule,time_t time)
{
	if (NULL == rule )
		return -1;
	if (NULL == rule->format.time)
		return 0;

	int i;
	int former;
	int format_time_cur;
	int len = strlen(rule->format.time);
	char buf[sizeof(int)+1];
	struct tm *f_time;

	char *format_time = malloc((len +1)*sizeof(char)+6*sizeof(int));

	f_time = localtime(&time);
	former = 0;
	format_time_cur  = 0;
	for (i=0;i<len;i++){
		if ('%' == *(rule->format.time + i) &&(
			'y' == *(rule->format.time+i+1) ||
			'd' == *(rule->format.time+i+1) ||
			'M' == *(rule->format.time+i+1) ||
			'm' == *(rule->format.time+i+1) ||
			'h' == *(rule->format.time+i+1) ||
			's' == *(rule->format.time+i+1) 
			)){

			memcpy(format_time+format_time_cur,rule->format.time+former,i-former);	
			format_time_cur += i-former;
			former += i-former; 
			
			memset(buf,0,sizeof(int)+1);
			switch( *(rule->format.time+i+1) ){
			case 'y':
				snprintf(buf,sizeof(int)+1,"%d",f_time->tm_year+1900);
				memcpy(format_time+format_time_cur,buf,strlen(buf));
				break;
			case 'd':
				snprintf(buf,sizeof(int)+1,"%02d",f_time->tm_mday);
				memcpy(format_time+format_time_cur,buf,strlen(buf));
				break;
			case 'M':
				snprintf(buf,sizeof(int)+1,"%02d",f_time->tm_mon+1);
				memcpy(format_time+format_time_cur,buf,strlen(buf));
				break;
			case 'm':
				snprintf(buf,sizeof(int)+1,"%02d",f_time->tm_min);
				memcpy(format_time+format_time_cur,buf,strlen(buf));
				break;
			case 's':
				snprintf(buf,sizeof(int)+1,"%02d",f_time->tm_sec);
				memcpy(format_time+format_time_cur,buf,strlen(buf));
				break;
			case 'h':
				snprintf(buf,sizeof(int)+1,"%02d",f_time->tm_hour);
				memcpy(format_time+format_time_cur,buf,strlen(buf));
				break;
			default:	
				break;
			}		
			format_time_cur +=strlen(buf); 
			former +=2;
		}	
	}
	memcpy(format_time+format_time_cur,rule->format.time+former,len -former);
	format_time_cur += len-former;
	*(format_time + format_time_cur) = '\0';
	rule->time = format_time;
	return 0;
}


int w2h_rules_fill_logfile_name(w2h_rules_t *rule)
{
	if (NULL == rule )
		return -1;
	if (NULL == rule->format.logfile_name){
		char *default_name = "w2h_default.log";	
		rule->logfile_name = malloc(strlen(default_name) +1);
		snprintf(rule->logfile_name,strlen(default_name)+1,"%s",default_name);
		return 0;
	}

	int index;
	int logfile_cur;
	time_t cur_time;
	struct tm *today_time;
	int len= strlen(rule->format.logfile_name);
	char buf[sizeof(int)+1];

	int i;
	index = -1;
	logfile_cur =0;
	cur_time = time(NULL);		
	today_time = localtime(&cur_time);
	char *logfile_name= malloc(len + 3*sizeof(int)+sizeof(char));			
	for(i=0;i<len;i++){
		if ('$' == *(rule->format.logfile_name +i) &&
			'T' == *(rule->format.logfile_name +i+1)){
			index = i;
		}	
	}
	if (index >=0){
		memcpy(logfile_name,rule->format.logfile_name,index);
		logfile_cur = index;
		index +=2;

		snprintf(buf,sizeof(int)+1,"%d",today_time->tm_year+1900);
		memcpy(logfile_name+logfile_cur,buf,strlen(buf));
		logfile_cur += strlen(buf);
		memset(buf,0,sizeof(int)+1);

		snprintf(buf,sizeof(int)+1,"%02d",today_time->tm_mon+1);
		memcpy(logfile_name+logfile_cur,buf,strlen(buf));
		logfile_cur += strlen(buf);
		memset(buf,0,sizeof(int)+1);

		snprintf(buf,sizeof(int)+1,"%02d",today_time->tm_mday);
		memcpy(logfile_name+logfile_cur,buf,strlen(buf));
		logfile_cur += strlen(buf);
		memset(buf,0,sizeof(int)+1);
	}
	if (index < 0)
		index = 0;
	memcpy(logfile_name+logfile_cur,rule->format.logfile_name+index,len-index);
	logfile_cur += len-index;

	*(logfile_name+logfile_cur) = '\0';
	rule->logfile_name  = logfile_name;
	
	return 0;
}


int w2h_rules_fill_data(w2h_rules_t *rule)
{

	if (NULL == rule )
		return -1;
	int msg_len;
	msg_len = rule->msg == NULL? 0:strlen(rule->msg);
	if (NULL == rule->format.data){
		if(NULL == rule->msg ){
			return 0;	
		}
		rule->data = malloc(msg_len+1);
		snprintf(rule->data,msg_len+1,"%s",rule->msg);
		return 0;
	}

	int len ;
	int i;
	int data_cur;
	int former;
	int format_len;
	int time_len;
	int tag_len;
	int app_len;


	format_len = rule->format.data == NULL ? 0:strlen(rule->format.data);
	time_len = rule->time == NULL ? 0:strlen(rule->time);
	tag_len = rule->tag== NULL ? 0:strlen(rule->tag);
	app_len = rule->app_name== NULL ? 0:strlen(rule->app_name);

	len =  format_len;
	len += tag_len;
	len += app_len;
	len += time_len;
	len += msg_len;
	len += sizeof(pid_t);
	char *data = malloc(len*sizeof(char));

	former  = 0;
	data_cur = 0;
	char buf[sizeof(pid_t)+1];
	for (i=0;i<format_len;i++){
		if ('$' == *(rule->format.data +i) && (
			't' == *(rule->format.data+i+1) || 
			'T' == *(rule->format.data+i+1) || 
			'a' == *(rule->format.data+i+1) || 
			'p' == *(rule->format.data+i+1) || 
			'm' == *(rule->format.data+i+1)  
			)){
			memcpy(data+data_cur,rule->format.data+former,i-former);		
			data_cur += i - former;
			former +=i-former;
			switch(*(rule->format.data+i+1)){
			case 't':
				memcpy(data+data_cur,rule->time,time_len);
				data_cur += time_len;
				break;
			case 'T':
				memcpy(data+data_cur,rule->tag,tag_len);
				data_cur += tag_len;
				break;
			case 'a':
				memcpy(data+data_cur,rule->app_name,app_len);
				data_cur += app_len;
				break;
			case 'p':
				snprintf(buf,sizeof(pid_t)+1,"%ld",(long) rule->pid);
				memcpy(data+data_cur,buf,strlen(buf));
				data_cur += strlen(buf);
				break;
			case 'm':
				memcpy(data+data_cur,rule->msg,msg_len);
				data_cur += msg_len;
				break;
			default:	
				break;
			}
			former +=2;
		}
	
	}
	memcpy(data+data_cur,rule->format.data+former,format_len-former);
	data_cur += format_len-former;
	*(data+data_cur) = '\0';
	rule->data = data;

	return 0;
}

void w2h_rules_free(w2h_rules_t *rule)
{
	free(rule->format.time);
	free(rule->format.data);
	free(rule->format.logfile_name);

	free(rule->logfile_name);
	free(rule->app_name);
	free(rule->tag);
	free(rule->time);
	free(rule->msg);
	free(rule->data);
}
