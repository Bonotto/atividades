#include <string>
#include <stdio.h>

int main() {

	for (int i = 0; i < 32; i++){
		printf("can_%d = acc_handle_tfarg(%d);\n", i, i+34);
	}

}