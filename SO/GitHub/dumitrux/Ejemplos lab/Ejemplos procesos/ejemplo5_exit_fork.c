#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void hacerTarea()
{
    fprintf(stdout,"Mi PID es %d y el de mi padre %d\n", getpid(), getppid());
    exit(0);
}

void main()
{
int i,pid;

    fprintf(stdout,"Mi PID es el %d\n", getpid());
    for (i = 0; i < 3; i++) {
	pid = fork();
	if (pid == 0)
	    hacerTarea();
    }

    fprintf(stdout, "Entrando en bucle infinito... \n");
    while (1);
}


