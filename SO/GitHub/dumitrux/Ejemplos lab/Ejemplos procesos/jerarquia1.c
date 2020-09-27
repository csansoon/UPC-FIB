#include <unistd.h>
#include <stdio.h>
#include <stdio.h>

main() {
int i,ret;

i=0;
ret =fork();
if (ret == 0) {
	fprintf(stdout, "Soy %d y mi padre es %d\n", getpid(), getppid());
}
i++;
while ((i<3) && (ret > 0)) {
	ret=fork();
	if (ret == 0) {
		fprintf(stdout, "Soy %d y mi padre es %d\n", getpid(), getppid());
	}
	i++;
}
//while(waitpid(-1,NULL,0)>0);
}
