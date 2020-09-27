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

int main() {
	char buffer[256];
	char bufferX[256];
	
	int f = open("salida.txt", O_RDWR);
	if(f==-1) error_y_exit("Ha fallado open",1);
	
	// se lee último carácter
	lseek(f,-1,SEEK_END);
	read(f, buffer, sizeof(char));
	// posicion anterior a último se añade 'X'
	lseek(f,-1,SEEK_CUR);
	sprintf(bufferX,"X");
	write(f, bufferX,strlen(bufferX));
	// se añade último carácter de nuevo
	write(f,buffer,strlen(buffer));
}
