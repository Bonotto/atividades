#include <string>
#include <stdio.h>

int main() {

	for (int i = 0; i < 32; i++){
		printf(".can_%d(can_%d);\n", i, i);
	}

}