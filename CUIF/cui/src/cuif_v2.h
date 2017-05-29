#ifndef __CUI_CUIF_V2_H
#define __CUI_CUIF_V2_H
 
#include "language.h"

#include "cuif.h"
#include "cuif_2d.h"

#include "cuif_v1.h"

#include "color_spaces.h"

#ifndef CUI_V2_Y
#define CUI_V2_Y 0
#endif

#ifndef CUI_V2_CB
#define CUI_V2_CB 1
#endif

#ifndef CUI_V2_CR
#define CUI_V2_CR 2
#endif


cuif_2d_image_t* cuif_v2_new_from_cuif_v1(cuif_2d_image_t* cuif_v1);

cuif_2d_image_t* cuif_v2_convert_to_cuif_v1(cuif_2d_image_t* cuif_v2);
 
#endif /* __CUI_CUIF_V2_H */