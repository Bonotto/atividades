#include <fcntl.h>  // O_WRONLY
#include <stdio.h>  //printf()
#include <sys/stat.h>  //mkfifo()
#include <unistd.h>  //write()

int main() {

    long int i, value;
    int fd;

    char *myfifo = "./fifo";

    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_RDONLY);

	for (i = 0; i < 50000; i++){

        while(read(fd, &value, sizeof(value)) == 0);

        printf("Lido: %ld\n", value);

        usleep(900);

    }

    close(fd);

    unlink(myfifo);

	return 0;

}