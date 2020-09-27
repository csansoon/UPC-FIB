
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	printf("Abans fork ");
	fork();
	printf("Despres fork");
}

