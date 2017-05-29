#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int fd;
    char * myfifo = "./fifo";
    int buf;

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
	printf("Esperando para ler\n");
	int i =0;
    while(i<100){
    	i++;
    	printf("Vou ler\n");
    	read(fd, &buf, sizeof(buf));
    	printf("Lido: %d\n", buf);
  	}
    
    close(fd);

    return 0;
}