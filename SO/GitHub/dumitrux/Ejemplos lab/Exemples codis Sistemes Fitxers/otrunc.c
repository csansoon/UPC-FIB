#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void escribe(char *m)
{
	write(1,m,strlen(m));
}
void main(int argc,char *argv[])
{
	int fd,ret,i;
	char c,men[128];
	fd=open("test",O_WRONLY|O_CREAT,0666);
	if (fd<0) perror("Open test");
	for (i=0;i<1000;i++){ // llenamos el fichero
		write(fd,&i,sizeof(int));
	}
	ret=lseek(fd,0,SEEK_END);
	sprintf(men,"EL tamanyo en bytes del fichero test es %d, compruebalo haciendo ls -l. Y apreta RETURN para continuar\n",ret);
	escribe(men);
	close(fd);
	read(0,&c,sizeof(char)); // Esperamos el RETURN
	escribe("Ahora lo abrimos con O_TRUNC y lo cerramos, comprueba de nuevo el tamayo y luego apreta RETURN (al final borraremos el fichero)\n");
	fd=open("test",O_WRONLY|O_TRUNC);
	if (fd<0) perror("Open test");
	close(fd);
	read(0,&c,sizeof(char)); // Esperamos el RETURN
	unlink("test");
}
