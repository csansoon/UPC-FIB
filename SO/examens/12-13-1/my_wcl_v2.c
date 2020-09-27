#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[]) {
    char c[32];
    int counter = 0;
    int ret;
    while ((ret = read(0,&c,sizeof(c))) > 0) {
        for (int i = 0; i < ret; ++i) if (c[i] == '\n') ++counter;
    }
    char buff[128];
    sprintf(buff,"El numero de lineas es %d\n",counter);
    write(1,buff,strlen(buff));
}