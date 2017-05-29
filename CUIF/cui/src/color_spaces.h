#ifndef __CUI_COLOR_SPACES_H
#define __CUI_COLOR_SPACES_H
 
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

void bt601_rgb_to_ycbcr(uint8_t r, 
						uint8_t g, 
						uint8_t b, 
						uint8_t * const y, 
						uint8_t * const cb, 
						uint8_t * const cr);

void bt601_ycbcr_to_rgb(uint8_t y, 
						uint8_t cb, 
						uint8_t cr, 
						uint8_t * const r, 
						uint8_t * const g, 
						uint8_t * const b);


void bt601_rgb_to_ycbcr_double(	double r, 
								double g, 
								double b, 
								double * const y, 
								double * const cb, 
								double * const cr);


void bt601_ycbcr_to_rgb_double(	double y, 
								double cb, 
								double cr, 
								double * const r, 
								double * const g, 
								double * const b);

 
#endif /* __CUI_COLOR_SPACES_H */