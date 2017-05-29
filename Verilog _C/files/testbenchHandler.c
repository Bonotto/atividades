#define _FILE_OFFSET_BITS 64

#include "acc_user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


/*! 
 *	@brief Defines the type of metric
 *
 * 	@sa SAD, SSD and SATD.
 *
 *	Until now just 3 metrics are calculated by the IP block. To minimize the size of control files and memory usage, the metric_type has been defined as unsigned char.
 */
#define metric_type unsigned char

/*! 
 *	@brief Defines the type of subsampling.
 *
 * 	@sa _1x1, _2x1 and _4x1.
 *
 *	Until now just 3 subsamplings for the IP block. To minimize the size of control files and memory usage, the size_type has been defined as unsigned char.
 */
#define subsampling_type unsigned char

/*! 
 *	@brief Defines the type of metric result.
 *
 *	All metrics must result an positive number. Thus, for large blocks, this value can be high. This way, it is defined with a unsigned long value. 
 */
#define metric_result unsigned long

/*! 
 *	@brief Defines the type of block sizes.
 *
 *
 *	The block sizes (width and height) only varies between 4 and 64. Also are always a positive number.
 */
#define size_type unsigned char

/*! 
 *	@brief Defines the type of pixel.
 *
 *
 *	The pixel values are between 0 and 255.
 */
#define pixel_type unsigned char

 /*! 
 *	@brief Defines the type of counter for the validation file.
 *
 *
 *	As massive tests will be done, the number of those should be represented by a larger positive number.
 */
#define validation_file_entrie_counter_type unsigned long

 /*! 
 *	@brief Defines the code associated with the Sum of Absolute Differences (SAD).
 *
 *	The SAD is calculated by the sum of the absolute value of each pel difference between one original and one candidate block.
 *	The SAD calculation are defined by the following equation: 
 *
 *	\f$ SAD=\sum\limits_{i=0}^M \sum\limits_{j=0}^N | Ori_{i,j} - Dec_{i,j} | \f$
 *
 */
#define SAD 0 

#define UNDEFINED_METRIC 1


 void freeMatrix(int** matrixToFree){
 	int h;
 	for(h=0;h<4;h++){
 		free(matrixToFree[h]);
 	}
 	free(matrixToFree);
 }

 metric_result satd_buffer = 0;
 metric_result satd_buffer2 = 0;
 metric_result satd_buffer3 = 0;
 metric_result satd_buffer4 = 0;
 metric_result satd_final = 0;
 int counter = 0;
 int bool_doneH = 0;
 typedef char * string;

//Declaração dos handles que serão utilizados
//Cada handle carrega informações sobre um objeto especico do design. As informações são
//relativas ao tipo de objeto e tambem sobre onde encontrar dados relativos ao objeto.

 handle valor;
 handle init;
 handle a0;
 handle a1;
 handle a2;
 handle a3;
 handle a4;
 handle a5;
 handle a6;
 handle a7;
 handle a8;
 handle a9;
 handle a10;
 handle a11;
 handle a12;
 handle a13;
 handle a14;
 handle a15;

 handle b0;
 handle b1;
 handle b2;
 handle b3;
 handle b4;
 handle b5;
 handle b6;
 handle b7;
 handle b8;
 handle b9;
 handle b10;
 handle b11;
 handle b12;
 handle b13;
 handle b14;
 handle b15;

 handle ack;
 handle result;
 handle done;

 handle clk;

 size_type initiated = 0;




//void sad();
//void sad_entradas();
 int converter(string in_string, int no_bits);
//unsigned char absdiff(unsigned char a, unsigned char b);

 int getBoolValueFromSignalHandle(handle signal_handle);

 void done_consumer_routine();
 void clock_consumer_routine();

 metric_result satd4x4(pixel_type** pixelsA, pixel_type** pixelsB);

//#############################################
//################# BLOCK #####################
//#############################################

/*!
	\brief The pel blocks.
*/
	typedef struct {
	size_type width;/*!< \brief Indicates the width of the block. 
				
				This value is indicated in pixel.*/

	size_type height;/*!< \brief Indicates the height of the block. 
				
				This value is indicated in pixel.*/

	pixel_type **pixel;/*!< \brief Points to array of pel samples. 
				
				The bi-dimentional pointer indexes the pel samples values. Wich sample is a unsigned char and should be 
				inside the 0..255 range.*/
			} Block;

			typedef struct {
				Block blockA;
				Block blockB;
				metric_result result;
			} SimulationBlock;

