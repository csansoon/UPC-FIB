#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void hago_algo_de_trabajo()
{

}

int sigchld_recibido = 0;

int pid_h;

void
trat_sigalrm (int signum)
{

  char buff[128];

  if (!sigchld_recibido)
    kill (pid_h, SIGKILL);

  strcpy (buff, "Timeout ! ");

  write (1, buff, strlen (buff));

  exit (1);

}

void
trat_sigchld (int signum)
{

  sigchld_recibido = 1;

}

void
main (int argc, char *argv[])
{

  int ret, n;

  int nhijos = 0;

  char buff[128];

  struct sigaction trat;

  trat.sa_flags = 0;

  sigemptyset (&trat.sa_mask);

  trat.sa_handler = trat_sigchld;

  sigaction (SIGCHLD, &trat, NULL);


  n = atoi (argv[1]);

  if (n > 0)
    {

      pid_h = fork ();

      if (pid_h == 0)
	{

	  n--;

	  trat.sa_flags = 0;

	  sigemptyset (&trat.sa_mask);

	  trat.sa_handler = trat_sigalrm;

	  sigaction (SIGALRM, &trat, NULL);

	  sprintf (buff, "%d", n);

	  execlp ("./ejercicio_exec", "ejercicio_exec", buff, (char *) 0);

	}

      strcpy (buff, "Voy a trabajar \n");
      write (1, buff, strlen (buff));

      alarm (10);

      hago_algo_de_trabajo ();	/*no ejecuta nada relevante para el problema */

      alarm (0);

      while ((ret = waitpid (-1, NULL, 0)) > 0)
	{

	  nhijos++;

	}

      sprintf (buff, "Fin de ejecución. Hijos esperados: %d \n", nhijos);

      write (1, buff, strlen (buff));

    }
  else
    {

      strcpy (buff, "Voy a trabajar \n");

      write (1, buff, strlen (buff));

      alarm (10);

      hago_algo_de_trabajo ();	/*no ejecuta nada relevante para el problema */

      alarm (0);

      strcpy (buff, "Fin de ejecucion");

      write (1, buff, strlen (buff));

    }

}
