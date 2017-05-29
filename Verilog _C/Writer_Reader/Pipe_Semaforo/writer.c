#include <fcntl.h>  // O_WRONLY
#include <stdio.h>  //printf()
#include <sys/stat.h>  //mkfifo()
#include <unistd.h>  //write()
#include <stdlib.h>  //rand()
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <semaphore.h>

int main() {

	int fd, values[10000];

	sem_t *limit;

    key_t key = 123;

    int shmid = shmget(key, sizeof(limit), 0666);

    if (shmid < 0) {
        perror("shmget");
        return 0;
    }

    limit = (sem_t*) shmat(shmid, NULL, 0);

    if (limit == (sem_t*) -1) {
        perror("shmgat");
        return 0;
    }

	int value;
	sem_getvalue(&(*limit), &value);
	printf("Value of limit = %d\n", value);

    char *myfifo = "./fifo";

    fd = open(myfifo, O_RDWR);

    for (int k = 0; k < 10000; k++) {

	    values[k] = rand() % 256;

		int value;
		sem_getvalue(&(*limit), &value);

		while (value == 0) {
			sem_getvalue(&(*limit), &value);
		}

		sem_wait(&(*limit));

		printf("Value of limit = %d\n", value);

	    while(write(fd, &values[k], sizeof(values[k])) == 0);
	            
	    printf("Escrito: %d\n", values[k]);

	}

    close(fd);
    
    return 0;

}