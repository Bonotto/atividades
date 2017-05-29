#include <fcntl.h>  // O_WRONLY
#include <stdio.h>  //printf()
#include <sys/stat.h>  //mkfifo()
#include <unistd.h>  //write()
#include <stdlib.h>  //rand()
#include <math.h>

int result(int* values) {

	int fd, abs_diff = 0;

	for (int i = 0; i < 4; i++) {

		abs_diff += abs(values[i] - values[i + 4]);

	}

    // Armazeno o endereço onde será gerado o
    //arquivo de sistema e o nome dele
    char *myfifo = "./fifo";

    // Abre o arquivo apenas para escrita, retornando o id do mesmo
    fd = open(myfifo, O_WRONLY);

    // Escreve o valor gerado dentro do arquivo de sistema
    while(write(fd, &abs_diff, sizeof(abs_diff)) == 0);

    // Fecha o arquivo com o respectivo id
    close(fd);

    return abs_diff;

}

void write_values(int* values){

    int fd;

    // Armazeno o endereço onde será gerado o
    //arquivo de sistema e o nome dele
    char *myfifo = "./fifo";

    // Abre o arquivo apenas para escrita, retornando o id do mesmo
    fd = open(myfifo, O_WRONLY);

    // Laço que gera os dados e insere no arquivo
    for(int i = 0; i < 8; i++){

        values[i] = rand() % 256;

        // Escreve o valor gerado dentro do arquivo de sistema
        while(write(fd, &values[i], sizeof(values[i])) == 0);
        printf("Valor escrito: %d\n", values[i]);

    }
    
    // Fecha o arquivo com o respectivo id
    close(fd);

}

int main() {

	int values[8];

	write_values(values);

	usleep(10000);

	printf("result = %d\n", result(values));
    
    return 0;
}