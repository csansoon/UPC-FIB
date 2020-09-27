#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
// Este programa redirecciona la entrada std del programa cuentaA desde el
// fichero que recibe como parametro en argv[1]
// Tambien redireccion la salida std al fichero que recibe en argv[2]
void error(char *s)
{
	perror(s);
	exit(0);
}
void main(int argc,char *argv[])
{
	int fd,pid;
	pid = fork();
	if (pid==0){
		// Ceramos la entrada std
		close(0);
		// El open devuelve el primer canal libre.
		if (open(argv[1],O_RDONLY)!=0) error("open1");
		// Cerramos la salida std
		close(1);
		if (open(argv[2],O_CREAT|O_WRONLY,0666)!=1) error("open2");
		execlp("./cuentaA","cuentaA",(char *)0);
		error("execlp");
	}
	if (pid<0) error("fork");
	waitpid(-1,NULL,0);
}

