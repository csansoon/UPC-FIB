#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define REGION_SIZE		4096

int *p;

void tractar_signal(int s)
{

	char buff[256];
	sprintf( buff, "S'ha generat un segmentation fault\n");
	write(1, buff, strlen(buff));
	exit(0);

}


int main(int argc, char *argv[])
{
	char buff[256];
	struct sigaction sa;
	sigset_t mask;
	sa.sa_handler = &tractar_signal;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	sigaction(SIGSEGV, &sa, NULL);


	sprintf( buff, "Addresses:\n");
	write(1, buff, strlen(buff));
	sprintf( buff, "\tp: %p\n", &p);
	write(1, buff, strlen(buff));

	*p = 5;

	sprintf( buff, "\tp Address: %p, p value: %p, *p: %d\n", &p, p, *p);
	write(1, buff, strlen(buff));

	exit(0);
}
