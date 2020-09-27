#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

main ()
{

     execlp ("ls", "kamikace","-l", (char *) 0);
     /* execlp ("./ls", "ls","-l", (char *) 0);*/  /* descomentar para forzar un exec con error */
     perror ("Error executing execlp");
     fprintf(stdout, "Despues del exec\n");

    

}
