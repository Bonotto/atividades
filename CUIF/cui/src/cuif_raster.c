/**
* @file
* @Author: ismaelseidel
* @Date:   2016-08-09 15:28:50
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-10 21:49:09
*/

#include "cuif_raster.h"

cuif_raster_image_t* cuif_raster_image_new(uint8_t version, uint8_t channels, uint32_t width, uint32_t height)
{
	cuif_raster_image_t* image = (cuif_raster_image_t*) malloc(sizeof(cuif_raster_image_t));
	
	cuif_init_header(&image->header, version, channels, width, height);

	image->pixel_array = (uint8_t**) malloc(channels*sizeof(uint8_t*));

	size_t number_of_pixels_per_channel = width*height;

	size_t k, i;
	for(k=0;k<channels;k++)
	{
		image->pixel_array[k] = (uint8_t*) malloc(number_of_pixels_per_channel*sizeof(uint8_t));
		for(i=0;i<number_of_pixels_per_channel;i++)
		{
			image->pixel_array[k][i] = 0;
		}
	}

	return image;
}