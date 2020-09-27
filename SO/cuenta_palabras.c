#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void Usage() {
	char buff[128];
	sprintf(buff, "Usage: ./cuenta_palabras arg\n");
	write(1, buff, strlen(buff));
	exit (1);
}

void error_y_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void main(int argc, char *argv[]){
	if(argc != 2) Usage();
	int fd[2];
	int i = pipe(fd), ret;
	if(i < 0)error_y_exit("Error en pipe");
	int pid = fork();
	if(pid < 0) error_y_exit("Error en fork");
	if(pid == 0){
		char *s = argv[1];
		ret = close(1);
		if(ret < 0)error_y_exit("Error en close");
		ret = close(fd[0]);
		if(ret < 0)error_y_exit("Error en close");
		ret = dup2(fd[1],1);
		if(ret < 0)error_y_exit("Error en dup2");
		execlp("/home/ferran/Desktop/SO/Exams/Lab/CLAB2_1718_Q1/iniciales_v2","iniciales_v2", s,(char *)NULL);
		error_y_exit("Error en execlp2");
	}
	ret = close(0);
	if(ret < 0)error_y_exit("Error en close");
	ret = close(fd[1]);
	if(ret < 0)error_y_exit("Error en close");	
	ret = dup2(fd[0],0);
	if(ret < 0)error_y_exit("Error en dup2");
	ret = close(fd[0]);
	if(ret < 0)error_y_exit("Error en close");
	waitpid(pid,&ret,0);
	execlp("wc","wc", "-c",(char *)NULL);
	error_y_exit("Error en execlp");
}
	
