#include <unistd.h>
#include <stdio.h>

main () {
fork();
fprintf (stdout, "Mi pid es: %d\n", getpid());

}


