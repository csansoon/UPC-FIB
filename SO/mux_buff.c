#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void Usage() {
	char buff[128];
	sprintf(buff, "Usage: ./mux_buff arg\n");
	write(1, buff, strlen(buff));
	exit (1);
}

void error_y_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void main(int argc, char *argv[]){
	if(argc != 2) Usage();
	int ret, ret2;
	if(ret < 0)error_y_exit("Error en close");
	int n = atoi(argv[1]);
	char *buffer = sbrk(2*n);
	char *ptr = malloc(n);
	char *ptr2 = malloc(n);
	int boolea = 0;
	while((ret = read(20,ptr,n)) > 0){
		
		if(ret < 0)error_y_exit("Error en read a");
		
		boolea = 1;
		if((ret2 = read(21,ptr2,n)) > 0){
			if(ret2 < 0)error_y_exit("Error en read b");
		}
		for(int i = 0; i < 2*n; ++i){
			if(i%2 == 0) buffer[i] = ptr[i/2];
			else buffer[i] = ptr2[i/2];
		}
		if(boolea != 0) ret = write(1,buffer,ret+ret2);
		if(ret < 0) error_y_exit("Error en write del buffer");

	}

	free(ptr);
	free(ptr2);
	sbrk(-2*n);
}
