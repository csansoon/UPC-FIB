#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


void error_cs(char *msj,int ec)
{
	perror(msj);
	exit(ec);
}
void usage()
{
	char buff[128];
	sprintf(buff,"1deN N\n");
	write(2,buff,strlen(buff));
	exit(1);
}
int main(int argc,char *argv[])
{
	int ret,i,num;
	char buff[128];
	if ((argc!=2) || (i=atoi(argv[1]))<0) usage();
	while((ret=read(0,&num,sizeof(num)))>0){
		sprintf(buff,"%d ",num);
		write(1,buff,strlen(buff));
		lseek(0,(i-1)*sizeof(int),SEEK_CUR);
	}
}
