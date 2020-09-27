#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define REGION_SIZE		4096

int *p;

void ras_sigsegv(int signo, siginfo_t *data, void *foo)
{
	fprintf(stderr, "Faulting address: %p\n", data->si_addr);
	exit(0);
}

int main(int argc, char *argv[])
{
	int i = 0;
	char buff[256];					

	struct sigaction sigsegv;

	sigsegv.sa_sigaction= ras_sigsegv;
	sigsegv.sa_flags = SA_SIGINFO;
	sigemptyset(&sigsegv.sa_mask);
	sigaction(SIGSEGV, &sigsegv, NULL);

	sprintf( buff, "Addresses:\n");
	write(1, buff, strlen(buff));	
	sprintf( buff, "\tp: %p\n", &p);
	write(1, buff, strlen(buff));	

	p = malloc(sizeof(int));
	
	if (p == NULL) {
		sprintf(buff, "ERROR en el malloc\n");
		write(2,buff,strlen(buff));
	}

	while (1) {
		*p = i;
		sprintf( buff, "\tProgram code -- p address: %p, p value: %p, *p: %d\n",
		      &p, p, *p);
		write(1, buff, strlen(buff));	
		p++;
		i++;
	}

}
