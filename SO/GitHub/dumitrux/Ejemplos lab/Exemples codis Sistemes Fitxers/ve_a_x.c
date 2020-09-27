#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void escribe(char *m)
{
	write(1,m,strlen(m));
}
void main(int argc,char *argv[])
{
	int fd;
	int t=0,ret;
	char c;
	char men[128];
	if (argc<3){
		escribe("Numero de parametros incorrecto: ve_a_x fichero posicion\n");
		exit(0);
	}
	fd=open(argv[1],O_RDONLY);
	if (fd<0) perror("open");
	t=lseek(fd,atoi(argv[2]),SEEK_SET);
	ret=read(fd,&c,sizeof(c));
	if (ret<0) {
		perror("Error de lectura\n");
		exit(0);
	}else if(ret==0) escribe("Estabas al final del fichero y no hay nada que leer\n");
	else write(1,&c,sizeof(c));
	write(1,"\n",1);
	close(fd);
}
