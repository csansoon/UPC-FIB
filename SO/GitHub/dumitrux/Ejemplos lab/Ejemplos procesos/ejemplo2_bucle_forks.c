#include <unistd.h>
#include <stdio.h>

main () {

int i;

for (i=0; i<2; i++){
	fork();
}
fprintf (stdout, "Mi pid es: %d\n", getpid());

}


