
#include "w2h_queue.h"
#include "inc.h"
#include "w2h_shm.h"
#include "w2h_dir.h"

#define SLEEP_TIME 2
#define BUF_SIZE 1024


static w2h_queue_t *queue;
static char *shm;
static void prepare_queue()
{
	shm = w2h_shm_create(SHM_SIZE);	
	queue = w2h_queue_create(shm,SHM_SIZE);
}

static int prepare_file(char *file)
{
	if ( !(strcmp(file,"stdout")) || !(strcmp(file,"stderr"))){
		return 1;	
	}

	char *dir;

	if ( !(w2h_file_exist(file))){
		dir = w2h_get_dir(file);		
		if( !(w2h_file_exist(dir))){
			if( (w2h_make_dir(dir)))
				return -1;
		}

	}
	free(dir);
	return w2h_file_open(file); 
}


static void *buf =NULL;
static size_t item_len = 0;
static void deal_io()
{
	size_t filename_len;
	char *filename;
	char *content;
	int fd;

	w2h_queue_dequeue(queue,&buf,&item_len);
	filename_len = *((size_t *)buf);
	filename = (char *)buf+sizeof(size_t);
	if (0 == filename_len)
		filename = "stdout";
	content = (char *)buf+ sizeof(size_t) + filename_len;
	fd =  prepare_file(filename);
	if (fd >= 0){
	/**
	* if input is  a string ,shoul write one less byte
	*/
		write(fd,content,item_len-sizeof(size_t) - filename_len);	
	}
	w2h_file_close(fd);
}

static void clear_queue(void){
 	/**< need not free shared memory free(queue); */
	free(buf);
	w2h_shm_del(shm);
	w2h_shm_clear();
}

static int stop = 0;
void sig_handler(int sig)
{
	if (sig == SIGTERM)
		stop = 1;
}
static void regist_sigs(void)
{
	signal(SIGTERM,sig_handler);	
}

void output_proc(void)
{
	regist_sigs();
	prepare_queue();
	usleep(100);

	while(1){
		if (w2h_queue_empty(queue)){
			if (stop)	
				break;
			sleep(SLEEP_TIME);		
		} else{	
			deal_io();
		}
	}
	clear_queue();
}
