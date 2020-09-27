#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// Este programa cuenta las A'a que hay en el fichero fitxer.txt. Como el open
// del fichero se hace despues del fork, el puntero de l/e NO es compartido. 
// Por lo tanto, el fichero se leera 2 veces completo y los dos procesos 
// imprimiran el mismo numero de A's
void error(char *m)
{
        perror(m);
        exit(0);
}

void main(int argc,char *argv[])
{
	int fd,pid,n,numA;
	char str[128],car;
	pid = fork();
	if (pid<0) error("fork");
	fd = open("fitxer.txt", O_RDONLY);
	if (fd<0) error("open");
	while ( ( n = read(fd, &car, 1) ) > 0 )
		if ( car == 'A' ) numA++;
	sprintf(str, "El número d’As és %d\n", numA);
	write(1, str, strlen(str));
}

