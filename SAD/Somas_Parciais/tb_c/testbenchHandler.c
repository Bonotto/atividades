#include "acc_user.h"  // acc routines
#include <stdio.h>  // printf()
#include <sys/stat.h>  // mkfifo()
#include <unistd.h>  // read()
#include <fcntl.h>  // O_RDONLY
#include <sys/ipc.h>  // key
#include <sys/shm.h>  // shm methods
#include <semaphore.h>  // Sincronização de processos

#define WIDTH 8
#define MAX_DATAS 100

typedef char *string;

// Variável utilizada para receber o id do pipe.
int fd;

// Variável utilizada para receber o id da memória compartilhada.
int shmid;

// Armazeno o endereço onde será gerado o pipe e o nome dele.
char *myfifo = "./fifo";

// Variável utilizada para acessar um espaço de memória compartilhado
// com o programa que fornecerá os dados.
sem_t *limit;

// Cada handle carrega informações sobre um objeto específico do design.
// As informações são relativas ao tipo de objeto e também sobre onde
// encontrar dados relativos ao objeto.
handle loaded;
handle load;
handle ack;
handle done;
handle ori_0;
handle ori_1;
handle ori_2;
handle ori_3;
handle can_0;
handle can_1;
handle can_2;
handle can_3;
handle out_sad;
handle end_sim;

void delete();
void shrm_init();
int get_result();
void define_ack();
void catch_values();
void sad_entradas();
void define_loaded();
void out_sad_verilog();
int converter(string in_string, int no_bits);

// Rotina responsável por monitorar os objetos do código verilog
// e chamar outras rotinas quando houver alterações no valor deles.
void sad_monitor(){
	
	// Inicializa o ambiente para as rotinas "acc". Deve ser chamado antes
	// de utilizar qualquer outra rotina "acc".
	acc_initialize();
	
	// Atribui um handle para cada um dos argumentos fornecidos quando
	// é feita a chamada no código em verilog.
	loaded = acc_handle_tfarg(1);
	load = acc_handle_tfarg(2);
	ack = acc_handle_tfarg(3);
	done = acc_handle_tfarg(4);
	ori_0 = acc_handle_tfarg(5);
	ori_1 = acc_handle_tfarg(6);
	ori_2 = acc_handle_tfarg(7);
	ori_3 = acc_handle_tfarg(8);
	can_0 = acc_handle_tfarg(9);
	can_1 = acc_handle_tfarg(10);
	can_2 = acc_handle_tfarg(11);
	can_3 = acc_handle_tfarg(12);
	out_sad = acc_handle_tfarg(13);
	end_sim = acc_handle_tfarg(14);
	
	// A rotina acc_vlc_add(handle, consumer_routine, user_data, vcl_flag)
	// chama a consumer_routine sempre que valor do objeto dado pelo
	// handle tiver seu valor lógico alterado.
	acc_vcl_add(load, sad_entradas, null, vcl_verilog_logic);
	acc_vcl_add(done, out_sad_verilog, null, vcl_verilog_logic);
	acc_vcl_add(end_sim, delete, null, vcl_verilog_logic);

	// Libera a memória interna utilizada pelas rotinas "acc". 
	acc_close();

    // Cria o pipe na pasta indicada por myfifo com o respectivo nome.
    mkfifo(myfifo, 0666);

    // Abre o pipe para ser lido e insere o id dele em fd para controle
    // posteriormente.
	fd = open(myfifo, O_RDONLY);

	// Chama a rotina que cria o espaço de memória compartilhada.
	shrm_init();
	
}

