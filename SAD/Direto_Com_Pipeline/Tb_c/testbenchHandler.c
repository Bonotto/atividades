#include "acc_user.h"
#include <stdio.h>

typedef char *string;

//Declaração dos handles que serão utilizados
//Cada handle carrega informações sobre um objeto especifico do design.
//As informações são relativas ao tipo de objeto e tambem sobre onde encontrar dados relativos ao objeto.

int out_sad_c[3];

handle i;
handle ori_0;
handle ori_1;
handle ori_2;
handle ori_3;
handle ori_4;
handle ori_5;
handle ori_6;
handle ori_7;
handle ori_8;
handle ori_9;
handle ori_10;
handle ori_11;
handle ori_12;
handle ori_13;
handle ori_14;
handle ori_15;
handle ori_16;
handle ori_17;
handle ori_18;
handle ori_19;
handle ori_20;
handle ori_21;
handle ori_22;
handle ori_23;
handle ori_24;
handle ori_25;
handle ori_26;
handle ori_27;
handle ori_28;
handle ori_29;
handle ori_30;
handle ori_31;
handle can_0;
handle can_1;
handle can_2;
handle can_3;
handle can_4;
handle can_5;
handle can_6;
handle can_7;
handle can_8;
handle can_9;
handle can_10;
handle can_11;
handle can_12;
handle can_13;
handle can_14;
handle can_15;
handle can_16;
handle can_17;
handle can_18;
handle can_19;
handle can_20;
handle can_21;
handle can_22;
handle can_23;
handle can_24;
handle can_25;
handle can_26;
handle can_27;
handle can_28;
handle can_29;
handle can_30;
handle can_31;
handle out_sad;

void sad_entradas();
void out_sad_verilog();
int converter(string in_string, int no_bits);

//Rotina responsável por ficar monitorando os objetos do código verilog e chamar outras
//rotinas quando houver alterações nestes.
void sad_monitor(){
	
	//Inicializa o ambiente para as rotinas "acc". Deve ser chamado antes de utilizar
	//qualquer outra rotina "acc"
	acc_initialize();
	
	//Atribui um handle para cada um dos argumentos fornecidos quando é feita a chamada
	//no código em verilog
	i = acc_handle_tfarg(1);
	ori_0 = acc_handle_tfarg(2);
	ori_1 = acc_handle_tfarg(3);
	ori_2 = acc_handle_tfarg(4);
	ori_3 = acc_handle_tfarg(5);
	ori_4 = acc_handle_tfarg(6);
	ori_5 = acc_handle_tfarg(7);
	ori_6 = acc_handle_tfarg(8);
	ori_7 = acc_handle_tfarg(9);
	ori_8 = acc_handle_tfarg(10);
	ori_9 = acc_handle_tfarg(11);
	ori_10 = acc_handle_tfarg(12);
	ori_11 = acc_handle_tfarg(13);
	ori_12 = acc_handle_tfarg(14);
	ori_13 = acc_handle_tfarg(15);
	ori_14 = acc_handle_tfarg(16);
	ori_15 = acc_handle_tfarg(17);
	ori_16 = acc_handle_tfarg(18);
	ori_17 = acc_handle_tfarg(19);
	ori_18 = acc_handle_tfarg(20);
	ori_19 = acc_handle_tfarg(21);
	ori_20 = acc_handle_tfarg(22);
	ori_21 = acc_handle_tfarg(23);
	ori_22 = acc_handle_tfarg(24);
	ori_23 = acc_handle_tfarg(25);
	ori_24 = acc_handle_tfarg(26);
	ori_25 = acc_handle_tfarg(27);
	ori_26 = acc_handle_tfarg(28);
	ori_27 = acc_handle_tfarg(29);
	ori_28 = acc_handle_tfarg(30);
	ori_29 = acc_handle_tfarg(31);
	ori_30 = acc_handle_tfarg(32);
	ori_31 = acc_handle_tfarg(33);
	can_0 = acc_handle_tfarg(34);
	can_1 = acc_handle_tfarg(35);
	can_2 = acc_handle_tfarg(36);
	can_3 = acc_handle_tfarg(37);
	can_4 = acc_handle_tfarg(38);
	can_5 = acc_handle_tfarg(39);
	can_6 = acc_handle_tfarg(40);
	can_7 = acc_handle_tfarg(41);
	can_8 = acc_handle_tfarg(42);
	can_9 = acc_handle_tfarg(43);
	can_10 = acc_handle_tfarg(44);
	can_11 = acc_handle_tfarg(45);
	can_12 = acc_handle_tfarg(46);
	can_13 = acc_handle_tfarg(47);
	can_14 = acc_handle_tfarg(48);
	can_15 = acc_handle_tfarg(49);
	can_16 = acc_handle_tfarg(50);
	can_17 = acc_handle_tfarg(51);
	can_18 = acc_handle_tfarg(52);
	can_19 = acc_handle_tfarg(53);
	can_20 = acc_handle_tfarg(54);
	can_21 = acc_handle_tfarg(55);
	can_22 = acc_handle_tfarg(56);
	can_23 = acc_handle_tfarg(57);
	can_24 = acc_handle_tfarg(58);
	can_25 = acc_handle_tfarg(59);
	can_26 = acc_handle_tfarg(60);
	can_27 = acc_handle_tfarg(61);
	can_28 = acc_handle_tfarg(62);
	can_29 = acc_handle_tfarg(63);
	can_30 = acc_handle_tfarg(64);
	can_31 = acc_handle_tfarg(65);
	out_sad = acc_handle_tfarg(66);
	
	//A rotina acc_vlc_add(object_handle, consumer_routine, user_data, vcl_flag) chama a 
	//consumer_routine sempre que valor do objeto dado pelo object_handle tiver seu valor 
	//lógico alterado.
	acc_vcl_add(i, sad_entradas, null, vcl_verilog_logic);
	acc_vcl_add(out_sad, out_sad_verilog, null, vcl_verilog_logic);

	//Libera a memória interna utilizada pelas rotinas "acc". 
	acc_close();
	
}

