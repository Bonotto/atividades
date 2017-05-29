#include <stdio.h>
#include <vector>
#include <climits>
#include <stdlib.h>
#include <cmath>

//write to file a square block with sizeXsize
//changed just to print 2 first elements
void print2file(FILE* f, std::vector<int> &block){
	for (int value : block) {
		fprintf(f, "%d\n", value);
	}
}

//create a randomized square block with sizeXsize
void create_block(std::vector<int> &block, int size){
	for(int i = 0; i < size; i++){
		block.push_back(rand() % 256);
	}
}

int afd_cost(std::vector<int> &ori, std::vector<int> &can, int n_elements) {
	int total =0;
	for(int i =0; i< n_elements; i++){
		total+=abs(ori[i]-can[i]);
	}
	return total<<3;
}	
// //generate random candidates to a sw me test
void generate_sw(int block_size, int num_tests, FILE* f_ori, FILE* f_can, FILE* f_result){
	

	//generate and evaluate each pair of tests
	for(int i =0; i<num_tests; i++){

		std::vector<int> ori;
		create_block(ori, block_size);
		print2file(f_ori, ori);

		std::vector<int> can;
		create_block(can, block_size);
		print2file(f_can, can);
	
		//calculate result
		int total_cost = afd_cost(ori, can, block_size);
	
		fprintf(f_result, "%d\n", total_cost);
	}

}

int main() {
	//open files
	FILE* file_ori;
	file_ori = fopen("ori.txt","w");
	FILE* file_can;
	file_can = fopen("can.txt","w");
	FILE* file_result;
	file_result = fopen("result.txt","w");

	//test parameters
	int block_size = 2; //max : 12, product of 2
	int num_tests = 100;

	//generate vectors
	generate_sw(block_size, num_tests, file_ori, file_can, file_result);

	// close files
	fclose(file_ori);
	fclose(file_can);
}
