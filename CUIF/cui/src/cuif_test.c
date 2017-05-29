/**
* @file
* @Author: ismaelseidel
* @Date:   2016-08-10 18:22:02
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-10 21:52:26
*/

#include "cuif_test.h"


void test_cuif_2d_rgb_writing()
{
	printf(_("Testing CUIF V1 RGB!\n\n"));

	cuif_2d_image_t* red = 	 cuif_2d_image_new(CUI_V1_ID, 3, 5, 5);
	cuif_2d_image_t* green = cuif_2d_image_new(CUI_V1_ID, 3, 5, 5);
	cuif_2d_image_t* blue =  cuif_2d_image_new(CUI_V1_ID, 3, 5, 5);

	size_t i,j;

	for(i=0;i<5;i++){
		for(j=0;j<5;j++)
		{
			red->pixel_array[CUI_V1_RED][i][j] = 255;
			green->pixel_array[CUI_V1_GREEN][i][j] = 255;
			blue->pixel_array[CUI_V1_BLUE][i][j] = 255;
		}
	}

	cuif_2d_write_to_file(red, "test_red.cuif");
	cuif_2d_write_to_file(green, "test_green.cuif");
	cuif_2d_write_to_file(blue, "test_blue.cuif");

	cuif_2d_image_free(red);
	cuif_2d_image_free(green);
	cuif_2d_image_free(blue);

	red = cuif_2d_read_from_file("test_red.cuif", true);
	printf(_("Red pixels:\n"));
	for(i=0;i<5;i++){
		for(j=0;j<5;j++)
		{
			printf("(%u, %u, %u)\t", red->pixel_array[CUI_V1_RED][i][j], red->pixel_array[CUI_V1_GREEN][i][j], red->pixel_array[CUI_V1_BLUE][i][j]);
		}
		printf("\n");
	}
	printf("\n");

	green = cuif_2d_read_from_file("test_green.cuif", true);
	printf(_("Green pixels:\n"));
	for(i=0;i<5;i++){
		for(j=0;j<5;j++)
		{
			printf("(%u, %u, %u)\t", green->pixel_array[CUI_V1_RED][i][j], green->pixel_array[CUI_V1_GREEN][i][j], green->pixel_array[CUI_V1_BLUE][i][j]);
		}
		printf("\n");
	}
	printf("\n");

	blue = cuif_2d_read_from_file("test_blue.cuif", true);
	printf(_("Blue pixels:\n"));
	for(i=0;i<5;i++){
		for(j=0;j<5;j++)
		{
			printf("(%u, %u, %u)\t", blue->pixel_array[CUI_V1_RED][i][j], blue->pixel_array[CUI_V1_GREEN][i][j], blue->pixel_array[CUI_V1_BLUE][i][j]);
		}
		printf("\n");
	}
	printf("\n");	

	cuif_2d_image_free(red);
	cuif_2d_image_free(green);
	cuif_2d_image_free(blue);

	printf(_("End Test: CUIF V1 RGB\n"));
}

void test_cuif_2d_bitmap_conversion()
{
	printf(_("Testing CUIF 2D V1 from bitmap\n"));
	bitmap_t* bitmap_from_file = bitmap_read_from_file("lena.bmp", false);

	cuif_2d_image_t* cuif_from_bitmap = cuif_v1_new_from_bitmap(bitmap_from_file);

	cuif_2d_write_to_file(cuif_from_bitmap, "lena_cuifv1.cuif");


	bitmap_free(bitmap_from_file);
	printf(_("Converting cuif v1 to bitmap\n"));
	bitmap_from_file = cuif_v1_convert_to_bitmap(cuif_from_bitmap);
	printf(_("Freeing the cuif v1\n"));
	cuif_2d_image_free(cuif_from_bitmap);

	bitmap_write_to_file(bitmap_from_file, "lena_from_cuif.bmp");

	bitmap_free(bitmap_from_file);
}