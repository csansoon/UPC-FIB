#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

main () {

fork();
fork();
fprintf (stdout, "Mi pid es: %d\n", getpid());

}


