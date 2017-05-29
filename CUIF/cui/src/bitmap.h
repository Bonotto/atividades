#ifndef BITMAP_H__
#define BITMAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include <string.h>
#include <errno.h>


//http://www.fastgraph.com/help/bmp_header_format.html
/*
#-----------#-----------#-----------------------------------------------------------#
|	offset	|	size	|						description							|
#-----------#-----------#-----------------------------------------------------------#
|	0		|	2		|	signature, must be 4D42 hex								|
|	2		|	4		|	size of BMP file in bytes (unreliable)					|
|	6		|	2		|	reserved, must be zero									|
|	8		|	2		|	reserved, must be zero									|
|	10		|	4		|	offset to start of image data in bytes 					|
|	14		|	4		|	size of BITMAPINFOHEADER structure, must be 40			|
|	18		|	4		|	image width in pixels									|
|	22		|	4		|	image height in pixels									|
|	26		|	2		|	number of planes in the image, must be 1				|
|	28		|	2		|	number of bits per pixel (1, 4, 8, or 24)				|
|	30		|	4		|	compression type (0=none, 1=RLE-8, 2=RLE-4)				|
|	34		|	4		|	size of image data in bytes (including padding)			|
|	38		|	4		|	horizontal resolution in pixels per meter (unreliable)	|
|	42		|	4		|	vertical resolution in pixels per meter (unreliable)	|
|	46		|	4		|	number of colors in image, or zero						|
|	50		|	4		|	number of important colors, or zero						|
#-----------#-----------#-----------------------------------------------------------#
*/

#define BITMAP_HEADER_COMMON_SIZE 54
#define BITMAP_SIGNATURE 19778

//the signature is not a part of the header for aligment reasons.
typedef struct {
	uint32_t size_of_bitmap_file; 			//2
	uint32_t reserved;					//6
	uint32_t offset_to_start_image;			//10
	uint32_t size_of_header; //must be 40	//14
	uint32_t width;
	uint32_t height;
	uint16_t number_of_planes;
	uint16_t number_of_bits_per_pixel;
	uint32_t compression_type;
	uint32_t size_of_image_in_bytes;
	uint32_t horizontal_pixels_per_meter;
	uint32_t vertical_pixels_per_meter;
	uint32_t number_of_colors;
	uint32_t number_of_important_colors;
} bitmap_header_t;

typedef struct {
	bitmap_header_t header;
	uint8_t* bgr_pixel_array;
} bitmap_t;



bitmap_t* bitmap_new();

void bitmap_free(bitmap_t* bitmap);

#endif