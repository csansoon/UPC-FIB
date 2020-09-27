#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


void error_y_exit(char* msg, int error_status) {
	perror(msg);
	exit(error_status);
}

int main(int argc, char *argv[]) {
	char buffer[256];
	char bufferX[256];
	
	int f1 = open(arvg[1], O_RDWR);
	int f2 = lseek(f1,0,SEEK_END);
	if(f==-1) error_y_exit("Ha fallado open",1);
	
	sprintf(bufferX,'X')
	int x = atoi(arvg[2]);
	while(x != f2) {
		lseek(f1,x,SEEK_SET);
		write();
		++x;
	}
	close(f1);
}
