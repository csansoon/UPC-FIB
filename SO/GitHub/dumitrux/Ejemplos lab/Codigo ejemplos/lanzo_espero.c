#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int terminados=0;
void misigchld(int s)
{
	int es;
	int pid;
	while((pid=waitpid(-1,&es,WNOHANG))>0){
		//trataexitcode
		printf("Termina proceso PID %d\n",pid);
		terminados++;
	}
}
int sigint_recibido=0;
void misigint(int s)
{
	sigint_recibido=1;
}
int main(int argc,char *argv[])
{
	char m[128];
	sigset_t mascara;
	int hijos=0;
	char tiempo[64];

	// Bloqueo SIGINT
	sigemptyset(&mascara);sigaddset(&mascara,SIGINT);
	sigprocmask(SIG_BLOCK,&mascara,NULL);

	// Capturo SIGINT
	struct sigaction sa;
	sa.sa_handler=misigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=SA_RESTART;
	sigaction(SIGINT,&sa,NULL);
        // Capturo SIGCHLD
        sa.sa_handler=misigchld;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags=SA_RESTART;
        sigaction(SIGCHLD,&sa,NULL);



	sigfillset(&mascara);
	sigdelset(&mascara,SIGINT);
	sigdelset(&mascara,SIGCHLD);
	while ((hijos<5) || (terminados<5)){
		sigsuspend(&mascara);
		if (sigint_recibido && (hijos<5)){
			sigint_recibido=0;
			hijos++;
			if (fork()==0){
				sprintf(tiempo,"%d",hijos);
				execlp("./espero","espero",tiempo,NULL);
				perror("Error mutar");
				exit(1);
			}
		}
	}
}	
		
