#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
// Este programa cuenta cuantas A's recibe por la entrada estandard y escribe 
// el resultado por la salida std
void main(int argc,char *argv[])
{
	int fd,pid,n,numA=0;
	char str[128],car;
	while ( ( n = read(0, &car, 1) ) > 0 )
		if ( car == 'A' ) numA++;
	sprintf(str, "El numero de As es %d\n", numA);
	write(1, str, strlen(str));
}

