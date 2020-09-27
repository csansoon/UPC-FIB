#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

//The program accepts 1..N input filenames.
//The parent process creates concurrent child processes
//1..N child processes execute "cat" to read i-th file and write to the unnamed pipe
//the "N+1" child mutate to execute "micat" to read from the unnamed pipe and write to the named pipe
void Usage(char *param){
                int len;
                char buf[256];
                
                len = sprintf(buf, "%s needs at least one input parameter\n%s filename1 [filename2...filenameN]\n", param, param);
                write(1, buf, len);
}


int main(int argc, char **argv){
        int pd[2], i, npd, len, pid;
        char buf[512];
        
        if (argc == 1){
                Usage(argv[0]);
                return -1;
        }
        
        pipe(pd);
        for(i=1; i<argc; i++){
                pid = fork();
                switch(pid){
                        case -1: //error
                                perror("Error at fork");
                                return -1;
                        case 0://child i-th to mutate to "cat"
                                //write to the pipe
                                close(pd[0]);
                                dup2(pd[1], 1); close(pd[1]);
                                execlp("cat", "cat", argv[i], NULL);
                                perror("Error at execlp cat");
                                return -1;
                }
        }
        
        close(pd[1]);
        
        pid = fork();
        switch(pid){
                case -1: //error
                        perror("Error at fork");
                        return -1;
                case 0://child to mutate to "micat"
                        dup2(pd[0], 20); close(pd[0]);close(pd[1]);
                        if ((mknod("MYPIPE", S_IFIFO|0644,0)<0) && (errno != EEXIST)){
                                perror("Error at mknod");
                                return -1;
                        }
                        if ((npd = open("MYPIPE", O_WRONLY))<0){
                                perror("Error at open MYPIPE");
                                return -1;
                        }
                        dup2(npd, 30); close(npd);
                        execlp("./micat", "./micat", NULL);
                        perror("Error at execlp micat");
                        return -1;
        }
        
        close(pd[0]);
        while(waitpid(-1, NULL, 0) > 0);
        len = sprintf(buf, "The execution is over\n");
        write(1, buf, len);
        return 0;
}