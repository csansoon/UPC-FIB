#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void escribe(char *m)
{
	write(1,m,strlen(m));
}
void main(int argc,char *argv[])
{
	int fd;
	int t;
	char men[128];
	if (argc==1) {
		escribe("Numero de parametros incorrecto\n");
		exit(0);
	}
	fd=open(argv[1],O_RDONLY);
	if (fd<0) perror("COn o_CREAT tampoco");
	t=lseek(fd,0,SEEK_END);
	sprintf(men,"EL tamanyo es %d\n",t);
	escribe(men);
	close(fd);
}
