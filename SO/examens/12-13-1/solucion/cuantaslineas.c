#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>


void error_cs(char *msj,int ec)
{
	perror(msj);
	exit(ec);
}

void usage()
{
	char buff[128];
	strcpy(buff,"Uso:my_wcl_v3 fichin fichout\n");
	write(2,buff,strlen(buff));
	exit(1);
}
int main(int argc,char *argv[])
{
	char c[32];
	int ret,i;
	char buff[128];
	int pid,p[2];

	if (argc!=3) usage();

	pipe(p);
	pid=fork();
	if (pid==0){
		dup2(p[1],1);
		close(p[0]);close(p[1]);
		execlp("grep","grep",argv[1],argv[2],(char *)NULL);
		error_cs("execlp grep ",1);
	}else if (pid<0) error_cs("fork grep ",2);
	close(p[1]);
	pid=fork();
	if (pid==0){
		dup2(p[0],0);
		close(p[0]);
		execlp("wc","wc","-l",(char *)NULL);
		error_cs("execlp wc ",1);
	}else if (pid<0) error_cs("fork wc -l ",4);
	close(p[0]);
	while(waitpid(-1,NULL,0)>0);
}
