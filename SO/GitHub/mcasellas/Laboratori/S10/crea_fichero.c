#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void error_y_exit(char* msg,int error_status) {
	perror(msg);
	exit(error_status);
}

int main() {
	char buf[256];
	int fitxer = creat("salida.txt",O_CREAT|O_RDWR);
	if (fitxer < 0) error_y_exit("error al crear el nou fitxer",1);
	sprintf(buf,"ABCD");
	write(fitxer,buf,strlen(buf));
}
