#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

void Usage() {
    char buff[128];
    sprintf(buff,"my_wcl_v3 necesita dos parámetros de entrada.\n#./my_wcl_v3 FICHERO_ENTRADA FICHERO_SALIDA\n");
    write(1,buff,strlen(buff));
    exit(-1);
}

int main(int argc,char *argv[]) {
    if (argc != 3) Usage();
    char buff[128];

    int filein = open(argv[1],O_RDONLY);
    if (filein == -1) {
        sprintf(buff,"Error abriendo %s",argv[1]);
        perror(buff);
        return -1;
    }
    int fileout = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
    if (filein == -1) {
        sprintf(buff,"Error abriendo %s",argv[2]);
        perror(buff);
        return -1;
    }

    char c[32];
    int counter = 0;
    int ret;
    while ((ret = read(filein,&c,sizeof(c))) > 0) {
        for (int i = 0; i < ret; ++i) if (c[i] == '\n') ++counter;
    }
    sprintf(buff,"El numero de lineas es %d\n",counter);
    write(fileout,buff,strlen(buff));
}