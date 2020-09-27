// Este programa escribe enteros en un fichero que recibe como parametro (argv[1]. 
// Escribe a partir del numero que tambien se le pasa en argv[2]
// Escribe 100 enteros
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
	escribe("Usage: escribe_enteros fichero numero_inicial\n");
	exit(0);
}
int  main(int argc,char *argv[])
{
	int fd, ret;
	int valor; // Usamos esta variable para leer del fichero
	int i;
	if (argc!=3) Usage();
	if ((fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0600))<0) error("open");
	valor=atoi(argv[2]);
	for (i=0;i<100;i++){
		write(fd,&valor,sizeof(int));
		valor++;
	}
	close(fd);
}
	
