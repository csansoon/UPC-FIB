
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char *m1= "abans fork\n";
	char *m2= "despres fork\n";

	write(1, m1, strlen(m1));
	fork();
	write(1, m2, strlen(m2));
}

