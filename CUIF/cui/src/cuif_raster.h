#ifndef __COMPRESSION_CUIF_RASTER_H
#define __COMPRESSION_CUIF_RASTER_H
 
#include "cuif.h"

typedef struct {
	cuif_header_t header; /**<  */
	void* extra_content; /**<  */
	uint8_t** pixel_array; /**<  */
} cuif_raster_image_t;

cuif_raster_image_t* cuif_raster_image_new(uint8_t version, uint8_t channels, uint32_t width, uint32_t height);
 
#endif /* __COMPRESSION_CUIF_RASTER_H */