#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


void error_cs(char *msj,int ec)
{
	perror(msj);
	exit(ec);
}
int main(int argc,char *argv[])
{
	char buff[128];
	// $ps -A -com | wc -l
	int pid,p[2];
	if (pipe(p)<0) error_cs("creating unnamed pipe ",1);
	if ((pid=fork())==0){
		dup2(p[1],1);
		close(p[0]);close(p[1]);
		execlp("ps","ps","-A","r",(char *)NULL);
		error_cs("mutacion ps ",1);
	}else if (pid<0) error_cs("fork primer hijo ",1);
	if ((pid=fork())==0){
		dup2(p[0],0);
		close(p[0]);close(p[1]);
		execlp("wc","wc","-l",(char *)NULL);
		error_cs("mutacion wc -l ",1);
	}else if (pid<0) error_cs("fork segundo hijo ",1);
	close(p[0]);close(p[1]);
	while(waitpid(-1,NULL,0)>0);
}
