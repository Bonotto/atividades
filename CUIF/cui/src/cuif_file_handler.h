#ifndef __COMPRESSION_CUIF_FILE_HANDLER_H
#define __COMPRESSION_CUIF_FILE_HANDLER_H

 
#include "cuif.h"
#include "cuif_2d.h"
#include "cuif_raster.h"

#include "language.h"

void cuif_2d_write_to_file(cuif_2d_image_t* image, const char* filename);

cuif_2d_image_t* cuif_2d_read_from_file(const char* filename, bool verbose);
 
#endif /* __COMPRESSION_CUIF_FILE_HANDLER_H */