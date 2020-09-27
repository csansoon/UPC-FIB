// Este programa lee un fichero (que recibe como parametro) y 
// lo escribe en la salida std. En fichero de entrada contiene caracteres
// Para leer, utilizaremos un buffer para minimizar el numero de lecturas
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(char *m)
{
	perror(m);
	exit(0);
}
int escribe(char *m)
{
	return write(1,m,strlen(m));
}
void Usage()
{
	escribe("Usage: lectura_con_buffer fichero\n");
	exit(0);
}
int  main(int argc,char *argv[])
{
	char buff[128];
	int fd, ret;
	if (argc!=2) Usage();
	if ((fd=open(argv[1],O_RDONLY))<0) error("open");
	while((ret=read(fd,buff,sizeof(buff)))>0)
		write(1,buff,ret);
}
	
