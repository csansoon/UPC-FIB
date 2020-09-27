#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


void error_cs(char *msj,int ec)
{
	perror(msj);
	exit(ec);
}
int main(int argc,char *argv[])
{
	char buff[128];
	char buff2[128];
	char *f="RUN.";
	int i=0;
	int fd,num,ret,fd2;
	int ultima_vez=0;
	if ((mknod("mi_pipe",S_IFIFO|S_IRWXU,0)<0) && (errno!=EEXIST)) error_cs("Creando la pipe ",1);
	fd=open("mi_pipe",O_RDWR);
	if (fd<0) error_cs("openin pipe for reading ",1);
	while((ultima_vez!=-1) && ((ret=read(fd,&num,sizeof(num)))>0)){
		if ((num!=ultima_vez) && (num!=-1)){
			// Hay que escribir
			sprintf(buff,"%s%d",f,i);i++;
			fd2=open(buff,O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);
			if (fd2<0) error_cs("opening log file ",1);
			sprintf(buff2,"Antes habia %d procesos running y ahora %d\n",ultima_vez,num);
			write(fd2,buff2,strlen(buff2));
			close(fd2);
		}
		ultima_vez=num;
	}
}
	
		