/*!
 * \brief Creates a new empty block.
 *
 *	This function creates a new empty block, allocating width*height pixels.
	
	\note Soh pra tentar entender essa tag
 *
 * \param width The width of the new block
 * \param height The height of the new block
 *
 * \sa deleteBlock()
 *
 */
 Block createNewBlock(size_type width, size_type height){
 	Block block = {width, height, 0};

 	block.pixel = malloc(height*sizeof(pixel_type *));

 	size_type h = 0;
 	for(;h < height; h++)
 		block.pixel[h] = malloc(width*sizeof(pixel_type));

 	return block;
 }


/*!
 * \brief Free the allocated block
 *
 *	This function deletes a block.
 *
 * \param Block The block to be deleted.
 *
 * \sa createNewBlock()
 *
 */
 void deleteBlock(Block block){
 	int f = 0;
 	for(;f < block.height; f++)
 		free(block.pixel[f]);
 	free(block.pixel);
 }

//#############################################
//################# BLOCK #####################
//#############################################

 FILE *f;
 SimulationBlock global_simulation_block;

//STATES DECLARATION

 enum st{
 	IDLE, CALC, DONE_ST, T1
 };
 typedef enum st state_type ;

 state_type next_state, current_state;

 void getNext4x4BlockFromFile(){

 	int i, j;
 	for (i = 0;i<4;i++){
 		for (j=0;j<4;j++){
 			fread(&(global_simulation_block.blockA.pixel[j][i]),sizeof(pixel_type),1,f);
 		}
 	}
 	for (i = 0;i<4;i++){
 		for (j=0;j<4;j++){
 			fread(&(global_simulation_block.blockB.pixel[j][i]),sizeof(pixel_type),1,f);
 		}
 	}
 	/*io_printf("\n=======================\n");
 	printMatrix(global_simulation_block.blockA.pixel);
 	io_printf("\n----------\n");
 	printMatrix(global_simulation_block.blockB.pixel);*/

 	satd_final = satd_buffer;
 	satd_buffer = satd_buffer2;
 	satd_buffer2 = satd_buffer3;
 	satd_buffer3 =satd_buffer4; 
 	satd_buffer4 =satd4x4(global_simulation_block.blockA.pixel, global_simulation_block.blockB.pixel); 

 	fread(&(global_simulation_block.result),sizeof(metric_result),1,f);

 }

 void satd_monitor(){

	//Init the environment to use the 'acc' routines.
 	acc_initialize();

	//varible mapping
	//Handle each monitor as called in verilog code.

 	valor = acc_handle_tfarg(1);

	//A rotina acc_vlc_add(object_handle, consumer_routine, user_data, vcl_flag) chama a 
	//consumer_routine sempre que valor do objeto dado pelo object_handle tiver seu valor 
	//lógico alterado.

 	acc_vcl_add(valor,done_consumer_routine,null,vcl_verilog_logic);

	//write_new_line(2);


	//Libera a memória interna utilizada pelas rotinas "acc". 
 	acc_close();

 }


 void set_next_state(int init, int ack, int doneH, state_type current_state, state_type *next){
 	switch (current_state) {
 		case IDLE: {
 			if(init==1)
 				*next = T1;
 		} break;
 		case T1: {
 			if(doneH==1)
 				*next = DONE_ST;
 		} break;
 		case DONE_ST: {
 			if(init == 0)
 				*next = IDLE;
 			if(ack==1 && init==1)
 				*next = CALC;
 		}break;
 		case CALC: {
 			*next = DONE_ST;
 		}break;
 	}
 }

 	void set_current_state(int reset, state_type next, state_type *current){
 		if(reset){
 			*current = IDLE;
 		}
 		else {
 			*current = next;
 		}
 	}

 	void write_new_line(){

 		char driverA0[9];
 		char driverA1[9];
 		char driverA2[9];
 		char driverA3[9];
 		char driverA4[9];
 		char driverA5[9];
 		char driverA6[9];
 		char driverA7[9];
 		char driverA8[9];
 		char driverA9[9];
 		char driverA10[9];
 		char driverA11[9];
 		char driverA12[9];
 		char driverA13[9];
 		char driverA14[9];
 		char driverA15[9];

 		char driverB0[9];
 		char driverB1[9];
 		char driverB2[9];
 		char driverB3[9];
 		char driverB4[9];
 		char driverB5[9];
 		char driverB6[9];
 		char driverB7[9];
 		char driverB8[9];
 		char driverB9[9];
 		char driverB10[9];
 		char driverB11[9];
 		char driverB12[9];
 		char driverB13[9];
 		char driverB14[9];
 		char driverB15[9];

 		getBin(global_simulation_block.blockA.pixel[0][0], driverA0);
 		getBin(global_simulation_block.blockA.pixel[0][1], driverA1);
 		getBin(global_simulation_block.blockA.pixel[0][2], driverA2);
 		getBin(global_simulation_block.blockA.pixel[0][3], driverA3);

 		getBin(global_simulation_block.blockA.pixel[1][0], driverA4);
 		getBin(global_simulation_block.blockA.pixel[1][1], driverA5);
 		getBin(global_simulation_block.blockA.pixel[1][2], driverA6);
 		getBin(global_simulation_block.blockA.pixel[1][3], driverA7);

 		getBin(global_simulation_block.blockA.pixel[2][0], driverA8);
 		getBin(global_simulation_block.blockA.pixel[2][1], driverA9);
 		getBin(global_simulation_block.blockA.pixel[2][2], driverA10);
 		getBin(global_simulation_block.blockA.pixel[2][3], driverA11);

 		getBin(global_simulation_block.blockA.pixel[3][0], driverA12);
 		getBin(global_simulation_block.blockA.pixel[3][1], driverA13);
 		getBin(global_simulation_block.blockA.pixel[3][2], driverA14);
 		getBin(global_simulation_block.blockA.pixel[3][3], driverA15);



 		getBin(global_simulation_block.blockB.pixel[0][0], driverB0);
 		getBin(global_simulation_block.blockB.pixel[0][1], driverB1);
 		getBin(global_simulation_block.blockB.pixel[0][2], driverB2);
 		getBin(global_simulation_block.blockB.pixel[0][3], driverB3);

 		getBin(global_simulation_block.blockB.pixel[1][0], driverB4);
 		getBin(global_simulation_block.blockB.pixel[1][1], driverB5);
 		getBin(global_simulation_block.blockB.pixel[1][2], driverB6);
 		getBin(global_simulation_block.blockB.pixel[1][3], driverB7);

 		getBin(global_simulation_block.blockB.pixel[2][0], driverB8);
 		getBin(global_simulation_block.blockB.pixel[2][1], driverB9);
 		getBin(global_simulation_block.blockB.pixel[2][2], driverB10);
 		getBin(global_simulation_block.blockB.pixel[2][3], driverB11);

 		getBin(global_simulation_block.blockB.pixel[3][0], driverB12);
 		getBin(global_simulation_block.blockB.pixel[3][1], driverB13);
 		getBin(global_simulation_block.blockB.pixel[3][2], driverB14);
 		getBin(global_simulation_block.blockB.pixel[3][3], driverB15);


	//O valor lógico a ser escrito e o delay na propagação deste são colocados em duas
	//estruturas referenciadas pelo seus ponteiros.

	//value_s1 e value_s2 são ponteiros para a structure type s_setval_value
 		s_setval_value value_a0;
 		s_setval_value value_a1;
 		s_setval_value value_a2;
 		s_setval_value value_a3;
 		s_setval_value value_a4;
 		s_setval_value value_a5;
 		s_setval_value value_a6;
 		s_setval_value value_a7;
 		s_setval_value value_a8;
 		s_setval_value value_a9;
 		s_setval_value value_a10;
 		s_setval_value value_a11;
 		s_setval_value value_a12;
 		s_setval_value value_a13;
 		s_setval_value value_a14;
 		s_setval_value value_a15;

 		s_setval_value value_b0;
 		s_setval_value value_b1;
 		s_setval_value value_b2;
 		s_setval_value value_b3;
 		s_setval_value value_b4;
 		s_setval_value value_b5;
 		s_setval_value value_b6;
 		s_setval_value value_b7;
 		s_setval_value value_b8;
 		s_setval_value value_b9;
 		s_setval_value value_b10;
 		s_setval_value value_b11;
 		s_setval_value value_b12;
 		s_setval_value value_b13;
 		s_setval_value value_b14;
 		s_setval_value value_b15;

	//delay_s é um ponteiro para a structure type s_setval_delay
 		s_setval_delay delay_s;

	//Defini-se que o formato em que será fornecido os valores para serem
	//colocados na entrada da SAD são strings de decimais
 		value_a0.format = accBinStrVal;
 		value_a1.format = accBinStrVal;
 		value_a2.format = accBinStrVal;
 		value_a3.format = accBinStrVal;
 		value_a4.format = accBinStrVal;
 		value_a5.format = accBinStrVal;
 		value_a6.format = accBinStrVal;
 		value_a7.format = accBinStrVal;
 		value_a8.format = accBinStrVal;
 		value_a9.format = accBinStrVal;
 		value_a10.format = accBinStrVal;
 		value_a11.format = accBinStrVal;
 		value_a12.format = accBinStrVal;
 		value_a13.format = accBinStrVal;
 		value_a14.format = accBinStrVal;
 		value_a15.format = accBinStrVal;



 		value_b0.format = accBinStrVal;
 		value_b1.format = accBinStrVal;
 		value_b2.format = accBinStrVal;
 		value_b3.format = accBinStrVal;
 		value_b4.format = accBinStrVal;
 		value_b5.format = accBinStrVal;
 		value_b6.format = accBinStrVal;
 		value_b7.format = accBinStrVal;
 		value_b8.format = accBinStrVal;
 		value_b9.format = accBinStrVal;
 		value_b10.format = accBinStrVal;
 		value_b11.format = accBinStrVal;
 		value_b12.format = accBinStrVal;
 		value_b13.format = accBinStrVal;
 		value_b14.format = accBinStrVal;
 		value_b15.format = accBinStrVal;

	//Defini-se que não haverá delay na propagação
 		delay_s.model = accNoDelay;

 		value_a0.value.str = driverA0;
 		value_a1.value.str = driverA1;
 		value_a2.value.str = driverA2;
 		value_a3.value.str = driverA3;
 		value_a4.value.str = driverA4;
 		value_a5.value.str = driverA5;
 		value_a6.value.str = driverA6;
 		value_a7.value.str = driverA7;
 		value_a8.value.str = driverA8;
 		value_a9.value.str = driverA9;
 		value_a10.value.str = driverA10;
 		value_a11.value.str = driverA11;
 		value_a12.value.str = driverA12;
 		value_a13.value.str = driverA13;
 		value_a14.value.str = driverA14;
 		value_a15.value.str = driverA15;

 		value_b0.value.str = driverB0;
 		value_b1.value.str = driverB1;
 		value_b2.value.str = driverB2;
 		value_b3.value.str = driverB3;
 		value_b4.value.str = driverB4;
 		value_b5.value.str = driverB5;
 		value_b6.value.str = driverB6;
 		value_b7.value.str = driverB7;
 		value_b8.value.str = driverB8;
 		value_b9.value.str = driverB9;
 		value_b10.value.str = driverB10;
 		value_b11.value.str = driverB11;
 		value_b12.value.str = driverB12;
 		value_b13.value.str = driverB13;
 		value_b14.value.str = driverB14;
 		value_b15.value.str = driverB15;

	//Escreve nos reg e1 e e2
 		acc_set_value(a0, &value_a0, &delay_s);
 		acc_set_value(a1, &value_a1, &delay_s);
 		acc_set_value(a2, &value_a2, &delay_s);
 		acc_set_value(a3, &value_a3, &delay_s);
 		acc_set_value(a4, &value_a4, &delay_s);
 		acc_set_value(a5, &value_a5, &delay_s);
 		acc_set_value(a6, &value_a6, &delay_s);
 		acc_set_value(a7, &value_a7, &delay_s);
 		acc_set_value(a8, &value_a8, &delay_s);
 		acc_set_value(a9, &value_a9, &delay_s);
 		acc_set_value(a10, &value_a10, &delay_s);
 		acc_set_value(a11, &value_a11, &delay_s);
 		acc_set_value(a12, &value_a12, &delay_s);
 		acc_set_value(a13, &value_a13, &delay_s);
 		acc_set_value(a14, &value_a14, &delay_s);
 		acc_set_value(a15, &value_a15, &delay_s);


 		acc_set_value(b0, &value_b0, &delay_s);
 		acc_set_value(b1, &value_b1, &delay_s);
 		acc_set_value(b2, &value_b2, &delay_s);
 		acc_set_value(b3, &value_b3, &delay_s);
 		acc_set_value(b4, &value_b4, &delay_s);
 		acc_set_value(b5, &value_b5, &delay_s);
 		acc_set_value(b6, &value_b6, &delay_s);
 		acc_set_value(b7, &value_b7, &delay_s);
 		acc_set_value(b8, &value_b8, &delay_s);
 		acc_set_value(b9, &value_b9, &delay_s);
 		acc_set_value(b10, &value_b10, &delay_s);
 		acc_set_value(b11, &value_b11, &delay_s);
 		acc_set_value(b12, &value_b12, &delay_s);
 		acc_set_value(b13, &value_b13, &delay_s);
 		acc_set_value(b14, &value_b14, &delay_s);
 		acc_set_value(b15, &value_b15, &delay_s);

	/*s_setval_value ack_value;
	s_setval_delay ack_delay;
	ack_value.format = accBinStrVal;
	ack_delay.model = accNoDelay;
	ack_value.value.str = "0";
	acc_set_value(ack, &ack_value, &ack_delay);*/

}

