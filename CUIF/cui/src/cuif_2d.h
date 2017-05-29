#ifndef __COMPRESSION_CUIF_2D_H
#define __COMPRESSION_CUIF_2D_H
 
#include "cuif.h"

typedef struct {
	cuif_header_t header; /**<  */
	void* extra_content; /**<  */
	uint8_t*** pixel_array; /**<  */
} cuif_2d_image_t;


cuif_2d_image_t* cuif_2d_image_new(uint8_t version, uint8_t channels, uint32_t width, uint32_t height);

cuif_2d_image_t* cuif_2d_image_new_with_header(cuif_header_t* header);

void cuif_2d_image_free(cuif_2d_image_t* cuif_2d_image);
 
#endif /* __COMPRESSION_CUIF_2D_H */