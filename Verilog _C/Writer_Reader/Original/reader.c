#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/resource.h>

int result(int ctrl) {
	return 0;
}

int result(){

	int fd, result_sad;

    // Armazeno o endereço onde será gerado o
    //arquivo de sistema e o nome dele
    char *myfifo = "./fifo";

    // Cria o arquivo na pasta com o respectivo nome
    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_RDONLY);

    // Escreve o valor do arquivo na posição x do vetor
    while(read(fd, &result_sad, sizeof(result_sad)) == 0);
    
    // Fecha o arquivo com o respectivo id
    close(fd);

    // Remove o determinado arquivo da pasta
    unlink(myfifo);

    return result_sad;

}

void reader_values(int* values){

    int fd;

    // Armazeno o endereço onde será gerado o
    //arquivo de sistema e o nome dele
    char *myfifo = "./fifo";

    // Cria o arquivo na pasta com o respectivo nome
    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_RDONLY);

    for (int i = 0; i < 8; i++){

        // Escreve o valor do arquivo na posição x do vetor
        while(read(fd, &values[i], sizeof(values[i])) == 0);
        printf("Lido: %d\n", values[i]);
    }
    
    // Fecha o arquivo com o respectivo id
    close(fd);

    // Remove o determinado arquivo da pasta
    unlink(myfifo);

}

int main() {

	int values[8];
	
	printf("Sad_1 = %d\n\n", result(0));

	reader_values(values);

	printf("\nCalculando Sad_2...\n");

	printf("\nSad_2 = %d\n", result());

	return 0;

}