void clock_consumer_routine(){

	int bool_init = getBoolValueFromSignalHandle(init);

	if (bool_init)
	{
		int bool_ack = getBoolValueFromSignalHandle(ack);
				//(int init, int ack, int doneH, state_type current_state, state_type *next
		set_next_state(bool_init, bool_ack,bool_doneH, current_state, &next_state);

		int bool_clk = getBoolValueFromSignalHandle(clk);

		if(bool_clk){
			set_current_state(0,next_state,&current_state);
			if(current_state == T1){
				counter++;
			}
			else{
				counter = 0;
			}
		}else{
			//write data
			if(counter>=4){
				bool_doneH = 1;
			}
			if ((current_state == IDLE)||(current_state == T1) ||(current_state == CALC) ){
				getNext4x4BlockFromFile();
				write_new_line();//0,1,2,3
			}
		}
	}

}

void done_consumer_routine(){

	io_printf("Hello World\n");

}



void getBin(unsigned char num, char *str){
	*(str+8) = '\0';
	int mask = 0x10 << 4;
	while(mask >>= 1)
		*str++ = !!(mask & num) + '0';
}

int getBoolValueFromSignalHandle(handle signal_handle){
	//Declaração dos argumentos necessários para utilizar acc_fetch_value
	p_acc_value value;

	string fetchedSignalHandle = acc_fetch_value(signal_handle,"%b", value);
	string zero = "0";

	if(strcmp(fetchedSignalHandle, zero)){
		return 1;
	}
	return 0;
}

