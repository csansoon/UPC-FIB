#include <stdlib.h>
#include <unistd.h>

main() {
int ret;

ret = fork();

if (ret == 0) {
	execlp("ls", "ls","-l", (char *) NULL);
	perror("Error ejecutando ls");
}
waitpid(-1, NULL, 0);
}
