/**
* @file 
* @Author: ismaelseidel
* @Date:   2016-08-10 21:56:11
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-11 19:13:28
*/

#include "bitmap.h"

/**
 * @brief      Creates a new bitmap (through (m)alloc)
 *
 * @return     The newly (m)allocated bitmap, with a all zeroed header and NULL pixel array
 */
bitmap_t* bitmap_new()
{
	bitmap_t* bitmap = (bitmap_t*) malloc(sizeof(bitmap_t));
	if (bitmap == NULL)
	{
		fprintf(stderr, "Error: Something went wrong when trying to (m)allocate the new bitmap!\n");
		return NULL;
	}
	bitmap->header.size_of_bitmap_file=0;
	bitmap->header.reserved=0;
	bitmap->header.offset_to_start_image=BITMAP_HEADER_COMMON_SIZE;
	bitmap->header.size_of_header=40;
	bitmap->header.width=0;
	bitmap->header.height=0;
	bitmap->header.number_of_planes=1;
	bitmap->header.number_of_bits_per_pixel=0;
	bitmap->header.compression_type=0;
	bitmap->header.size_of_image_in_bytes=0;
	bitmap->header.horizontal_pixels_per_meter=0;
	bitmap->header.vertical_pixels_per_meter=0;
	bitmap->header.number_of_colors=0;
	bitmap->header.number_of_important_colors=0;
	bitmap->bgr_pixel_array = NULL;
	return bitmap;
}

/**
 * @brief      This function frees the bitmap from the memory
 *
 * @param      bitmap  Pointer to the bitmap that should be freed
 */
void bitmap_free(bitmap_t* bitmap)
{
	free(bitmap->bgr_pixel_array);
	free(bitmap);
}
