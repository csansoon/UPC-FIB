#include <unistd.h>
int main(int argc,char *argv[])
{
	int i;
	for (i=0;i<1000;i++) write(1,&i,sizeof(int));
}
