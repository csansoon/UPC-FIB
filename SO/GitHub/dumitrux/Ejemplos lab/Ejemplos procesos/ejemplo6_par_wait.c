#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

main() {

int ret;
int status;
char buf[80];
int *p = NULL;
ret =fork();

switch (ret) {
case -1: perror("Error en el fork");
	 exit(1);
case 0:  *p=3;   	/* descomentar para ver la muerte  por sigsegv */
	exit(1);  	/* muero por exit */
default: waitpid(-1,&status,0);
	 sprintf(buf, "Valor status: %d\n", status);
	 write (1, buf, strlen(buf));
	 sprintf(buf, "Valor 1<<8 %d\n", (unsigned int)1<<8);
	 write (1, buf, strlen(buf));
	 sprintf(buf, "WIFEXITED: %d\n", WIFEXITED(status));
	 write (1, buf, strlen(buf));
	 sprintf(buf, "WIFSIGNALED: %d\n", WIFSIGNALED(status)); 
	 write (1, buf, strlen(buf));
	 if (WEXITSTATUS(status)){
	 	sprintf(buf, "WEXITSTATUS: %d\n", WEXITSTATUS(status)); 
	 	write (1, buf, strlen(buf));
	 } else {
	 	sprintf(buf, "WTERMSIG: %d\n", WTERMSIG(status)); 
	 	write (1, buf, strlen(buf));

	}
	


}

}


