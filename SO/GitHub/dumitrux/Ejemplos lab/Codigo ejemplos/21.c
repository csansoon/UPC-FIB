#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char *signame[]={"INVALID", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGPOLL", "SIGPWR", "SIGSYS", NULL};

void dump(char *str)
{
  sigset_t current;
  int i;

  sigprocmask(SIG_SETMASK, NULL, &current);

  fprintf(stderr, "** %s: ", str);
//  for (i=1; i<_NSIG; i++) {
  for (i=1; i<32; i++) {
    if (sigismember(&current, i))
 	fprintf(stderr, "%d(%s) ", i, signame[i]);
  }
  fprintf(stderr, "\n");
}

void sigusr1 (int signum)
{
  sigset_t mascara;

/* C */ dump("C");

  sigemptyset (&mascara);

  sigaddset (&mascara, SIGINT);
  sigaddset (&mascara, SIGUSR1);

  sigprocmask (SIG_BLOCK, &mascara, NULL);

/* D*/ dump("D");

}

void
sigusr2 (int signum)
{
/* B */ dump("B");

  kill (getpid (), SIGUSR1);

}

void
sigalrm (int signum)
{
/* H*/ dump("H");

}

int main ()
{
  sigset_t mascara;

  struct sigaction new;


  new.sa_handler = sigusr1;
  new.sa_flags = 0;

  sigemptyset (&new.sa_mask);
  sigaddset (&new.sa_mask, SIGALRM);

  sigaction (SIGUSR1, &new, NULL);


  new.sa_handler = sigalrm;
  sigemptyset (&new.sa_mask);

  sigaction (SIGALRM, &new, NULL);


  new.sa_handler = sigusr2;

  sigemptyset (&new.sa_mask);
  sigaddset (&new.sa_mask, SIGPIPE);

  sigaction (SIGUSR2, &new, NULL);


/* A */ dump("A");

  kill (getpid (), SIGUSR2);

/* E */ dump("E");

  sigemptyset (&mascara);
  sigaddset (&mascara, SIGALRM);

  sigprocmask (SIG_BLOCK, &mascara, NULL);

/* F */ dump("F");

  sigfillset (&mascara);
  sigdelset (&mascara, SIGALRM);

  alarm (2);

/* G */ dump("G");

  sigsuspend (&mascara);

/* I */ dump("I");

}
