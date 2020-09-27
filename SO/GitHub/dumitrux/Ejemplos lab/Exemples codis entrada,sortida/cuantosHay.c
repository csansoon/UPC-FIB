#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Este programa hace ls argv[1] | grep argv[2] | wc -l
void error(char *s)
{
	perror(s);
	exit(0);
}
void usage()
{
	char men[128];
	sprintf(men,"usage: cuantosHay directorio palabra_clave\n");
	write(1,men,strlen(men));
	exit(0);
}
void main(int argc,char *argv[])
{
	int pid_ls,pid_grep,pid_wc;
	int ls_grep[2],grep_wc[2];
	if (argc!=3) usage();
	if (pipe(ls_grep)<0) error("pipe ls_grep");
	// LS
	pid_ls=fork();
	if (pid_ls==0){ //LS
		if (dup2(ls_grep[1],1)!=1) error("dup2 ls grep");
		close(ls_grep[0]);close(ls_grep[1]);
		execlp("ls","ls",argv[1],(char *)0);
		error("execlp=ls");
	}else if (pid_ls<0) error("fork ls");
	// CREAMOS PIPE grep_wc
	if (pipe(grep_wc)<0) error("pipe grep_wc");
	// GREP
	pid_grep=fork();
	if (pid_grep <0) error("fork grep");
	if (pid_grep==0){ // GREP
		// Hay que redireccionar la entrada y la salida std
		if (dup2(ls_grep[0],0)!=0) error("Redireccion entrada std grep");
		if (dup2(grep_wc[1],1)!=1) error("Redireccion salida std grep");
		close(ls_grep[0]);close(ls_grep[1]);
		close(grep_wc[0]);close(grep_wc[1]);
		execlp("grep","grep",argv[2],(char *)0);
		error("execlp=grep");
	}
	// CERRAMOS PIPE ls_grep
	close(ls_grep[0]);close(ls_grep[1]);
	// FORK WC
	pid_wc=fork();
	if (pid_wc<0) error("fork wc");
	if (pid_wc==0){
		// Hay que redireccinar la entrada del wc
		if (dup2(grep_wc[0],0)!=0) error("Redireccion entrada std wc");
		close(grep_wc[0]);close(grep_wc[1]);
		execlp("wc","wc","-l",(char *)0);
		error("execlp=wc");
	}
	// CERRAMOS TODO LO QUE QUEDE
	close(grep_wc[0]);close(grep_wc[1]);
	// Esperamos que terminen los procesos
	while(waitpid(-1,NULL,0)>0);
}

