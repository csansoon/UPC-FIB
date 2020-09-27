#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void error_cs(char *msj,int ec)
{
	perror(msj);
	exit(ec);
}

void usage()
{
	char buff[128];
	strcpy(buff,"Uso:my_wcl_v3 fichin fichout\n");
	write(2,buff,strlen(buff));
	exit(1);
}
int main(int argc,char *argv[])
{
	char c[32];
	int ret,i,fdin,fdout;
	char buff[128];
	int lineas=0;

	if (argc!=3) usage();
	if ((fdin=open(argv[1],O_RDONLY))<0) error_cs("Open fich entrada ",2);
	if ((fdout=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666))<0) error_cs("Open fich salida ",3);

	while((ret=read(fdin,c,sizeof(c)))>0){
		for(i=0;i<ret;i++){
			if (c[i]=='\n') lineas++;
		}
	}
	sprintf(buff,"El numero de lineas es %d\n",lineas);
	write(fdout,buff,strlen(buff));
}
