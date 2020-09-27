#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10000

#define NTHREADS 10

int globalvector[MAX];

struct infojob {
	int ini;	/* posición inicial */
	int fin;	/* posición final */
	int res;	/* resultado parcial */
};

struct infojob Tareas[NTHREADS];

void SumaParcial(struct infojob *mi_tarea)
{
	int i;
	mi_tarea->res=0;
	/* sum global vector */
	for (i=mi_tarea->ini; i< mi_tarea->fin; i++) {
		mi_tarea->res += globalvector[i];
	}	
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
		SumaParcial(&Tareas[cur_th]);
	}
	for (cur_th=0;cur_th<NTHREADS;cur_th++){
		suma+=Tareas[cur_th].res;
	}

	sprintf (buf, "El resultado de la suma es %d\n", suma);
	write (1, buf, strlen(buf));
}
