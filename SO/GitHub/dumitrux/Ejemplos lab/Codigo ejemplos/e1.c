
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	printf("Abans fork ");
	execl("/bin/ls", "ls", NULL);
}

