#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void
HacerTarea ()
{
  printf ("Mi PID es %d y el de mi padre %d\n", getpid (), getppid ());
}

void
main (int argc, char *argv[])
{
  int i;
  int pid;
  printf ("Mi PID es %d\n", getpid ());
  for (i = 0; i < 3; i++)
    {
      pid = fork ();
      if (pid == 0)
	HacerTarea ();
    }
  while (1);
}
