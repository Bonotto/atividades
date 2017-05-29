/**
* @file
* @brief {briefing of this file}
* @author: ismaelseidel
* @date:   2016-08-29 17:14:24
* @last Modified by:   ismaelseidel
* @last Modified time: 2016-08-29 19:11:52
*/

#include "color_spaces_test.h"



/*
Rec. ITU-R BT.601-7, p.3

							Table 1
						Signal values
-------------------------------------------------------------
Condition	Red		Green	Blue	Y 		Pr		Pb
-------------------------------------------------------------
White		1.0		1.0		1.0		1.0		0		0
Black		0		0		0		0		0		0
-------------------------------------------------------------
Red			1.0		0		0		.299	-0.701	-0.299
Green		0		1.0		0		.587	-0.587	-0.587
Blue		0		0		1.0		.114	-0.114	.886
-------------------------------------------------------------
Yellow		1.0		1.0		0		.886	.114	-0.886
Cyan		0		1.0		1.0		.701	-0.701	.299
Magenta		1.0		0		1.0		.413	.587	.587
-------------------------------------------------------------

The above table, presents the values before normalization of Pb and Pr.

							Table 2
		Expected signal values after normalization
-------------------------------------------------------------
Condition	Red		Green	Blue	Y 		Cb		Cr
-------------------------------------------------------------
White		1.0		1.0		1.0		1.0		0		0
Black		0		0		0		0		0		0
-------------------------------------------------------------
Red			1.0		0		0		.299	-0.169	0.500
Green		0		1.0		0		.587	-0.331	-0.419
Blue		0		0		1.0		.114	0.500	-0.081
-------------------------------------------------------------
Yellow		1.0		1.0		0		.886	-0.500	0.081
Cyan		0		1.0		1.0		.701	0.169	-0.500
Magenta		1.0		0		1.0		.413	0.331	0.419
-------------------------------------------------------------


*/


void test_color_double(	double r, 
						double g, 
						double b,
						double * const y, 
						double * const cb, 
						double * const cr)
{
	bt601_rgb_to_ycbcr_double(r, g, b, y, cb, cr);
	printf("R: %4.3f\tG:%4.3f\t\tB:%4.3f\t\tY: %4.3f\tCb: %4.3f\tCr: %4.3f\n", r, g, b, *y, *cb, *cr);

	double r_inv, g_inv, b_inv;

	bt601_ycbcr_to_rgb_double(*y, *cb, *cr, &r_inv, &g_inv, &b_inv);
	printf("\tR: %4.3f\tG:%4.3f\t\tB:%4.3f\t(inverse)\n", r_inv, g_inv, b_inv);
}

void test_color(uint8_t r, 
				uint8_t g, 
				uint8_t b,
				uint8_t * const y, 
				uint8_t * const cb, 
				uint8_t * const cr)
{
	bt601_rgb_to_ycbcr (r, g, b, y, cb, cr);
	printf("R: %u\tG:%u\t\tB:%u\t\tY: %u\tCb: %u\tCr: %u\n", r, g, b, *y, *cb, *cr);

	uint8_t r_inv, g_inv, b_inv;

	bt601_ycbcr_to_rgb (*y, *cb, *cr, &r_inv, &g_inv, &b_inv);
	printf("\tR: %u\tG:%u\t\tB:%u\t(inverse)\n", r_inv, g_inv, b_inv);

}


void color_space_test()
{


	uint8_t y_uint8_t;
	uint8_t cb_uint8_t;
	uint8_t cr_uint8_t;


	printf("\n#################################################################\n");
	printf("Testing Color Space conversions BT.601 (uint8_t):\n");

	printf("=================================================================\n");
	
	printf("\nWhite:\t");
	test_color(255,255,255, &y_uint8_t, &cb_uint8_t, &cr_uint8_t);
	printf("----------------------------------------------------------------\n");
	printf("Black:\t");
	test_color(0,0,0, &y_uint8_t, &cb_uint8_t, &cr_uint8_t);

	printf("=================================================================\n");

	printf("\nRed:\t");
	test_color(255,0,0, &y_uint8_t, &cb_uint8_t, &cr_uint8_t);
	printf("----------------------------------------------------------------\n");
	printf("\nGreen:\t");
	test_color(0,255,0, &y_uint8_t, &cb_uint8_t, &cr_uint8_t);
	printf("----------------------------------------------------------------\n");
	printf("\nBlue:\t");
	test_color(0,0,255, &y_uint8_t, &cb_uint8_t, &cr_uint8_t);


	printf("=================================================================\n");

	printf("\nYellow:\t");
	test_color(255,255,0, &y_uint8_t, &cb_uint8_t, &cr_uint8_t);
	printf("----------------------------------------------------------------\n");
	printf("\nCyan:\t");
	test_color(0,255,255, &y_uint8_t, &cb_uint8_t, &cr_uint8_t);
	printf("----------------------------------------------------------------\n");
	printf("\nMagen.:\t");
	test_color(255,0,255, &y_uint8_t, &cb_uint8_t, &cr_uint8_t);

	printf("#################################################################\n");


	double y_double;
	double cb_double;
	double cr_double;


	printf("#################################################################\n");
	printf("Testing Color Space conversions BT.601 (double):\n");

	printf("=================================================================\n");
	
	printf("\nWhite:\t");
	test_color_double(1.0,1.0,1.0, &y_double, &cb_double, &cr_double);
	printf("----------------------------------------------------------------\n");
	printf("Black:\t");
	test_color_double(0.0,0.0,0.0, &y_double, &cb_double, &cr_double);

	printf("=================================================================\n");

	printf("\nRed:\t");
	test_color_double(1.0,0.0,0.0, &y_double, &cb_double, &cr_double);
	printf("----------------------------------------------------------------\n");
	printf("\nGreen:\t");
	test_color_double(0.0,1.0,0.0, &y_double, &cb_double, &cr_double);
	printf("----------------------------------------------------------------\n");
	printf("\nBlue:\t");
	test_color_double(0.0,0.0,1.0, &y_double, &cb_double, &cr_double);


	printf("=================================================================\n");

	printf("\nYellow:\t");
	test_color_double(1.0,1.0,0.0, &y_double, &cb_double, &cr_double);
	printf("----------------------------------------------------------------\n");
	printf("\nCyan:\t");
	test_color_double(0.0,1.0,1.0, &y_double, &cb_double, &cr_double);
	printf("----------------------------------------------------------------\n");
	printf("\nMagen.:\t");
	test_color_double(1.0,0.0,1.0, &y_double, &cb_double, &cr_double);

	printf("#################################################################\n");




}