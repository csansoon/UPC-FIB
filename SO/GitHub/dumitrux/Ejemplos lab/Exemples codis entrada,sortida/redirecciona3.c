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
		if ((fd=open(argv[1],O_RDONLY))<0) error("open1");
		close(0);
                // Opcion 3: usamos dup para redireccionar la entrada y la 
                // salida std
		if (dup(fd)!=0) error("dup");
		close(fd);
		if ((fd=open(argv[2],O_CREAT|O_WRONLY,0666))<0) error("open2");
		close(1);
		if (dup(fd)!=1) error("dup-2");
		close(fd);
		execlp("./cuentaA","cuentaA",(char *)0);
		error("execlp");
	}
	if (pid<0) error("fork");
	waitpid(-1,NULL,0);
}

