#include <stdio.h>
#include "w2h_log.h"

int main(int argc,char *argv[])	
{
	char *config = "./config.w2h";
	w2h_init(config);
	w2h_log("debug","debug_0","have a bug in file %s,line %d \n",__FILE__,__LINE__);
	w2h_finish();
	return 0;
}

