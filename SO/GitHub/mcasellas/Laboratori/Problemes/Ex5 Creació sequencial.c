void muta_grep(char* p, char* f){
  char buf[128];
  sprintf(buf, "Fill amb pid %d, el del pare és %d\n", getpid(), getppid());
  write(1,buf,strlen(buf));
  execlp("grep", "grep", p,f,(char*)0);
}

int main (int argc, char *argv[]) {
  int i, pid, status;
  char buf[128];

  sprintf(buff, "Soc el pare i el meu pid es:" %d\n , getpid());
  write(1,buf,strlen(buf));

  for (int i = 0; i < argc-2; i++) {

      pid = fork();
      switch(pid) {
        case 0:
        muta_grep(argv[i+1],argv[argc-1]);

        case -1:
        // En cas d'error
        exit(0);

        default:
        waitpid(pid,&status,0); //Sequencial, esperem per un PID complet
        sprintf(buf, "Status del fill %d amb pid %d és: %d\n", i, pid, (char)WEXITSTATUS(status));

        write(1,buf,strlen(buf));
        break;
      }
    }


}
