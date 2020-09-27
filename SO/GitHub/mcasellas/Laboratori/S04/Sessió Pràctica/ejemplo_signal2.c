#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

int hijos=0;



void error_y_exit(char *msg,int exit_status)
{
    perror(msg);
    exit(exit_status);
}

void trata_alarma(int s) 
{
     char buff[256];
    
    if (s == SIGCHLD) {
    
       int pid=waitpid(-1,NULL,WNOHANG);
    sprintf(buff,"Termina el proceso %d\n",pid);

        hijos --;
          write(1, buff, strlen(buff));
    }
      
}

int main(int argc,char *argv[])
{
    int pid,res;
    char buff[256];		
    int contador = 0;
    struct sigaction sa;
    sigset_t mask;

    /* Evitamos recibir el SIGALRM fuera del sigsuspend */

    sigemptyset(&mask);
    sigaddset(&mask,SIGALRM);

    sigprocmask(SIG_BLOCK,&mask, NULL);

    for (hijos=0;hijos<10;hijos++)
    {
	sprintf(buff, "Creando el hijo numero %d\n", hijos);
	write(1, buff, strlen(buff)); 
		  sa.sa_handler = &trata_alarma;
            sa.sa_flags = SA_RESTART;
            sigfillset(&sa.sa_mask);
        if (sigaction(SIGCHLD, &sa, NULL) < 0) error_y_exit("sigaction", 1);


	pid=fork();
	if (pid==0) /* Esta linea la ejecutan tanto el padre como el hijo */
	{

    	    sa.sa_handler = &trata_alarma;
    	    sa.sa_flags = SA_RESTART;
    	    sigfillset(&sa.sa_mask);
	    if (sigaction(SIGALRM, &sa, NULL) < 0) error_y_exit("sigaction", 1);
        if (sigaction(SIGCHLD, &sa, NULL) < 0) error_y_exit("sigaction", 1);

	    /* Escribe aqui el codigo del proceso hijo */
  	    sprintf(buff,"Hola, soy %d\n",getpid());
	    write(1, buff, strlen(buff)); 

	    alarm(3); 
	    sigfillset(&mask);
            sigdelset(&mask, SIGALRM);
            sigdelset(&mask, SIGCHLD);
            sigdelset(&mask, SIGINT);
            sigsuspend(&mask);

	    /* Termina su ejecución */
	    exit(0);
	} else if (pid<0)	
	{
	    /* Se ha producido un error */
  	    error_y_exit("Error en el fork", 1);
	}
    }
    /* Esperamos que acaben los hijos */
    while (hijos > 0)
    {
	

	contador++;
    }
    sprintf(buff,"Valor del contador %d\n", contador);
    write(1, buff, strlen(buff)); 
    return 0;
}
