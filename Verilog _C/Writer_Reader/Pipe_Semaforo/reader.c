#include <fcntl.h>  // O_WRONLY
#include <stdio.h>  //printf()
#include <sys/stat.h>  //mkfifo()
#include <unistd.h>  //write()
#include <sys/resource.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <semaphore.h>

int main() {

    int fd, values[10000];

    sem_t  *limit;

    key_t key = 123;

    int shmid = shmget(key, sizeof(limit), 0666 | IPC_CREAT);

    if (shmid < 0) {
        perror("shmget");
        return 0;
    }

    limit = (sem_t*) shmat(shmid, NULL, 0);

    if (limit == (sem_t*) -1) {
        perror("shmgat");
        return 0;
    }

	sem_init(&(*limit),	0,	100);

    char *myfifo = "./fifo";

    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_RDONLY);

	for (int i = 0; i < 10000; i++){

        while(read(fd, &values[i], sizeof(values[i])) == 0);

		sem_post(&(*limit));

		int value;
		sem_getvalue(&(*limit), &value);

        printf("Lido: %d\n", values[i]);
        printf("Value of limit = %d\n", value);

        usleep(99000);

    }

    close(fd);

    unlink(myfifo);

	return 0;

}