/*void sad_entradas(){
	

	//Declaração dos argumentos necessários para utilizar acc_fetch_value
	p_acc_value value;
	
	//Faz a leitura dos reg e1 e e2 e da net result nas strings i_e1, i_e2
	//e i_result respectivamente
	string fetchedCalc = acc_fetch_value(calc,"%b", value);
	string zero = "0";

	if(strcmp(fetchedCalc, zero)){
		//Atribui-se um valor do arquivo para cada uma das strings
		if(line != 4 && gollumn != 4){
			char driverA[9];
			char driverB[9];
			getBin(global_simulation_block.blockA.pixel[line][gollumn], driverA);
			getBin(global_simulation_block.blockB.pixel[line][gollumn], driverB);
			gollumn++;
			if (gollumn == 4)
			{
				line++;
				gollumn = 0;
			}
		

		
			//O valor lógico a ser escrito e o delay na propagação deste são colocados em duas
			//estruturas referenciadas pelo seus ponteiros.
			
			//value_s1 e value_s2 são ponteiros para a structure type s_setval_value
			s_setval_value value_s1;
			s_setval_value value_s2;
			
			//delay_s é um ponteiro para a structure type s_setval_delay
			s_setval_delay delay_s;
			
			//Defini-se que o formato em que será fornecido os valores para serem
			//colocados na entrada da SAD são strings de decimais
			value_s1.format = accBinStrVal;
			value_s2.format = accBinStrVal;
			
			//Defini-se que não haverá delay na propagação
			delay_s.model = accNoDelay;
			
			value_s1.value.str = driverA;
			value_s2.value.str = driverB;
			
			//Escreve nos reg e1 e e2
			acc_set_value(e1, &value_s1, &delay_s);
			acc_set_value(e2, &value_s2, &delay_s);


		}
	}

}*/

	unsigned char absdiff(unsigned char a, unsigned char b){
		if(a > b)
			return a-b;
		return b-a;
	}

	void printMatrix(unsigned char **matrix){
		int i = 0;
		int j;
		for (; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				io_printf("%d \t", matrix[i][j]);
			}
			io_printf("\n");
		}
		io_printf("\n");
	}

