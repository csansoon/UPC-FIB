
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	printf("Abans fork\n");
	fork();
	printf("Despres fork\n");
}

