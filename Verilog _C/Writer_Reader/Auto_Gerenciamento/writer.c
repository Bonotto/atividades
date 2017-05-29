#include <fcntl.h>  // O_WRONLY
#include <stdio.h>  //printf()
#include <sys/stat.h>  //mkfifo()
#include <unistd.h>  //write()

int main() {

	long int i;
	int fd;

    char *myfifo = "./fifo";

    fd = open(myfifo, O_WRONLY);

    for (i = 0; i < 50000; i++) {

	    while(write(fd, &i, sizeof(i)) == 0);
	            
	    printf("Escrito: %ld\n", i);

	}

    close(fd);
    
    return 0;

}