//Rotina responsável por gerar os valores que serão atribuidos as entradas da SAD, tanto do 
//modelo C, quanto da do desing em Verilog.
void sad_entradas(){
	
	//Defini-se uma string para cada uma das entradas da SAD
	int valor_ori[32];
	int valor_can[32];
	int abs_diff = 0;

	out_sad_c[2] = out_sad_c[1];
	out_sad_c[1] = out_sad_c[0];
	out_sad_c[0] = 0;

	for(int x = 0; x < 32; x++){

		valor_ori[x] = rand() % 256;
		valor_can[x] = rand() % 256;

		abs_diff = valor_ori[x] - valor_can[x];

		if (abs_diff < 0){
			out_sad_c[0] += -abs_diff;
		}else{
			out_sad_c[0] += abs_diff;
		}

		//io_printf("\nori = %d\ncan = %d\ndiff = %d\n out_c = %d\n", valor_ori[x], valor_can[x], abs_diff, out_sad_c);

	}

	char valor_ori_0[8];
	char valor_ori_1[8];
	char valor_ori_2[8];
	char valor_ori_3[8];
	char valor_ori_4[8];
	char valor_ori_5[8];
	char valor_ori_6[8];
	char valor_ori_7[8];
	char valor_ori_8[8];
	char valor_ori_9[8];
	char valor_ori_10[8];
	char valor_ori_11[8];
	char valor_ori_12[8];
	char valor_ori_13[8];
	char valor_ori_14[8];
	char valor_ori_15[8];
	char valor_ori_16[8];
	char valor_ori_17[8];
	char valor_ori_18[8];
	char valor_ori_19[8];
	char valor_ori_20[8];
	char valor_ori_21[8];
	char valor_ori_22[8];
	char valor_ori_23[8];
	char valor_ori_24[8];
	char valor_ori_25[8];
	char valor_ori_26[8];
	char valor_ori_27[8];
	char valor_ori_28[8];
	char valor_ori_29[8];
	char valor_ori_30[8];
	char valor_ori_31[8];
	char valor_can_0[8];
	char valor_can_1[8];
	char valor_can_2[8];
	char valor_can_3[8];
	char valor_can_4[8];
	char valor_can_5[8];
	char valor_can_6[8];
	char valor_can_7[8];
	char valor_can_8[8];
	char valor_can_9[8];
	char valor_can_10[8];
	char valor_can_11[8];
	char valor_can_12[8];
	char valor_can_13[8];
	char valor_can_14[8];
	char valor_can_15[8];
	char valor_can_16[8];
	char valor_can_17[8];
	char valor_can_18[8];
	char valor_can_19[8];
	char valor_can_20[8];
	char valor_can_21[8];
	char valor_can_22[8];
	char valor_can_23[8];
	char valor_can_24[8];
	char valor_can_25[8];
	char valor_can_26[8];
	char valor_can_27[8];
	char valor_can_28[8];
	char valor_can_29[8];
	char valor_can_30[8];
	char valor_can_31[8];
	
	//Atribui-se um valor randômico para cada uma das strings
	sprintf (valor_ori_0, "%d", valor_ori[0]);
	sprintf (valor_ori_1, "%d", valor_ori[1]);
	sprintf (valor_ori_2, "%d", valor_ori[2]);
	sprintf (valor_ori_3, "%d", valor_ori[3]);
	sprintf (valor_ori_4, "%d", valor_ori[4]);
	sprintf (valor_ori_5, "%d", valor_ori[5]);
	sprintf (valor_ori_6, "%d", valor_ori[6]);
	sprintf (valor_ori_7, "%d", valor_ori[7]);
	sprintf (valor_ori_8, "%d", valor_ori[8]);
	sprintf (valor_ori_9, "%d", valor_ori[9]);
	sprintf (valor_ori_10, "%d", valor_ori[10]);
	sprintf (valor_ori_11, "%d", valor_ori[11]);
	sprintf (valor_ori_12, "%d", valor_ori[12]);
	sprintf (valor_ori_13, "%d", valor_ori[13]);
	sprintf (valor_ori_14, "%d", valor_ori[14]);
	sprintf (valor_ori_15, "%d", valor_ori[15]);
	sprintf (valor_ori_16, "%d", valor_ori[16]);
	sprintf (valor_ori_17, "%d", valor_ori[17]);
	sprintf (valor_ori_18, "%d", valor_ori[18]);
	sprintf (valor_ori_19, "%d", valor_ori[19]);
	sprintf (valor_ori_20, "%d", valor_ori[20]);
	sprintf (valor_ori_21, "%d", valor_ori[21]);
	sprintf (valor_ori_22, "%d", valor_ori[22]);
	sprintf (valor_ori_23, "%d", valor_ori[23]);
	sprintf (valor_ori_24, "%d", valor_ori[24]);
	sprintf (valor_ori_25, "%d", valor_ori[25]);
	sprintf (valor_ori_26, "%d", valor_ori[26]);
	sprintf (valor_ori_27, "%d", valor_ori[27]);
	sprintf (valor_ori_28, "%d", valor_ori[28]);
	sprintf (valor_ori_29, "%d", valor_ori[29]);
	sprintf (valor_ori_30, "%d", valor_ori[30]);
	sprintf (valor_ori_31, "%d", valor_ori[31]);
	sprintf (valor_can_0, "%d", valor_can[0]);
	sprintf (valor_can_1, "%d", valor_can[1]);
	sprintf (valor_can_2, "%d", valor_can[2]);
	sprintf (valor_can_3, "%d", valor_can[3]);
	sprintf (valor_can_4, "%d", valor_can[4]);
	sprintf (valor_can_5, "%d", valor_can[5]);
	sprintf (valor_can_6, "%d", valor_can[6]);
	sprintf (valor_can_7, "%d", valor_can[7]);
	sprintf (valor_can_8, "%d", valor_can[8]);
	sprintf (valor_can_9, "%d", valor_can[9]);
	sprintf (valor_can_10, "%d", valor_can[10]);
	sprintf (valor_can_11, "%d", valor_can[11]);
	sprintf (valor_can_12, "%d", valor_can[12]);
	sprintf (valor_can_13, "%d", valor_can[13]);
	sprintf (valor_can_14, "%d", valor_can[14]);
	sprintf (valor_can_15, "%d", valor_can[15]);
	sprintf (valor_can_16, "%d", valor_can[16]);
	sprintf (valor_can_17, "%d", valor_can[17]);
	sprintf (valor_can_18, "%d", valor_can[18]);
	sprintf (valor_can_19, "%d", valor_can[19]);
	sprintf (valor_can_20, "%d", valor_can[20]);
	sprintf (valor_can_21, "%d", valor_can[21]);
	sprintf (valor_can_22, "%d", valor_can[22]);
	sprintf (valor_can_23, "%d", valor_can[23]);
	sprintf (valor_can_24, "%d", valor_can[24]);
	sprintf (valor_can_25, "%d", valor_can[25]);
	sprintf (valor_can_26, "%d", valor_can[26]);
	sprintf (valor_can_27, "%d", valor_can[27]);
	sprintf (valor_can_28, "%d", valor_can[28]);
	sprintf (valor_can_29, "%d", valor_can[29]);
	sprintf (valor_can_30, "%d", valor_can[30]);
	sprintf (valor_can_31, "%d", valor_can[31]);

	//O valor lógico a ser escrito e o delay na propagação deste são colocados em duas
	//estruturas referenciadas pelo seus ponteiros.
	
	//value_s1 e value_s2 são ponteiros para a structure type s_setval_value
	s_setval_value valor_o_0;
	s_setval_value valor_o_1;
	s_setval_value valor_o_2;
	s_setval_value valor_o_3;
	s_setval_value valor_o_4;
	s_setval_value valor_o_5;
	s_setval_value valor_o_6;
	s_setval_value valor_o_7;
	s_setval_value valor_o_8;
	s_setval_value valor_o_9;
	s_setval_value valor_o_10;
	s_setval_value valor_o_11;
	s_setval_value valor_o_12;
	s_setval_value valor_o_13;
	s_setval_value valor_o_14;
	s_setval_value valor_o_15;
	s_setval_value valor_o_16;
	s_setval_value valor_o_17;
	s_setval_value valor_o_18;
	s_setval_value valor_o_19;
	s_setval_value valor_o_20;
	s_setval_value valor_o_21;
	s_setval_value valor_o_22;
	s_setval_value valor_o_23;
	s_setval_value valor_o_24;
	s_setval_value valor_o_25;
	s_setval_value valor_o_26;
	s_setval_value valor_o_27;
	s_setval_value valor_o_28;
	s_setval_value valor_o_29;
	s_setval_value valor_o_30;
	s_setval_value valor_o_31;
	s_setval_value valor_c_0;
	s_setval_value valor_c_1;
	s_setval_value valor_c_2;
	s_setval_value valor_c_3;
	s_setval_value valor_c_4;
	s_setval_value valor_c_5;
	s_setval_value valor_c_6;
	s_setval_value valor_c_7;
	s_setval_value valor_c_8;
	s_setval_value valor_c_9;
	s_setval_value valor_c_10;
	s_setval_value valor_c_11;
	s_setval_value valor_c_12;
	s_setval_value valor_c_13;
	s_setval_value valor_c_14;
	s_setval_value valor_c_15;
	s_setval_value valor_c_16;
	s_setval_value valor_c_17;
	s_setval_value valor_c_18;
	s_setval_value valor_c_19;
	s_setval_value valor_c_20;
	s_setval_value valor_c_21;
	s_setval_value valor_c_22;
	s_setval_value valor_c_23;
	s_setval_value valor_c_24;
	s_setval_value valor_c_25;
	s_setval_value valor_c_26;
	s_setval_value valor_c_27;
	s_setval_value valor_c_28;
	s_setval_value valor_c_29;
	s_setval_value valor_c_30;
	s_setval_value valor_c_31;
	
	//delay_s é um ponteiro para a structure type s_setval_delay
	s_setval_delay delay_s;
	
	//Defini-se que o formato em que será fornecido os valores para serem
	//colocados na entrada da SAD são strings de decimais
	valor_o_0.format = accDecStrVal;
	valor_o_1.format = accDecStrVal;
	valor_o_2.format = accDecStrVal;
	valor_o_3.format = accDecStrVal;
	valor_o_4.format = accDecStrVal;
	valor_o_5.format = accDecStrVal;
	valor_o_6.format = accDecStrVal;
	valor_o_7.format = accDecStrVal;
	valor_o_8.format = accDecStrVal;
	valor_o_9.format = accDecStrVal;
	valor_o_10.format = accDecStrVal;
	valor_o_11.format = accDecStrVal;
	valor_o_12.format = accDecStrVal;
	valor_o_13.format = accDecStrVal;
	valor_o_14.format = accDecStrVal;
	valor_o_15.format = accDecStrVal;
	valor_o_16.format = accDecStrVal;
	valor_o_17.format = accDecStrVal;
	valor_o_18.format = accDecStrVal;
	valor_o_19.format = accDecStrVal;
	valor_o_20.format = accDecStrVal;
	valor_o_21.format = accDecStrVal;
	valor_o_22.format = accDecStrVal;
	valor_o_23.format = accDecStrVal;
	valor_o_24.format = accDecStrVal;
	valor_o_25.format = accDecStrVal;
	valor_o_26.format = accDecStrVal;
	valor_o_27.format = accDecStrVal;
	valor_o_28.format = accDecStrVal;
	valor_o_29.format = accDecStrVal;
	valor_o_30.format = accDecStrVal;
	valor_o_31.format = accDecStrVal;
	valor_c_0.format = accDecStrVal;
	valor_c_1.format = accDecStrVal;
	valor_c_2.format = accDecStrVal;
	valor_c_3.format = accDecStrVal;
	valor_c_4.format = accDecStrVal;
	valor_c_5.format = accDecStrVal;
	valor_c_6.format = accDecStrVal;
	valor_c_7.format = accDecStrVal;
	valor_c_8.format = accDecStrVal;
	valor_c_9.format = accDecStrVal;
	valor_c_10.format = accDecStrVal;
	valor_c_11.format = accDecStrVal;
	valor_c_12.format = accDecStrVal;
	valor_c_13.format = accDecStrVal;
	valor_c_14.format = accDecStrVal;
	valor_c_15.format = accDecStrVal;
	valor_c_16.format = accDecStrVal;
	valor_c_17.format = accDecStrVal;
	valor_c_18.format = accDecStrVal;
	valor_c_19.format = accDecStrVal;
	valor_c_20.format = accDecStrVal;
	valor_c_21.format = accDecStrVal;
	valor_c_22.format = accDecStrVal;
	valor_c_23.format = accDecStrVal;
	valor_c_24.format = accDecStrVal;
	valor_c_25.format = accDecStrVal;
	valor_c_26.format = accDecStrVal;
	valor_c_27.format = accDecStrVal;
	valor_c_28.format = accDecStrVal;
	valor_c_29.format = accDecStrVal;
	valor_c_30.format = accDecStrVal;
	valor_c_31.format = accDecStrVal;
	
	//Defini-se que não haverá delay na propagação
	delay_s.model = accNoDelay;
	
	valor_o_0.value.str = valor_ori_0;
	valor_o_1.value.str = valor_ori_1;
	valor_o_2.value.str = valor_ori_2;
	valor_o_3.value.str = valor_ori_3;
	valor_o_4.value.str = valor_ori_4;
	valor_o_5.value.str = valor_ori_5;
	valor_o_6.value.str = valor_ori_6;
	valor_o_7.value.str = valor_ori_7;
	valor_o_8.value.str = valor_ori_8;
	valor_o_9.value.str = valor_ori_9;
	valor_o_10.value.str = valor_ori_10;
	valor_o_11.value.str = valor_ori_11;
	valor_o_12.value.str = valor_ori_12;
	valor_o_13.value.str = valor_ori_13;
	valor_o_14.value.str = valor_ori_14;
	valor_o_15.value.str = valor_ori_15;
	valor_o_16.value.str = valor_ori_16;
	valor_o_17.value.str = valor_ori_17;
	valor_o_18.value.str = valor_ori_18;
	valor_o_19.value.str = valor_ori_19;
	valor_o_20.value.str = valor_ori_20;
	valor_o_21.value.str = valor_ori_21;
	valor_o_22.value.str = valor_ori_22;
	valor_o_23.value.str = valor_ori_23;
	valor_o_24.value.str = valor_ori_24;
	valor_o_25.value.str = valor_ori_25;
	valor_o_26.value.str = valor_ori_26;
	valor_o_27.value.str = valor_ori_27;
	valor_o_28.value.str = valor_ori_28;
	valor_o_29.value.str = valor_ori_29;
	valor_o_30.value.str = valor_ori_30;
	valor_o_31.value.str = valor_ori_31;
	valor_c_0.value.str = valor_can_0;
	valor_c_1.value.str = valor_can_1;
	valor_c_2.value.str = valor_can_2;
	valor_c_3.value.str = valor_can_3;
	valor_c_4.value.str = valor_can_4;
	valor_c_5.value.str = valor_can_5;
	valor_c_6.value.str = valor_can_6;
	valor_c_7.value.str = valor_can_7;
	valor_c_8.value.str = valor_can_8;
	valor_c_9.value.str = valor_can_9;
	valor_c_10.value.str = valor_can_10;
	valor_c_11.value.str = valor_can_11;
	valor_c_12.value.str = valor_can_12;
	valor_c_13.value.str = valor_can_13;
	valor_c_14.value.str = valor_can_14;
	valor_c_15.value.str = valor_can_15;
	valor_c_16.value.str = valor_can_16;
	valor_c_17.value.str = valor_can_17;
	valor_c_18.value.str = valor_can_18;
	valor_c_19.value.str = valor_can_19;
	valor_c_20.value.str = valor_can_20;
	valor_c_21.value.str = valor_can_21;
	valor_c_22.value.str = valor_can_22;
	valor_c_23.value.str = valor_can_23;
	valor_c_24.value.str = valor_can_24;
	valor_c_25.value.str = valor_can_25;
	valor_c_26.value.str = valor_can_26;
	valor_c_27.value.str = valor_can_27;
	valor_c_28.value.str = valor_can_28;
	valor_c_29.value.str = valor_can_29;
	valor_c_30.value.str = valor_can_30;
	valor_c_31.value.str = valor_can_31;
	
	//Escreve nos reg e1 e e2
	acc_set_value(ori_0, &valor_o_0, &delay_s);
	acc_set_value(ori_1, &valor_o_1, &delay_s);
	acc_set_value(ori_2, &valor_o_2, &delay_s);
	acc_set_value(ori_3, &valor_o_3, &delay_s);
	acc_set_value(ori_4, &valor_o_4, &delay_s);
	acc_set_value(ori_5, &valor_o_5, &delay_s);
	acc_set_value(ori_6, &valor_o_6, &delay_s);
	acc_set_value(ori_7, &valor_o_7, &delay_s);
	acc_set_value(ori_8, &valor_o_8, &delay_s);
	acc_set_value(ori_9, &valor_o_9, &delay_s);
	acc_set_value(ori_10, &valor_o_10, &delay_s);
	acc_set_value(ori_11, &valor_o_11, &delay_s);
	acc_set_value(ori_12, &valor_o_12, &delay_s);
	acc_set_value(ori_13, &valor_o_13, &delay_s);
	acc_set_value(ori_14, &valor_o_14, &delay_s);
	acc_set_value(ori_15, &valor_o_15, &delay_s);
	acc_set_value(ori_16, &valor_o_16, &delay_s);
	acc_set_value(ori_17, &valor_o_17, &delay_s);
	acc_set_value(ori_18, &valor_o_18, &delay_s);
	acc_set_value(ori_19, &valor_o_19, &delay_s);
	acc_set_value(ori_20, &valor_o_20, &delay_s);
	acc_set_value(ori_21, &valor_o_21, &delay_s);
	acc_set_value(ori_22, &valor_o_22, &delay_s);
	acc_set_value(ori_23, &valor_o_23, &delay_s);
	acc_set_value(ori_24, &valor_o_24, &delay_s);
	acc_set_value(ori_25, &valor_o_25, &delay_s);
	acc_set_value(ori_26, &valor_o_26, &delay_s);
	acc_set_value(ori_27, &valor_o_27, &delay_s);
	acc_set_value(ori_28, &valor_o_28, &delay_s);
	acc_set_value(ori_29, &valor_o_29, &delay_s);
	acc_set_value(ori_30, &valor_o_30, &delay_s);
	acc_set_value(ori_31, &valor_o_31, &delay_s);
	acc_set_value(can_0, &valor_c_0, &delay_s);
	acc_set_value(can_1, &valor_c_1, &delay_s);
	acc_set_value(can_2, &valor_c_2, &delay_s);
	acc_set_value(can_3, &valor_c_3, &delay_s);
	acc_set_value(can_4, &valor_c_4, &delay_s);
	acc_set_value(can_5, &valor_c_5, &delay_s);
	acc_set_value(can_6, &valor_c_6, &delay_s);
	acc_set_value(can_7, &valor_c_7, &delay_s);
	acc_set_value(can_8, &valor_c_8, &delay_s);
	acc_set_value(can_9, &valor_c_9, &delay_s);
	acc_set_value(can_10, &valor_c_10, &delay_s);
	acc_set_value(can_11, &valor_c_11, &delay_s);
	acc_set_value(can_12, &valor_c_12, &delay_s);
	acc_set_value(can_13, &valor_c_13, &delay_s);
	acc_set_value(can_14, &valor_c_14, &delay_s);
	acc_set_value(can_15, &valor_c_15, &delay_s);
	acc_set_value(can_16, &valor_c_16, &delay_s);
	acc_set_value(can_17, &valor_c_17, &delay_s);
	acc_set_value(can_18, &valor_c_18, &delay_s);
	acc_set_value(can_19, &valor_c_19, &delay_s);
	acc_set_value(can_20, &valor_c_20, &delay_s);
	acc_set_value(can_21, &valor_c_21, &delay_s);
	acc_set_value(can_22, &valor_c_22, &delay_s);
	acc_set_value(can_23, &valor_c_23, &delay_s);
	acc_set_value(can_24, &valor_c_24, &delay_s);
	acc_set_value(can_25, &valor_c_25, &delay_s);
	acc_set_value(can_26, &valor_c_26, &delay_s);
	acc_set_value(can_27, &valor_c_27, &delay_s);
	acc_set_value(can_28, &valor_c_28, &delay_s);
	acc_set_value(can_29, &valor_c_29, &delay_s);
	acc_set_value(can_30, &valor_c_30, &delay_s);
	acc_set_value(can_31, &valor_c_31, &delay_s);

}

//Rotina responsável por pegar os valores na entrada da SAD em verilog, e utiliza-los como
//entrada para o modelo em C. Posteriormente verifica se o resultado obtido pelo modelo em 
//C confere com o resultado da SAD em verilog.
void out_sad_verilog(){

	p_acc_value value;

	string i_out_sad = acc_fetch_value(out_sad,"%b", value);

	int int_out_sad = converter(i_out_sad, 13);
	
	//Imprime na tela o resultado obtido tanto pela SAD Verilog quanto pela SAD C
	if (int_out_sad != out_sad_c[2]){
		io_printf("*************************ERRO*************************\n");
		io_printf("\nsad_v = %d\nsad_c = %d\n", int_out_sad, out_sad_c[2]);
	}

}

//Função utilizada para converter strings com números bínarios em inteiros
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
