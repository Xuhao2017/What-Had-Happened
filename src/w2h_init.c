#include "inc.h"
#include "w2h_format.h"
#include "w2h_list.h"
#include "w2h_log.h"
#include "w2h_lua.h"


#include <sys/wait.h>

extern void output_proc(void);

static void init_config_list(void)
{
	config_class_a = w2h_list_creat();	
	config_class_b = w2h_list_creat();	
	config_id_b = w2h_list_creat();	
	config_id_a = w2h_list_creat();	
}

static void get_conf_from_lua(lua_State *conf,char *category,int list_type)
{
	lua_getglobal(conf,category);	
	lua_pushnil(conf);
	while (lua_next(conf,-2)){
		w2h_format_t *fmt= w2h_format_create(); 
		w2h_format_add_name(fmt,lua_tostring(conf,-2));

		lua_getfield(conf,-1,"logfile_name");	
		w2h_format_add_lfn(fmt,lua_tostring(conf,-1));
		lua_pop(conf,1);

		lua_getfield(conf,-1,"time");	
		w2h_format_add_time(fmt,lua_tostring(conf,-1));
		lua_pop(conf,1);

		lua_getfield(conf,-1,"data");	
		w2h_format_add_data(fmt,lua_tostring(conf,-1));
		lua_pop(conf,1);

		lua_getfield(conf,-1,"app_name");	
		w2h_format_add_an(fmt,lua_tostring(conf,-1));
		lua_pop(conf,1);

		lua_getfield(conf,-1,"tag");	
		w2h_format_add_tag(fmt,lua_tostring(conf,-1));
		lua_pop(conf,1);
					
		switch (list_type){
		case LIST_CLASS_A :	
			w2h_list_append(config_class_a,fmt,sizeof(w2h_format_t));
			break;
		case LIST_CLASS_B :
			w2h_list_append(config_class_b,fmt,sizeof(w2h_format_t));
			break;
		case LIST_ID_A:
			w2h_list_append(config_id_a,fmt,sizeof(w2h_format_t));
			break;
		case LIST_ID_B:
			w2h_list_append(config_id_b,fmt,sizeof(w2h_format_t));
			break;
		}						

		lua_pop(conf,1);
	}
	lua_pop(conf,1);
}

static int read_config(char *file)
{
	char *conf_lua_script="class = {};id = {};";
	lua_State *conf= luaL_newstate();
	if (luaL_loadstring(conf,conf_lua_script) || 
		lua_pcall(conf,0,0,0) ||
		luaL_loadfile(conf,file) ||
		lua_pcall(conf,0,0,0))
		return -1;
	get_conf_from_lua(conf,"class",LIST_CLASS_A);	
	get_conf_from_lua(conf,"id",LIST_ID_A);	
	return 0;
}

static void deal(void *data)
{
	w2h_format_t *format = data;
	printf("logfile_name %s: \n\tdate %s,\ttime %s,\ttag %s,\tapp_name %s\n",
		format->logfile_name,
		format->data,
		format->time,
		format->tag,
		format->app_name);
}

static void print_config()
{
	w2h_list_foreach(config_class_a,deal);
	w2h_list_foreach(config_id_a,deal);
}


static void prepare_guard_thread()
{
	// to do 
}

static void clear_config_list(void)
{
	w2h_list_free(config_class_a);
	w2h_list_free(config_class_b);
	w2h_list_free(config_id_b);
	w2h_list_free(config_id_a);

	w2h_list_del(config_class_a);
	w2h_list_del(config_class_b);
	w2h_list_del(config_id_b);
	w2h_list_del(config_id_a);
}

static int w2h_main(pid_t ch_pid)
{
	mem = w2h_shm_create(SHM_SIZE);
	if (NULL == mem){
		clear_config_list();	
		kill(ch_pid,SIGTERM);
		return -1;
	}
	
	inqueue = w2h_queue_create(mem,SHM_SIZE);
	if (NULL == inqueue){
		clear_config_list();	
		w2h_shm_del(mem);
		kill(ch_pid,SIGTERM);
		return -1;
	}

	return 0;
}

int w2h_init(char *file)
{
	int res;

	init_config_list();	
	res = read_config(file);

	if (res)
		return -1;
	prepare_guard_thread();
	ch_pid = fork();
	switch (ch_pid){
	case 0:
		output_proc();	
		break;
	case -1:
		clear_config_list();
		return -1;
		break;
	default:
		res = w2h_main(ch_pid);
		if (res)
			return -1;
	}

	return 0;
}

void w2h_finish(void)
{
		clear_config_list();	
		w2h_shm_del(mem);
	 	kill(ch_pid,SIGTERM);
		waitpid(ch_pid,NULL,0);
}
