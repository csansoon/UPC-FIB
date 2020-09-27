// Este programa lee un fichero que contiene enteros (en formato binario) 
// y tiene que escribir por la pantalla los numeros con el siguiente formato
// M[i]=valor, donde i indica si es el primer numero , segundo etc y 
// valor el numero en sº
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
	int fd, ret;
	int valor; // Usamos esta variable para leer del fichero
	char num_en_car[32]; // Y esta para convertirlo
	int i=0;
	if (argc!=2) Usage();
	if ((fd=open(argv[1],O_RDONLY))<0) error("open");
	while((ret=read(fd,&valor,sizeof(valor)))>0){
		sprintf(num_en_car,"M[%d]=%d ",i,valor);
		write(1,num_en_car,strlen(num_en_car)); // Usamos strlen y no sizeof para no scribir basura
		i++;
	}
	write(1,"\n",1);
}
	
