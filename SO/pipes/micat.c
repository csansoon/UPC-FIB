#include <unistd.h>

int main(int argc, char **argv){
        char c;
        
        while(read(20, &c, 1) > 0)
                write(30, &c, 1);
        
        return 0;
}