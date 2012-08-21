/**
* @author gotaly
* @data	2012-08-10
* @email gotawork@163.com
*/

#ifndef INC_H
#define INC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

enum {
	LIST_CLASS_A = 5920 ,
	LIST_CLASS_B,
	LIST_ID_A ,
	LIST_ID_B,
};

#define SHM_SIZE  10*1024*1024
#define MSG_BUF_SIZE  1024
#define MAX_NAME_LEN   100


#endif
