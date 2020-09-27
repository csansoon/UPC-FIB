#include <unistd.h>
#include <stdio.h>

main () {

int id1, ret;
	
	id1=getpid();
	
	ret= fork();

	id1 =getpid();

	fprintf (stdout, "Valor de id1: %d; valor de ret: %d; valor de id1: %d\n", id1, ret, id1);

}


