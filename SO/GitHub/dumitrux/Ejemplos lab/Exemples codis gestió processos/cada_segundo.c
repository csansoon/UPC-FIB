#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void error (char *msg) {
  perror (msg);
  exit (0);
}

void crea_ps () {
  int pid;
  pid = fork ();
  if (pid == 0) {
      execlp ("ps", "ps", (char *) 0);
      error ("execlp");
    }
  else if (pid < 0) error ("fork");
}

void f_alarma (int s) {}

void main (int argc, char *argv[]) {
  int x;
  struct sigaction trat;
  sigset_t mask;

  trat.sa_handler = f_alarma;
  trat.sa_flags = 0;
  sigemptyset(&mask);
  trat.sa_mask = mask;
  sigaction (SIGALRM, &trat, NULL);

  sigaddset(&mask,SIGALRM);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  sigfillset(&mask);
  sigdelset(&mask,SIGALRM);

  x = 0;
  while (x < 100) {
      alarm (2);
      sigsuspend(&mask);
      crea_ps ();
      x++;
	}
}
