#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// Este programa crea un nuevo proceso y los dos, padre e hijo leen del fichero 
// que abren antes del fork, asi que comparten el puntero de l/e. Entre los dos
// el fichero se lee solo 1 vez. 
// La suma de las A's que indicaran los dos procesos es el total de A's del 
// fichero fitxer.txt
void error(char *m)
{
	perror(m);
	exit(0);
}
void main(int argc,char *argv[])
{
	int fd,pid,n,numA=0;
	char str[128],car;
	fd = open("fitxer.txt", O_RDONLY);
	if (fd<0) error("open");
	pid = fork();
	if (pid<0) error("fork");
	while ( ( n = read(fd, &car, 1) ) > 0 )
		if ( car == 'A' ) numA++;
	sprintf(str, "El número d’As és %d\n", numA);
	write(1, str, strlen(str));
}

