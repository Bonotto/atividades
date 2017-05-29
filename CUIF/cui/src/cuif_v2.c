/**
* @file
* @brief {briefing of this file}
* @author: ismaelseidel
* @date:   2016-08-29 14:10:33
* @last Modified by:   ismaelseidel
* @last Modified time: 2016-08-29 16:48:43
*/

#include "cuif_v2.h"

cuif_2d_image_t* cuif_v2_new_from_cuif_v1(cuif_2d_image_t* cuif_v1)
{
	if (cuif_v1 == NULL)
	{
		fprintf(stderr, _("Error: Impossible to create a cuif v2 with a NULL cuif v1!\n"));
		return NULL;
	}

	cuif_2d_image_t* cuif_v2 = cuif_2d_image_new(CUI_V2_ID, 3, cuif_v1->header.width, cuif_v1->header.height);

	cuif_copy_header(&cuif_v1->header, &cuif_v2->header); //from, to
	cuif_v2->header.version=CUI_V2_ID;

	size_t i,j;
	for(i=0;i<cuif_v2->header.width;i++){
		for(j=0;j<cuif_v2->header.height;j++)
		{
			
			bt601_rgb_to_ycbcr(	cuif_v1->pixel_array[CUI_V1_RED]  [i][j],
								cuif_v1->pixel_array[CUI_V1_GREEN][i][j],
								cuif_v1->pixel_array[CUI_V1_BLUE] [i][j],
								&cuif_v2->pixel_array[CUI_V2_Y]	  [i][j],
								&cuif_v2->pixel_array[CUI_V2_CB]  [i][j],
								&cuif_v2->pixel_array[CUI_V2_CR]  [i][j]
							  );
		}
	}

	return cuif_v2;
}

cuif_2d_image_t* cuif_v2_convert_to_cuif_v1(cuif_2d_image_t* cuif_v2)
{
	if (cuif_v2 == NULL)
	{
		fprintf(stderr, _("Error: Impossible to create a cuif v1 with a NULL cuif v2!\n"));
		return NULL;
	}

	cuif_2d_image_t* cuif_v1 = cuif_2d_image_new(CUI_V1_ID, 3, cuif_v2->header.width, cuif_v2->header.height);

	cuif_copy_header(&cuif_v2->header, &cuif_v1->header); //from, to
	cuif_v1->header.version=CUI_V1_ID;

	size_t i,j;
	for(i=0;i<cuif_v1->header.width;i++){
		for(j=0;j<cuif_v1->header.height;j++)
		{
			bt601_ycbcr_to_rgb( cuif_v2->pixel_array[CUI_V2_Y]     [i][j],
								cuif_v2->pixel_array[CUI_V2_CB]    [i][j],
								cuif_v2->pixel_array[CUI_V2_CR]    [i][j],
								&cuif_v1->pixel_array[CUI_V1_RED]  [i][j],
								&cuif_v1->pixel_array[CUI_V1_GREEN][i][j],
								&cuif_v1->pixel_array[CUI_V1_BLUE] [i][j]
				);
		}
	}

	return cuif_v1;
}