/*void sad(){
	
	//Declaração dos argumentos necessários para utilizar acc_fetch_value
	p_acc_value value;
	
	string fetchedDONE = acc_fetch_value(done,"%b", value);
	string zero = "0";

	if(strcmp(fetchedDONE, zero)){

		//Faz a leitura dos reg e1 e e2 e da net result nas strings i_e1, i_e2
		//e i_result respectivamente
		string i_result = acc_fetch_value(result,"%b", value);

		//Converte-se o valor binário nas string i_e1, e i_e2 para valores inteiros
		//decimais. É importante observar que ambas as strings i_e1 e i_e2 carregam
		//entradas com 128 bits(16 pixels com 8 bits), e para fazer o cálculo da SAD
		//precisamos destes 32 valores separados, por isso é criado dois arrays de 
		//inteiros.
		
		int int_result;
		int_result = converter(i_result,12);
		
		//Calcula a SAD pelo modelo em C. A variável "sad_total" irá carregar o resultado
		//do cálculo.
		metric_result sad_total = 0;
		int i = 0;
		int j = 0;
		
		//io_printf("\n######################BEGIN#######################\n");

		//printMatrix(inputA);
		//printMatrix(inputB);

		for (; i < 4; i++)
		{
			for (j=0; j < 4; j++)
			{
				sad_total+=absdiff(global_simulation_block.blockA.pixel[i][j], global_simulation_block.blockB.pixel[i][j]);
			}
		}		
		
		if (int_result != sad_total){
			io_printf("Error\n");
		//} else {
		//	io_printf("0");
		}

		line=0;
		gollumn=0;
		getNext4x4BlockFromFile();


		s_setval_value ack_value;
		s_setval_delay ack_delay;
		ack_value.format = accBinStrVal;
		ack_delay.model = accNoDelay;
		ack_value.value.str = "1";
		acc_set_value(ack, &ack_value, &ack_delay);
	}

}*/

