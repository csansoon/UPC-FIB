#include <unistd.h>
#include <string.h>
#include <stdio.h>

main() {
	char *buf="fin ejecución\n";
	char buffer[256];
	int ret;
	
	ret=read(0,&buffer,sizeof(buffer));
	while(ret>0) {
		write(2,buffer,strlen(buffer));
		ret=read(0,&buffer,sizeof(buffer));
	}
	write(1,buf,strlen(buf));
}
