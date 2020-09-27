#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int alarma=0;

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

void f_alarma (int s) { }

void fin_hijo (int s) {
	while (waitpid(-1,NULL,WNOHANG)>0);
}

void configurar_esperar_alarma() {
   sigset_t mask;
   sigemptyset(&mask);
   sigaddset(&mask, SIGALRM); 
   sigprocmask(SIG_BLOCK,&mask, NULL);    
}


void main (int argc, char *argv[]) {
  struct sigaction trat;
  sigset_t mask;
  int x;

  configurar_esperar_alarma();
  trat.sa_handler =f_alarma;
  trat.sa_flags = 0;
  sigemptyset(&mask);
  trat.sa_mask = mask;
  sigaction (SIGALRM, &trat, NULL);
  trat.sa_handler =fin_hijo;
  sigaction (SIGCHLD, &trat, NULL);

  sigfillset(&mask);
  sigdelset(&mask, SIGALRM);
  x = 0;
  while (x <10) {
      alarm (2);
      sigsuspend(&mask);
      crea_ps ();
      x++;
    }
}
