#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void error_cs(char *msj,int ec)
{
        perror(msj);
        exit(ec);
}


int main(int argc,char *argv[])
{
	int fd,num,pos;
	char num_ascii[32];
	char b[128];
	fd=open("FAT.dat",O_RDONLY);
	if (fd<0) error_cs("Opening input file ",1);
	pos=atoi(argv[1]);
	if (pos<0){
		sprintf(b,"parametro incorrecto \n");
		write(2,b,strlen(b));
		exit(1);
	}
	lseek(fd,pos*sizeof(int),SEEK_SET);
	read(fd,&num,sizeof(num));
	while(num!=-1){
		sprintf(num_ascii,"%d ",num);
		write(1,num_ascii,strlen(num_ascii));
		lseek(fd,num*sizeof(int),SEEK_SET);
		read(fd,&num,sizeof(num));
	}
	write(1,"\n",1);
	close(fd);
}