// Rotina responsável por verificar o valor lógico de "load", se caso for 1
// ela chama o método de leitura do pipe para preencher o vetor de dados
// e assim que o mesmo estiver completo, os valores dele são inseridos nos
// registradores oris e cans.
void sad_entradas(){

	p_acc_value value;

	// Inserção do valor do sinal em uma string.
	string i_load = acc_fetch_value(load,"%b", value);

	// Conversão do sinal de binário para inteiro.
	int v_load = converter(i_load, 2);

	if (v_load) {
	
		// Criação do vetor de dados.
		int values[WIDTH];

		// Chamada da função de leitura do pipe e escrita no vetor.
		catch_values(values);

		// Criação das strings que receberão os valores do vetor de dados.
		char valor_ori_0[WIDTH];
		char valor_ori_1[WIDTH];
		char valor_ori_2[WIDTH];
		char valor_ori_3[WIDTH];
		char valor_can_0[WIDTH];
		char valor_can_1[WIDTH];
		char valor_can_2[WIDTH];
		char valor_can_3[WIDTH];
		
		// Atribuição de um dado do vetor a cada uma das strings.
		sprintf (valor_ori_0, "%d", values[0]);
		sprintf (valor_ori_1, "%d", values[1]);
		sprintf (valor_ori_2, "%d", values[2]);
		sprintf (valor_ori_3, "%d", values[3]);
		sprintf (valor_can_0, "%d", values[4]);
		sprintf (valor_can_1, "%d", values[5]);
		sprintf (valor_can_2, "%d", values[6]);
		sprintf (valor_can_3, "%d", values[7]);
		
		// delay_s é um ponteiro para a structure type s_setval_delay.
		s_setval_delay delay_s;
		
		// Defini-se que não haverá delay na propagação.
		delay_s.model = accNoDelay;
		
		// Criação dos ponteiros para a structure type s_setval_value
		s_setval_value valor_o_0;
		s_setval_value valor_o_1;
		s_setval_value valor_o_2;
		s_setval_value valor_o_3;
		s_setval_value valor_c_0;
		s_setval_value valor_c_1;
		s_setval_value valor_c_2;
		s_setval_value valor_c_3;
		
		// Definição do formato em que serão fornecidos os valores a serem
		// gravados nos resgistradores da entrada da SAD.
		valor_o_0.format = accDecStrVal;
		valor_o_1.format = accDecStrVal;
		valor_o_2.format = accDecStrVal;
		valor_o_3.format = accDecStrVal;
		valor_c_0.format = accDecStrVal;
		valor_c_1.format = accDecStrVal;
		valor_c_2.format = accDecStrVal;
		valor_c_3.format = accDecStrVal;
		
		// Faz-se com que cada um dos ponteiros apontem para uma respectiva
		// string de dados.
		valor_o_0.value.str = valor_ori_0;
		valor_o_1.value.str = valor_ori_1;
		valor_o_2.value.str = valor_ori_2;
		valor_o_3.value.str = valor_ori_3;
		valor_c_0.value.str = valor_can_0;
		valor_c_1.value.str = valor_can_1;
		valor_c_2.value.str = valor_can_2;
		valor_c_3.value.str = valor_can_3;
		
		// Escreve nos registradores de entrada da arquitetura.
		acc_set_value(ori_0, &valor_o_0, &delay_s);
		acc_set_value(ori_1, &valor_o_1, &delay_s);
		acc_set_value(ori_2, &valor_o_2, &delay_s);
		acc_set_value(ori_3, &valor_o_3, &delay_s);
		acc_set_value(can_0, &valor_c_0, &delay_s);
		acc_set_value(can_1, &valor_c_1, &delay_s);
		acc_set_value(can_2, &valor_c_2, &delay_s);
		acc_set_value(can_3, &valor_c_3, &delay_s);

	}

	// Chamada do método para realizar a transição de estado, uma vez
	// que os dados necessários já se encontram nos registradores.
	define_loaded();

}

// Rotina responsável por verificar o valor lógico de "done", se caso for 1
// ela pega o valor do registrador de saída da arquitetura e chama o método
// de leitura do pipe para preencher o valor de resultado a ser comparado.
void out_sad_verilog(){

	p_acc_value value;

	// Inserção do valor do sinal em uma string.
	string i_done = acc_fetch_value(done,"%b", value);

	// Conversão do sinal de binário para inteiro.
	int v_done = converter(i_done, 2);

	if (v_done) {

		p_acc_value value;

		string i_out_sad = acc_fetch_value(out_sad,"%b", value);

		int int_out_sad = converter(i_out_sad, 13);

		// Chamada do método de leitura do pipe para busca de resultado.
		int result = get_result();
		
		// Comparação dos resultados obtidos e impreção na tela dos
		// mesmos caso sejam diferentes.
		if (int_out_sad != result){
			io_printf("*************************ERRO*************************\n");
			io_printf("\nsad_v = %d\nsad_c = %d\n\n", int_out_sad, result);
		}

	}

	// Chamada do método para realizar a transição de estado uma vez
	// que o valor de saída da arquitetura já foi utilizado.
	define_ack();

}

