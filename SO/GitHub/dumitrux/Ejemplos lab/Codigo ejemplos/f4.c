
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	fprintf(stderr, "Abans fork ");
	fork();
	fprintf(stderr, "Despres fork ");
}

