/**
* @file
* @Author: ismaelseidel
* @Date:   2016-08-09 15:28:48
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-10 21:34:10
*/

#include "cuif_2d.h"

/**
 * @brief      Creates a new 2d cuif
 *
 * @param[in]  width   The width
 * @param[in]  height  The height
 *
 * @return     A pointer to the recently created 2d cuif
 */
cuif_2d_image_t* cuif_2d_image_new(uint8_t version, uint8_t channels, uint32_t width, uint32_t height)
{
	cuif_2d_image_t* image = (cuif_2d_image_t*) malloc(sizeof(cuif_2d_image_t));
	
	cuif_init_header(&image->header, version, channels, width, height);

	image->pixel_array = (uint8_t***) malloc (channels*sizeof(uint8_t**));

	size_t i, j, k;

	for(k=0;k<channels;k++)
	{
		image->pixel_array[k] = (uint8_t**) malloc (width*sizeof(uint8_t*));
		for(i=0;i<width;i++)
		{
			image->pixel_array[k][i] = (uint8_t*) malloc (height*sizeof(uint8_t));
			for(j=0;j<height;j++){ //makes the image black
				image->pixel_array[k][i][j] = 0;	
			}
		}
	}

	return image;
}

cuif_2d_image_t* cuif_2d_image_new_with_header(cuif_header_t* header)
{
	cuif_2d_image_t* image = cuif_2d_image_new(header->version, header->channels, header->width, header->height);
	image->header.signature = header->signature;
	image->header.number_of_students = header->number_of_students;
	return image;
}


/**
 * @brief      Frees the (m)allocated memory
 *
 * @param      cuif_2d_image  The cuif 2 d image
 */
void cuif_2d_image_free(cuif_2d_image_t* cuif_2d_image)
{
	size_t k, i;
	for(k=0;k<cuif_2d_image->header.channels;k++)
	{
		for(i=0;i<cuif_2d_image->header.width;i++)
		{
			free(cuif_2d_image->pixel_array[k][i]);
		}
		free(cuif_2d_image->pixel_array[k]);
	}
	free(cuif_2d_image->header.student_id);
	free(cuif_2d_image);
}