// Função utilizada para converter strings de bits em um valor inteiro.
int converter(string in_string, int no_bits){
	
	int conv = 0;
	int i = 0;
	int j = 0;
	int bin = 0;

	for (i = no_bits-1; i >= 0; i = i-1){
		if(*(in_string+i) == 49){
			bin = 1;
		} else if(*(in_string+i) == 120){
			//io_printf("%d, Warning : X detected\n");
			bin = 0;
		} else if (*(in_string+i) == 122){
			//io_printf("%d, Warning : Z detected\n");
		} else {
			bin = 0;
		}
		conv = conv + (1 << j)*bin;
		j ++;
	}

	return conv;
}

// Método responsável por fazer a leitura do pipe e inserir os valores
// no vetor de dados.
void catch_values(int* values) {

    for (int x = 0; x < WIDTH; x++){

		// Escreve o valor do arquivo na posição x do vetor
	    while(read(fd, &values[x], sizeof(values[x])) == 0);

        //printf("Lido: %d\n", values[x]);

		// O limite é incrementado em um, aumentando o 
		// número de dados que podem ser escritos no pipe.
		// Com o semáforo garante-se que o incremento será
		// atômico.
        sem_post(&(*limit));

		//int value;
		//sem_getvalue(&(*limit), &value);
        //printf("Value of limit = %d\n", value);

    }

}

// Método responsável por setar o valor lógico do registrador loaded para
// que arquitetura possa prosseguir ao método de cálculo da SAD.
void define_loaded(){
	
	s_setval_delay delay_s;
	delay_s.model = accNoDelay;

	s_setval_value value_loaded;
	value_loaded.format = accDecStrVal;
	value_loaded.value.str = "1";

	acc_set_value(loaded, &value_loaded, &delay_s);

}

// Método responsável por fazer a leitura do pipe e retornar o valor
// a ser comparado com a saida da arquitetura.
int get_result(){

	int sad;

	while(read(fd, &sad, sizeof(sad)) == 0);

	// O limite é incrementado em um, aumentando o 
	// número de dados que podem ser escritos no pipe.
	// Com o semáforo garante-se que o incremento será
	// atômico.
    sem_post(&(*limit));

	//int value;
	//sem_getvalue(&(*limit), &value);
    //printf("Value of limit = %d\n", value);

    return sad;
	
}

// Método responsável por setar o valor lógico do registrador ack para
// que arquitetura possa retornar ao ponto de início.
void define_ack(){
	
	s_setval_delay delay_s;
	delay_s.model = accNoDelay;

	s_setval_value value_ack;
	value_ack.format = accDecStrVal;
	value_ack.value.str = "1";

	acc_set_value(ack, &value_ack, &delay_s);

}

// Responsável por verificar o sinal del_pipe, que fica ativo sempre que
// a simulação estiver terminada. Com isso o pipe pode ser deletado.
void delete() {

	p_acc_value value;

	// Inserção do valor do sinal em uma string.
	string i_delete = acc_fetch_value(end_sim,"%b", value);

	// Conversão do sinal de binário para inteiro.
	int v_delete = converter(i_delete, 2);

	if (v_delete) {

		// Fecha o pipe.
		close(fd);

	    // Remove o arquivo da pasta especificada por "myfifo".
	    unlink(myfifo);

	    // Desvincula a memória compartilhada.
		shmdt(limit);

		// Desaloca a memória com o respectivo id.
		shmctl(shmid, IPC_RMID, NULL);

	}

}

// Método responsável por criar um espaço de memória compartilhada.
void shrm_init() {

	// Id temporário para criação da memória.
	key_t key = 123;

	// Criação do espaço de memória a partir do id temporário.
	// A função shmget retorna o id "verdadeiro" da memória.
    shmid = shmget(key, sizeof(limit), 0666 | IPC_CREAT);

    // Verificação se foi possível a alocação de memória.
    if (shmid < 0) {
        perror("shmget");
        return;
    }

    // limit recebe o endereço da memória alocada.
    limit = (sem_t*) shmat(shmid, NULL, 0);

    // Verificação se a atribuição do endereço é válida.
    if (limit == (sem_t*) -1) {
        perror("shmgat");
        return;
    }

	// Inicialização do semáforo com o limite máximo permitido menos
	// um, por garantia de que não haja sobreposição do limite inicial.
	sem_init(&(*limit),	0, MAX_DATAS-1);

}