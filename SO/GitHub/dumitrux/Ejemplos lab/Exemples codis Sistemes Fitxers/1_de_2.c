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
	if (argc==1){
		escribe("Numero de parametros incorrecto\n");
		exit(0);
	}
	fd=open(argv[1],O_RDONLY);
	if (fd<0) perror("open");
	while((ret=read(fd,&c,sizeof(c)))>0){
		write(1,&c,sizeof(c));
		t=lseek(fd,1,SEEK_CUR);
	}
	close(fd);
}
