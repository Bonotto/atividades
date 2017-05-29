#include "acc_user.h"
#include <stdio.h>

typedef char *string;

//Declaração dos handles que serão utilizados
//Cada handle carrega informações sobre um objeto especifico do design.
//As informações são relativas ao tipo de objeto e tambem sobre onde encontrar dados relativos ao objeto.
handle e1;
handle e2;
handle result;
handle i;

void sad();
void sad_entradas();
int converter(string in_string, int no_bits);

//Rotina responsável por ficar monitorando os objetos do código verilog e chamar outras
//rotinas quando houver alterações nestes.
void sad_monitor(){
	
	//Inicializa o ambiente para as rotinas "acc". Deve ser chamado antes de utilizar
	//qualquer outra rotina "acc"
	acc_initialize();
	
	//Atribui um handle para cada um dos argumentos fornecidos quando é feita a chamada
	//no código em verilog
	e1 = acc_handle_tfarg(1);
	e2 = acc_handle_tfarg(2);
	result = acc_handle_tfarg(3);
	i = acc_handle_tfarg(4);
	
	//A rotina acc_vlc_add(object_handle, consumer_routine, user_data, vcl_flag) chama a 
	//consumer_routine sempre que valor do objeto dado pelo object_handle tiver seu valor 
	//lógico alterado.
	acc_vcl_add(i, sad_entradas, null, vcl_verilog_logic);
	acc_vcl_add(result, sad, null, vcl_verilog_logic);
	
	//Libera a memória interna utilizada pelas rotinas "acc". 
	acc_close();
	
}

//Rotina responsável por gerar os valores que serão atribuidos as entradas da SAD, tanto do 
//modelo C, quanto da do desing em Verilog.
void sad_entradas(){
	
	//Defini-se uma string para cada uma das entradas da SAD
	char valor1[128];
	char valor2[128];
	
	//Atribui-se um valor randômico(decimal) para cada uma das strings
	sprintf (valor1, "%d%d%d%d",rand(),rand(),rand(),rand());
	sprintf (valor2, "%d%d%d%d",rand(),rand(),rand(),rand());
	
	//O valor lógico a ser escrito e o delay na propagação deste são colocados em duas
	//estruturas referenciadas pelo seus ponteiros.
	
	//value_s1 e value_s2 são ponteiros para a structure type s_setval_value
	s_setval_value value_s1;
	s_setval_value value_s2;
	
	//delay_s é um ponteiro para a structure type s_setval_delay
	s_setval_delay delay_s;
	
	//Defini-se que o formato em que será fornecido os valores para serem
	//colocados na entrada da SAD são strings de decimais
	value_s1.format = accDecStrVal;
	value_s2.format = accDecStrVal;
	
	//Defini-se que não haverá delay na propagação
	delay_s.model = accNoDelay;
	
	value_s1.value.str = valor1;
	value_s2.value.str = valor2;
	
	//Escreve nos reg e1 e e2
	acc_set_value(e1, &value_s1, &delay_s);
	acc_set_value(e2, &value_s2, &delay_s);
}

//Rotina responsável por pegar os valores na entrada da SAD em verilog, e utiliza-los como
//entrada para o modelo em C. Posteriormente verifica se o resultado obtido pelo modelo em 
//C confere com o resultado da SAD em verilog.
void sad(){
	
	//Declaração dos argumentos necessários para utilizar acc_fetch_value
	p_acc_value value;
	
	//Faz a leitura dos reg e1 e e2 e do result e atribui nas strings i_e1, i_e2 e i_result
	string i_e1 = acc_fetch_value(e1,"%b",value);
	string i_e2 = acc_fetch_value(e2,"%b",value);
	string i_result = acc_fetch_value(result,"%b", value);

	//Converte-se o valor binário nas string i_e1, e i_e2 para valores inteiros decimais.
	//É importante observar que ambas as strings i_e1 e i_e2 carregam entradas com 128 bits(16 pixels com 8 bits)
	//e para fazer o cálculo da SAD precisamos destes 32 valores separados, por isso é criado dois arrays de inteiros.
	
	int int_e1[16];
	int int_e2[16];
	int int_result;

	int_result = converter(i_result, 12);
	
	int i;

	for (i = 0; i <= 15; i = i+1){
		int_e1[i] = converter((i_e1 + 8*i),8);
		int_e2[i] = converter((i_e2 + 8*i),8);
	}
	
	//Calcula a SAD pelo modelo em C. A variável "sad_total" irá carregar o resultado do cálculo.
	int sub[16];
	int sad_parcial[16];
	int sad_total = 0;

	for (i = 0; i <= 15; i = i+1){
		sub[i] = int_e1[i] - int_e2[i];
		if (sub[i] <= 0){
			sad_parcial[i] = -sub[i];
		}else{
			sad_parcial[i] = sub[i];
		}
		sad_total = sad_total + sad_parcial[i];
	}
	
	//Imprime na tela o resultado obtido tanto pela SAD Verilog quanto pela SAD C
	io_printf("*************************************************\n");
	io_printf("sad_verilog = %d\nsad_c = %d\n", int_result, sad_total); 
	
	//Imprime "ok" na tela caso os resultados sejam iguais, e "erro" caso sejam diferentes
	if (int_result == sad_total){
		io_printf("ok \n");
	} else {
		io_printf("erro \n");
	}
}

//Função utilizada para converter strings com números bínarios em inteiros
int converter(string in_string, int no_bits){
	
	int conv = 0;
	int i = 0;
	int j = 0;
	int bin = 0;

	// For gerado para varrer a string de acordo com o número de bits, do mais significativo (no_bits-1) até o bit zero
	for (i = no_bits-1; i >= 0; i = i-1){
		if(*(in_string+i) == 49){
			bin = 1;
		}else
			if(*(in_string+i) == 120){
				io_printf("%d, Warning: X detected\n");
				bin = 0;
			}else
				if (*(in_string+i) == 122){
				io_printf("%d, Warning : Z detected\n");
				}else{
					bin = 0;
				}
				conv = conv + (1 << j)*bin;
				j ++;
	}
	return conv;
}
