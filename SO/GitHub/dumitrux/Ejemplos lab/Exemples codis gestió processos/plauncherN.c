#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MIN_PARS 3

// Funcion que escribe como se ejecuta el programa
void Usage()
{
	printf("Usage: plauncherN N cmd [cmd]\n");
	exit(1);
}
// Funcion que procesa el exit code
void EscribeExitCode(int pid, int code)
{
	int ret;
	if (WIFEXITED(code)){
		ret=WEXITSTATUS(code);
		printf("El proceso %d termina con exit code %d\n",pid,ret);
	}else{
		ret=WTERMSIG(code);	
		printf("El proceso %d termina por el signal %d\n",pid,ret);
	}
}
void LanzaComando(char *cmd)
{
	int pid;
	pid=fork();
	if (pid==0){
		// Cambiamos al ejecutable que nos piden
		// Es MUY importante controlar este error o todo el 
		// codigo se descontrolaria
		if (execlp(cmd,cmd,(char *)0)<0){
			perror("Exec FAILS\n");
			exit(100);
		}
	}else if (pid<0){
		// Este codigo lo ejecuta el padre, pq el fork ha fallado
		perror("FORK FALLA\n");
		exit(1);
	}
}
// FUncion que devuelve el minimo de los dos 
int min(int a , int b)
{
	if (a>b) return b;
	else return a;
}
// Funcion principal
int main(int argc,char *argv[])
{
	int pid, exit_code,i,num_cmd,max_procs, creados;
	// Minimo 1 comando a ejecutar
	if (argc<MIN_PARS) Usage();
	// Tenemos (argc-2) comandos que ejecutar
	num_cmd=argc-2;
	// En argv[1] tenemos el grado de concurrencia 
	max_procs=atoi(argv[1]);
	// Creamos tantos hijos como comandos hay que ejecutar
	creados=min(max_procs,num_cmd);
	for (i=0;i<creados;i++){
		// Como hemos contado a partir del 0, los comandos 
		// estan en i+2
		LanzaComando(argv[i+2]);
	}
	// En este punto ya hemos creado todos los procesos, ahora a esperar que
	// acaben. Si hay comandos pendientes, los vamos creando
	while ((pid=waitpid(-1,&exit_code,0))>0){
		EscribeExitCode(pid,exit_code);
		// Como ha terminado un proceso, si aun faltan comandos 
		// puedo crear otro
		if (creados<num_cmd){
			LanzaComando(argv[creados+2]);
			creados++;
		}
	}
	exit(0);
}
