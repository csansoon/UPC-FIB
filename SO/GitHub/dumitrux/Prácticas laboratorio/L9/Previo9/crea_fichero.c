#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


void error_y_exit(char* msg, int error_status) {
	perror(msg);
	exit(error_status);
}

int main() {
	char buffer[256];
	int f = creat("salida.txt", O_CREAT|O_TRUNC|0600);
	if(f==-1) error_y_exit("Ha fallado creat",1);
	sprintf(buffer, "ABCD");
	write(f,buffer,strlen(buffer));
}
