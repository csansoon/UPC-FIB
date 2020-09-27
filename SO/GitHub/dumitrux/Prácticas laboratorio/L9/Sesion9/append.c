#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void error_y_exit(char* msg, int error_status) {
	perror(msg);
	exit(error_status);
}

int main(int argc, char *argv[]) {
	char buffer[256];
	int f1 = open(argv[1], O_RDONLY);
	int f2 = open(argv[1], O_WRONLY);
	if((f2 || f1) == -1) error_y_exit("Ha fallado open", 1);
	
	lseek(f1,0,SEEK_SET);
	int f3 = lseek(f2,0,SEEK_END);
	
	while(f3 != 0) {
		read(f1,buffer,1);
		write(f2,buffer,1);
		--f3;
	}
	close(f1);
	close(f2);
}
