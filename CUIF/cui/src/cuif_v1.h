#ifndef CUIF_V1_H__
#define CUIF_V1_H__

#include "bitmap.h"

#include "language.h"

#include "cuif.h"
#include "cuif_2d.h"

#ifndef CUI_V1_RED
#define CUI_V1_RED 0
#endif

#ifndef CUI_V1_GREEN
#define CUI_V1_GREEN 1
#endif

#ifndef CUI_V1_BLUE
#define CUI_V1_BLUE 2
#endif


cuif_2d_image_t* cuif_v1_new_from_bitmap(bitmap_t* bitmap);

bitmap_t* cuif_v1_convert_to_bitmap(cuif_2d_image_t* cuif_v1);


#endif /* end of include guard: CUIF_V1_H__ */