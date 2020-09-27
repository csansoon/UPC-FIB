#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void error_y_exit(char *msg,int exit_status) {
	perror(msg);
	exit(exit_status);
}

int main(int argc,char *argv[]){

char buffer[80];
int pid;

sprintf(buffer, "Sóc el procés: %d\n", getpid()); // Missatge del pare
write(1,buffer,strlen(buffer));

if ((pid = fork()) < 0) error_y_exit("Error en el fork",1);


if (pid == 0){

	sprintf(buffer, "Sóc el procés: %d. El paràmetre és %s\n", getpid(), argv[1]);
	write(1,buffer,strlen(buffer));
}


while(1);

return 0;
}
