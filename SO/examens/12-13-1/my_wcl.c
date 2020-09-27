#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[]) {
    char c;
    int counter = 0;
    while ( read(0,&c,sizeof(char)) > 0) {
        if (c == '\n') ++counter;
    }
    char buff[128];
    sprintf(buff,"El nimero de lineas es %d\n",counter);
    write(1,buff,strlen(buff));
}