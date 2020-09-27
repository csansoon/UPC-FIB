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
    char buf_x[256];
	int file = open("salida.txt", O_RDWR);
    if(file < 0) error_y_exit("error al obrir el fitxer",1);

    lseek(file,-2,SEEK_END);
    sprintf(buf_x,"X");
	read(file,buf_ult,sizeof(char));
	write(file,buf_x,strlen(buf_x));

}
