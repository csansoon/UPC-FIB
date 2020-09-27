#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void Usage() {
    printf("This program needs at least one input parameter\n#./prog1 filename1 [filename2 .. filenameN]\n");
}


int main(int argc, char **argv) {
    //Usage function:
    if (argc == 1) Usage();

    //setup
    int p[2];
    pipe(p);
    char buf[512];


    for (int i = 1; i < argc; ++i) {
        int pid = fork();
        if (pid == -1) {
            perror("Error en el fork");
            return -1;
        }
        if (pid == 0) {
            //CHILDREN FUNCTION:
            close(p[0]);    //Cerrar el canal INPUT de la pipe.
            dup2(p[1],1);   //Duplicar el canal OUTPUT de la pipe en mi canal de salida por defecto (1).
            close(p[1]);    //Cerrar el canal OUTPUT de la pipe.

            execlp("cat","cat",argv[i],NULL);   //Ejecutar #cat argv[i]

            perror("Error en el execlp");   //Error
            return -1;
        }
    }

    int pid = fork();
    if (pid == -1) {
        perror("Error en el fork");
        return -1;
    }
    if (pid == 0) {
        /* El programa 'micat' leerá por el canal 20 y escribirá por el canal 30,
        así que hay que redireccionar el canal INPUT de la pipe al canal 20, y
        el canal OUTPUT de la nueva pipe con nombre al canal 30.                */

        dup2(p[0],20);
        close(p[0]);close(p[1]);

        if (mknod("MYPIPE",S_IFIFO|0644,0) == -1) {
            if (errno != EEXIST) { //Si el error se produce porque el archivo ya existe, lo ignoramos.
                perror("Error en el mknod");
                return -1;
            }
        }

        int npd = open("MYPIPE", O_WRONLY);
        if (npd == -1) {
            perror("Error en el open MYPIPE");
            return -1;
        }

        dup2(npd,30);
        close(npd);

        execlp("./micat","./micat",NULL);
    }


    //FATHER:
    close(p[0]);
    while ( waitpid(-1,NULL,0) > 0 ) {}
    int len = sprintf(buf, "The execution is over\n");
    write(1, buf, len);
    return 0;
}