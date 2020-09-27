#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

void signal_recibido(int s) {
	char buf[256];
	sprintf(buf, "Ha llegado signal SIGINT\n");
	write(1,buf,strlen(buf));
}


main(){
	char c;
	int ret;
	char buffer[1024];
	signal(SIGINT,signal_recibido);
	ret=read(0,&c,sizeof(char));
	if(ret>0) sprintf(buffer, "Se ha hecho el read\n");
	else if(ret<0) sprintf(buffer,"%s\n",strerror(errno));
	else sprintf(buffer, "Error read\n");
	write(1,&buffer,strlen(buffer));
	write(1, &c, sizeof(char));
	
}
