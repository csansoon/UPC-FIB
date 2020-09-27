#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>

#define MAX 10000

#define NTHREADS 10

int globalvector[MAX];
int globalPos=0;

struct infojob {
	int ini;	/* posición inicial */
	int fin;	/* posición final */
	int res;	/* resultado parcial */
};

struct infojob Tareas[NTHREADS];
static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void * SumaParcial(void *p)
{
	int i;
	int myPos;

	pthread_mutex_lock(&m);
	myPos=globalPos;
	globalPos++;
	pthread_mutex_unlock(&m);

	struct infojob *mi_tarea=&Tareas[myPos];
	mi_tarea->res=0;
	/* sum global vector */
	for (i=mi_tarea->ini; i< mi_tarea->fin; i++) {
		mi_tarea->res += globalvector[i];
	}	
	pthread_exit(NULL);
}
int min(int a,int b)
{
	if (a<b) return a;
	return b;
}
void main()
{
	int i;
	int suma=0;
	char buf[100];
	pthread_t ths[NTHREADS];
	int cur_th,ret,tamanyo_trozo;

	/* init global vector */
	for (i=0; i< MAX; i++) {
		globalvector[i] = i;
	}
	tamanyo_trozo=MAX/NTHREADS;
	for (cur_th=0;cur_th<NTHREADS;cur_th++){
		Tareas[cur_th].ini=cur_th*tamanyo_trozo;
		Tareas[cur_th].fin=min(Tareas[cur_th].ini+tamanyo_trozo,MAX);
		Tareas[cur_th].res=0;
	}
	pthread_mutex_init(&m,NULL);
	for (cur_th=0;cur_th<NTHREADS;cur_th++){
		ret=pthread_create(&ths[cur_th],NULL,SumaParcial,NULL);
	}
	for (cur_th=0;cur_th<NTHREADS;cur_th++){
		pthread_join(ths[cur_th],NULL);
		suma+=Tareas[cur_th].res;
	}

	sprintf (buf, "El resultado de la suma es %d\n", suma);
	write (1, buf, strlen(buf));
}
