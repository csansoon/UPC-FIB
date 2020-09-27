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
	int fd,num;
	int i=0;
	while((read(0,&buff[i],1)>0) && (buff[i]!='\n')) i++;
	buff[i]='\0';
	num=atoi(buff);
	fd=open("mi_pipe",O_WRONLY);
	if (fd<0) error_cs("opening pipe ",1);
	write(fd,&num,sizeof(num));
	close(fd);
	sprintf(buff2,"He leido el numero %d\n",atoi(buff));
	write(2,buff2,strlen(buff2));
}
	
		

