#ifndef BITMAP_FILE_HANDLER_H__
#define BITMAP_FILE_HANDLER_H__

#include "language.h"
#include "bitmap.h"

#include <math.h>

bitmap_t* bitmap_read_from_file(const char* filename, bool verbose);

void bitmap_write_to_file(const bitmap_t* bitmap, const char* filename);

#endif /* end of include guard: BITMAP_FILE_HANDLER_H__ */