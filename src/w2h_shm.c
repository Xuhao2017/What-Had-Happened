/**
* @file w2h_queue.h
* @author gotaly
* @data	2012-08-14
*/
#include "w2h_shm.h"

static int key = SHM_KEY;
static int shm_id;

char *w2h_shm_create(size_t shm_size)
{
	char *shm_addr;
	int shm_oflag = IPC_CREAT | 0666 ; /* should change 0666 */
	
	shm_id = shmget(key,shm_size,shm_oflag);
	if (-1 == shm_id)
		return NULL;
	shm_addr = shmat(shm_id,NULL,0);
	if ((void *)-1 == shm_addr)
		return NULL;
	return shm_addr;	
}


int w2h_shm_del(char *shm_addr)
{
	int res;
	res = shmdt(shm_addr);
	if (res)
		return -1;
	return 0;

}

int w2h_shm_clear(void)
{
	int res = shmctl(shm_id,IPC_RMID,NULL);
	if (-1 == res )
		return -1;
	return 0;
}
