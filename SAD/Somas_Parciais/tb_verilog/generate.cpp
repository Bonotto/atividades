#include <stdio.h>
#include <vector>
#include <climits>
#include <stdlib.h>
#include <cmath>

//write to file a square block with sizeXsize
//changed just to print 2 first elements
void print2file(FILE* f, std::vector<int> & block){
	for(int value : block) {
		fprintf(f, "%d\n", value);
	}
}

//create a randomized square block with sizeXsize
void create_block(std::vector<int> & block, int size){
	for(int i = 0; i < size; i++){
		block.push_back(rand() % 256);
	}
}

int sad(std::vector<int> & ori, std::vector<int> & can, int size) {
	int total = 0;
	for(int i = 0; i < size; i++){
		total += abs(ori[i] - can[i]);
	}
	return total;
}	
// //generate random candidates to a sw me test
void generate_sw(int block_size, int num_tests, FILE* f_ori, FILE* f_can, FILE* f_result){
	

	//generate and evaluate
	for(int i = 0; i < num_tests; i++){

		std::vector<int> ori;
		create_block(ori, block_size);
		print2file(f_ori, ori);

		std::vector<int> can;
		create_block(can, block_size);
		print2file(f_can, can);
	
		//calculate result
		int results = sad(ori, can, block_size);
	
		fprintf(f_result, "%d\n", results);
	}

}

int main() {
	//open files
	FILE* f_ori;
	f_ori = fopen("ori.txt","w");
	FILE* f_can;
	f_can = fopen("can.txt","w");
	FILE* f_result;
	f_result = fopen("result.txt","w");

	//test parameters
	int block_size = 32;
	int num_tests = 1000;

	//generate vectors
	generate_sw(block_size, num_tests, f_ori, f_can, f_result);

	// close files
	fclose(f_ori);
	fclose(f_can);
	fclose(f_result);
}
