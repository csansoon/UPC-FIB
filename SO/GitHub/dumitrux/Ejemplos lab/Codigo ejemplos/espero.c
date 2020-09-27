#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int t;
void mialarma(int s)
{
	exit(t%2);
}
void usage()
{
	char m[128];
	sprintf(m,"usage espero num\n");
	write(1,m,strlen(m));
	exit(0);
}
int main(int argc,char *argv[])
{
	char m[128];
	sigset_t mascara;

	if (argc==1) usage();
	// Bloqueo SIGALRM
	sigemptyset(&mascara);sigaddset(&mascara,SIGALRM);
	sigprocmask(SIG_BLOCK,&mascara,NULL);

	// Capturo SIGALARM
	struct sigaction sa;
	sa.sa_handler=mialarma;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=SA_RESTART;
	sigaction(SIGALRM,&sa,NULL);

	sprintf(m,"Recibo %s\n",argv[1]);
	write(1,m,strlen(m));

	t=atoi(argv[1]);
	alarm(2+t%2);
	// Espero a la alarma	
	sigfillset(&mascara);
	sigdelset(&mascara,SIGALRM);
	sigsuspend(&mascara);
}	
		
