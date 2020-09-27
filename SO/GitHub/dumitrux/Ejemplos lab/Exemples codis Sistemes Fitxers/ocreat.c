#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
void escribe(char *m)
{
	write(1,m,strlen(m));
}
void main(int argc,char *argv[])
{
	int fd,ret;
	char c;
	fd=open("test",O_WRONLY);
	if (fd<0) perror("Sin O_CREAT no funciona");
	fd=open("test",O_WRONLY|O_CREAT);
	if (fd<0) perror("Con O_CREAT tampoco");
	else escribe("Con O_CREAT si se crea correctamente\n");
	close(fd);
	escribe("Hemos creado un fichero test, ahora ahora hacemos ls, comprueba las protecciones\n");
	escribe("Apreta RETURN para continuar\n");
	ret=read(0,&c,sizeof(c));
	system("ls -l");
	unlink("test"); // Elimina el fichero
	escribe("Volvemos a crearlo pero con los permisos correctos y repetimos\n");
	escribe("Apreta RETURN para continuar\n");
	ret=read(0,&c,sizeof(c));
	fd=open("test",O_WRONLY|O_CREAT,0600);
	if (fd<0) perror("Open con permisos");
	close(fd);
	escribe("Hemos creado un fichero test, ahora ahora hacemos ls, comprueba las protecciones\n");
	escribe("Apreta RETURN para continuar\n");
	ret=read(0,&c,sizeof(c));
	system("ls -l");
	unlink("test");
}
