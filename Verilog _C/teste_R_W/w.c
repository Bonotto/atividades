#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char * myfifo = "./fifo";

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    /* write "Hi" to the FIFO */
    fd = open(myfifo, O_WRONLY);
    int j=0;
    while(j<122){
        printf("Escrevendo %d\n", j);
        while(write(fd, &j, sizeof(j))==0);
        j++;
    }
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);
}