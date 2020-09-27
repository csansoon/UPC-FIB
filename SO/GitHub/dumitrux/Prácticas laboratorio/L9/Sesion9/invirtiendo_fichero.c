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
	char buffer1[256];
	char buffer2[256];
	
	int f1 = open(argv[1], O_RDONLY);
	sprintf(buffer2,"%s.inv", argv[1]);
	
	int f2 = creat(buffer2, 0666);
	int f3 = lseek(f2,0,SEEK_END);
	lseek(f2, 0, SEEK_SET);
	
	while(f3!= 0) {
		lseek(f1,-1,SEEK_CUR);
		read(f1,buffer1,1);
		write(f2,buffer1,1);
		--f3;
	}
	close(f1);
	close(f2);
}