//Função utilizada para converter strings com números bínarios em inteiros 
	int converter (string in_string, int no_bits){

		int conv = 0;
		int i = 0;
		int j = 0;
		int bin = 0;

		for (i=no_bits-1; i>=0; i=i-1){
			if(*(in_string+i) == 49){
				bin = 1;
			} else if(*(in_string+i) == 120){
				io_printf("%d, Warning : X detected\n");
				bin = 0;
			} else if (*(in_string+i) == 122){
				io_printf("%d, Warning : Z detected\n");
			} else {
				bin = 0;
			}
			conv = conv + (1 << j)*bin;
			j ++;
		}
		return conv;
	}

//SATD
//
//
//

	inline void __attribute__ ((always_inline)) oneDHadamard(int *a, int *b, int *c, int *d){
		int i = *a+*b;
		int j = *c+*d;
		int k = *a-*b;
		int l = *c-*d;
		*a = i+j;
		*b = i-j;
		*c = k-l;
		*d = k+l;
	}

#define ONE_D_HADAMARD_FIRST(I) oneDHadamard(&(diff[0][I]), &(diff[1][I]), &(diff[2][I]), &(diff[3][I]))
#define ONE_D_HADAMARD_SECOND(I) oneDHadamard(&(diff[I][0]), &(diff[I][1]), &(diff[I][2]), &(diff[I][3]))


	void hadamard4x4(int **diff){
		ONE_D_HADAMARD_FIRST(0);
		ONE_D_HADAMARD_FIRST(1);
		ONE_D_HADAMARD_FIRST(2);
		ONE_D_HADAMARD_FIRST(3);
		ONE_D_HADAMARD_SECOND(0);
		ONE_D_HADAMARD_SECOND(1);
		ONE_D_HADAMARD_SECOND(2);
		ONE_D_HADAMARD_SECOND(3);
	}

	metric_result satd4x4(pixel_type** pixelsA, pixel_type** pixelsB){
		int **diff = malloc(4*sizeof(int*));
		int i = 0;
		for ( ; i < 4; i++)
		{
			diff[i]=malloc(4*sizeof(int));
		}
		i = 0;
		int j;
		for (; i < 4; i++)
		{
			j = 0;
			for ( ; j < 4; j++)
			{
				diff[i][j]=(int)(pixelsA[i][j]-pixelsB[i][j]);
			}
		}
		hadamard4x4(diff);
		metric_result satd = 0;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (diff[i][j] > 0)
				{
					satd+=diff[i][j];
				}else{
					satd-=diff[i][j];
				}
			}
		}
		freeMatrix(diff);
		return satd >> 1;
	}