#include <fcntl.h>  // O_WRONLY
#include <stdio.h>  // printf()
#include <sys/stat.h>  // mkfifo()
#include <unistd.h>  // write()
#include <stdlib.h>  // rand()
#include <math.h>  // abs()
#include <sys/ipc.h>  // key
#include <sys/shm.h>  // shm methods
#include <semaphore.h>  // Sincronização de processos

// Variável utilizada para receber o id do pipe.
int fd;

// Variável utilizada para acessar um espaço de memória compartilhado
// com o programa que lerá os dados.
sem_t *limit;

// Método responsável por buscar o espaço de memória compartilhada.
void shm_init() {

	// Id temporário para obtenção da memória. Deve ser o mesmo utilizado
	// na alocação dela.
    key_t key = 123;

	// Obtenção do espaço de memória a partir do id temporário.
	// A função shmget retorna o id verdadeiro da memória.
    int shmid = shmget(key, sizeof(limit), 0666);

    // Verificação se foi possível a obtenção de memória.
    if (shmid < 0) {
        perror("shmget");
        return;
    }

    // limit recebe o endereço da memória alocada.
    limit = (sem_t*) shmat(shmid, NULL, 0);

    // Verificação se a atribuição do endero é válida.
    if (limit == (sem_t*) -1) {
        perror("shmgat");
        return;
    }

    int value;
    sem_getvalue(&(*limit), &value);
    //printf("Value of limit = %d\n", value);
}


// Método responsável pelo cálculo do resultado da SAD a partir dos dados
// gerados no vetor.
int result(int* values) {

	int abs_diff = 0;

    for (int j = 0; j < 8; j++) {

    	for (int i = 0; i < 4; i++) {

    		abs_diff += abs(values[i+(j*8)] - values[i+(j*8)+4]);

    	}

    }

    int value;
    sem_getvalue(&(*limit), &value);
    //printf("Value of limit = %d\n", value);

    // Laço de atualização do valor atual do semáforo.
    while (value == 0) {
        sem_getvalue(&(*limit), &value);
    }

    // Decremento do limite caso o mesmo for maior que zero.
    sem_wait(&(*limit));

    int control = 0;

    // Escreve o valor gerado dentro do arquivo de sistema
    // caso ele esteja aberto, senão mostra um erro.
    while(control == 0) {

        control = write(fd, &abs_diff, sizeof(abs_diff));

        if (control == -1) {

            printf("Erro ao escrever no pipe!\n");

            return 0;

        }

    }

    return abs_diff;

}

// Método responsável pela geração de dados aleatórios para o vetor e
// inserção dos mesmos no pipe.
void write_values(int* values){

    for (int j = 0; j < 8; j++) {

        // Laço que gera os dados e insere no arquivo.
        for(int i = 0; i < 8; i++){

            values[i+(j*8)] = rand() % 256;

            int value;
            sem_getvalue(&(*limit), &value);
            //printf("Value of limit = %d\n", value);

            // Laço de atualização do valor atual do semáforo.
            while (value == 0) {
                sem_getvalue(&(*limit), &value);
            }

            // Decremento do limite caso o mesmo for maior que zero.
            sem_wait(&(*limit));

            int control = 0;

            // Escreve o valor gerado dentro do arquivo de sistema
            // caso ele esteja aberto, senão mostra um erro.
            while(control == 0) {

                control = write(fd, &values[i+(j*8)], sizeof(values[i+(j*8)]));

                if (control == -1) {

                    printf("Erro ao escrever no pipe!\n");

                    return;

                }

            }
                    
            printf("Escrito: %d\n", values[i+(j*8)]);

        }

    }

}

int main() {

    int values[64];

    // Chamada da rotina de busca da memória compartilhada para obtenção
    // do endereço da mesma.
    shm_init();

    // Armazena o endereço onde será gerado o arquivo de sistema e o
    // nome dele.
    char *myfifo = "./fifo";

    // Abre o arquivo apenas para escrita, retornando o id do mesmo.
    fd = open(myfifo, O_WRONLY);

    // Laço que implementa o número vezes que devem ser gerado dados para
    // a arquitetura, ou seja, o número de testes a serem realizados.
    for (int i = 0; i < 10000; i++) {

        write_values(values);
    	printf("\nresult = %d\n\n", result(values));
        
    }

    // Fechamento do pipe.
    close(fd);
    
    return 0;
}