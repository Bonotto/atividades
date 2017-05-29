/**
* @file
* @Author: ismaelseidel
* @Date:   2016-08-10 21:42:43
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-10 21:42:52
*/

#include "cuif_v1.h"

cuif_2d_image_t* cuif_v1_new_from_bitmap(bitmap_t* bitmap)
{
	if (bitmap == NULL)
	{
		fprintf(stderr, _("Error: Cannot create a new CUIF V1 from a NULL bitmap!\n"));
		return NULL;
	}

	uint32_t width = bitmap->header.width;
	uint8_t padding = width % 4;
	uint32_t height = bitmap->header.height;
	cuif_2d_image_t* cuif_v1 = cuif_2d_image_new(CUI_V1_ID, 3, width, height);

	size_t i, j, pixel_index=0;

	for(j=0;j<height;j++){
		for(i=0;i<width;i++)
		{
			cuif_v1->pixel_array[CUI_V1_RED]  [i][j] = bitmap->bgr_pixel_array[pixel_index++];
			cuif_v1->pixel_array[CUI_V1_GREEN][i][j] = bitmap->bgr_pixel_array[pixel_index++];
			cuif_v1->pixel_array[CUI_V1_BLUE] [i][j] = bitmap->bgr_pixel_array[pixel_index++];
			
		}
		for(i=0;i<padding;i++)
		{
			pixel_index++;
		}
	}

	return cuif_v1;
}

bitmap_t* cuif_v1_convert_to_bitmap(cuif_2d_image_t* cuif_v1)
{
	if (cuif_v1 == NULL)
	{
		fprintf(stderr, _("Error: Cannot convert a NULL CUIF V1 to bitmap!\n"));
		return NULL;
	}

	uint32_t width = cuif_v1->header.width;
	uint8_t padding = width % 4;
	uint32_t height = cuif_v1->header.height;
	
	bitmap_t* bitmap = bitmap_new();
	if (bitmap == NULL)
	{
		fprintf(stderr, _("Error: Cannot create a new bitmap!\n"));
		return NULL;
	}

	bitmap->header.width = width;
	bitmap->header.height = height;
	bitmap->header.number_of_bits_per_pixel = 24;

	bitmap->bgr_pixel_array = (uint8_t*) malloc(3*height*(width+padding)*sizeof(uint8_t));

	size_t i, j, pixel_index=0;

	for(j=0;j<height;j++){
		for(i=0;i<width;i++)
		{
			bitmap->bgr_pixel_array[pixel_index++] = cuif_v1->pixel_array[CUI_V1_BLUE] [i][j];
			bitmap->bgr_pixel_array[pixel_index++] = cuif_v1->pixel_array[CUI_V1_GREEN][i][j];
			bitmap->bgr_pixel_array[pixel_index++] = cuif_v1->pixel_array[CUI_V1_RED]  [i][j];
		}
		for(i=0;i<padding;i++)
		{
			bitmap->bgr_pixel_array[pixel_index++] = 0;
		}
	}

	return bitmap;
}

