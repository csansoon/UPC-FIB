#include <stdio.h>
#include <signal.h>
#include <string.h>

void f_alarma(); // Implementada mas abajo...

void main()
{
    long i;
    char buf[80];
    struct sigaction trat;
    sigset_t mask;

    // Programo la rutina de atención alsignal (f_alarma)indicando que 
    // no quiero bloquear ningun signal durante el tratamiento (mask=emptyset)

    trat.sa_handler = f_alarma;
    trat.sa_flags = 0;
    sigemptyset(&mask);
    trat.sa_mask = mask;

    sigaction(SIGALRM, &trat, NULL);

    // Y programo una alarma para dentro de 1 segundo
    alarm(1);

    // Ahora se supone que el proceso se dedica a hacer
    // cualquier tarea que no tiene nada que ver con el tiempo.
    // Por ejemplo, aqui hay un bucle infinito que escribe por
    // pantalla.
    while(1) {
	// Le ponemos un retardo, para que de tiempo
	// para ver visualmente los mensajes
	for( i = 0; i < 20000000; i++);
	sprintf(buf, "Estoy haciendo cierta tarea...\n");
	write(1,buf,strlen(buf));
    }

    // Para acabar la ejecución, pulsa ^C
}

void f_alarma()
{
    // Escribo mensaje de tiempo
    // y reprogramo la alarma de reloj
    printf("\n**************\n");
    printf("*** TIEMPO ***\n");
    printf("**************\n\n");
    alarm(1);
}
