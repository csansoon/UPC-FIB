#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
    char buff[256];
    int num;
    read(0, &num, sizeof(int));
    sprintf(buff,"%d\n",num);
    write(1,buff,strlen(buff));
}
