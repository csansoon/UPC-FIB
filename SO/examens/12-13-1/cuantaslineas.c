#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


void Usage() {
    char buff[128];
    sprintf(buff,"Usage:\n#./cuantaslineas PALABRA FICHERO\n");
    write(1,buff,strlen(buff));
    exit(-1);
}

void error(char *msg) {
    perror(msg);
    exit(-1);
}

int main(int argc,char *argv[]) {

    if (argc != 3) Usage();
    int p[2];
    if (pipe(p) == -1) error("Error con la pipe");

    int pid = fork();
    if (pid == -1) error("Error con el fork");
    if (pid == 0) {
        dup2(p[1],1);
        close(p[0]);close(p[1]);
        execlp("grep","grep",argv[1],argv[2],(char *)NULL);
        error("Error ejecutando grep");
    }
    close(p[1]);
    pid = fork();
    if (pid == -1) error("Error con el fork");
    if (pid == 0) {
        dup2(p[0],0);
        close(p[0]);close(p[1]);
        execlp("wc","wc","-l",(char *)NULL);
        error("Error ejecutando wc -l");
    }
    close(p[0]);
    while( waitpid(-1,NULL,0) > 0 );
}