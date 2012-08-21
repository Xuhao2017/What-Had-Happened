#include "w2h_dir.h"


int w2h_file_exist(char *file)
{
	if (NULL == file)
		return -1;
	return !(access(file,F_OK));
}

char *w2h_get_dir(char *file)
{
	int count = 0;
	int index = 0;
	int i = 0;
	
	while ('\0' != *(file+i)){
		if ('/' == *(file+i)){	
			count++;
			index = i;
		}
		i++;
	}
	if (0 == count){
		return NULL;
	}
	if (1 == count){
		if ('.' == *file){		
			return NULL;
		}
	} else {
		char *dir = malloc((index+1+1)*sizeof(char));	
		memcpy(dir,file,index+1);
		*(dir+index+1) = '\0';
		return dir;
	}
	return NULL;
}

int w2h_make_dir(char *path)
{
	int res;
	int cmd_len= 10+strlen(path);
	char *cmd = malloc(cmd_len * sizeof(size_t));
	snprintf(cmd,cmd_len,"mkdir -p %s",path);
	res = system(cmd);
	return (res == -1) ? 1 : 0 ;
}


int w2h_file_open(char *file)
{
	int fd = open(file,OPEN_MODE,0644);
	return fd;
}

void w2h_file_close(int fd)
{
	if (1 != fd || 2 != fd)
		return ;
	close(fd);	
}


