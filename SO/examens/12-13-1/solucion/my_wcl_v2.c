#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void error_cs(char *msj,int ec)
{
	perror(msj);
	exit(ec);
}
int main(int argc,char *argv[])
{
	char c[32];
	int ret,i;
	char buff[128];
	int lineas=0;
	while((ret=read(0,c,sizeof(c)))>0){
		for(i=0;i<ret;i++){
			if (c[i]=='\n') lineas++;
		}
	}
	sprintf(buff,"El numero de lineas es %d\n",lineas);
	write(1,buff,strlen(buff));
}
