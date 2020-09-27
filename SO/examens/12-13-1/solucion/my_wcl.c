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
	char c;
	char buff[128];
	int lineas=0;
	while(read(0,&c,sizeof(char))>0){
		if (c=='\n') lineas++;
	}
	sprintf(buff,"El numero de lineas es %d\n",lineas);
	write(1,buff,strlen(buff));
}
