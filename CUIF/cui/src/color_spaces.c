/*
* @Author: ismaelseidel
* @Date:   2016-08-01 12:14:00
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-01 18:45:58
*/

#include "color_spaces.h"


double color_difference(double y, double k, uint8_t color){
    return ((color-y)/(1-k))/2.0; //the division is a means to normalize the values...
}


double color_difference_double(double y, double k, double color){// a little bit of black magic.
    return ((color-y)/(1-k))/2.0; //the division is a means to normalize the values...
}

double rgb_uint8_t_to_double(uint8_t value)
{
	return (double)value/255.0;
}

uint8_t rgb_double_to_uint8_t(double value)
{
	return value*255.0;
}


void rgb_to_ycbcr_base_double(	double r, 
								double g, 
								double b, 
								double * const y, 
								double * const cb, 
								double * const cr)
{    
	/** 
		TODO!
	**/
    *y = r;
    *cb = g;
    *cr = b;
    /** 
		Modifiquem o código acima para fazer a conversão corretamente!
		PS: sugiro que não se baseiem na conversão inversa que está otimizada... 
		Sigam a especificação do documento BT.601
	**/
}

uint8_t ycbcr_y_double_to_uint8_t(double y)
{
	return 219.0*y+16.0; // pg.4 of BT.601
}

uint8_t ycbcr_chroma_double_to_uint8_t(double chroma)
{
	return 224.0*chroma+128.0;
}

double ycbcr_y_uint8_t_to_double(uint8_t y)
{
	return (y-16)/219.0;
}

double ycbcr_chroma_uint8_t_to_double(uint8_t chroma)
{
	return (chroma-128)/224.0;
}

void rgb_to_ycbcr_base(	uint8_t r, 
						uint8_t g, 
						uint8_t b, 
						uint8_t * const y, 
						uint8_t * const cb, 
						uint8_t * const cr)
{
    double r_double = rgb_uint8_t_to_double(r);
    double g_double = rgb_uint8_t_to_double(g);
    double b_double = rgb_uint8_t_to_double(b);

   	double y_double, cb_double, cr_double;

   	rgb_to_ycbcr_base_double(r_double, g_double, b_double, &y_double, &cb_double, &cr_double);

    *y = ycbcr_y_double_to_uint8_t(y_double);
    *cb = ycbcr_chroma_double_to_uint8_t(cb_double);
    *cr = ycbcr_chroma_double_to_uint8_t(cr_double);

}

void check_and_correct_rgb_range_component( double * const component)
{
	if (*component > 1.0)
	{
		*component = 1.0;
		return;
	}
	if (*component < 0.0)
	{
		*component = 0.0;
	}
}

void ycbcr_to_rgb_check_and_correct_ranges(	double * const r, 
											double * const g, 
											double * const b)
{
	check_and_correct_rgb_range_component(r);
	check_and_correct_rgb_range_component(g);
	check_and_correct_rgb_range_component(b);
}

void ycbcr_to_rgb_base_double(	double kb, 
								double kr, 
								double y, 
								double cb, 
								double cr, 
								double * const r, 
								double * const g, 
								double * const b)
{    
    *b = cb*2*(1.0-kb)+y;
    *r = cr*2*(1.0-kr)+y;
    *g = (y-kr*(*r)-kb*(*b))/(1.0-kr-kb);
    ycbcr_to_rgb_check_and_correct_ranges(r,g,b);
}

void ycbcr_to_rgb_base(	double kb, 
					double kr, 
					uint8_t y, 
					uint8_t cb, 
					uint8_t cr, 
					uint8_t * const r, 
					uint8_t * const g, 
					uint8_t * const b)
{
    double r_double;
    double g_double;
    double b_double;

    double y_double = ycbcr_y_uint8_t_to_double(y);
	double cb_double = ycbcr_chroma_uint8_t_to_double(cb);
	double cr_double = ycbcr_chroma_uint8_t_to_double(cr);

    ycbcr_to_rgb_base_double(kb, kr, y_double, cb_double, cr_double, &r_double, &g_double, &b_double);

    *r = rgb_double_to_uint8_t(r_double);
    *g = rgb_double_to_uint8_t(g_double);
    *b = rgb_double_to_uint8_t(b_double);
}


//ITU-R BT.601 conversion
void bt601_rgb_to_ycbcr(uint8_t r, 
						uint8_t g, 
						uint8_t b, 
						uint8_t * const y, 
						uint8_t * const cb, 
						uint8_t * const cr)
{
	rgb_to_ycbcr_base(r, g, b, y, cb, cr);
}

void bt601_rgb_to_ycbcr_double(	double r, 
								double g, 
								double b, 
								double * const y, 
								double * const cb, 
								double * const cr)
{
	assert((r >= 0.0) && (r <= 1.0));
	assert((g >= 0.0) && (g <= 1.0));
	assert((b >= 0.0) && (b <= 1.0));

	rgb_to_ycbcr_base_double(r, g, b, y, cb, cr);
}

void bt601_ycbcr_to_rgb(uint8_t y, 
						uint8_t cb, 
						uint8_t cr, 
						uint8_t * const r, 
						uint8_t * const g, 
						uint8_t * const b)
{
	ycbcr_to_rgb_base(0.114, 0.299, y, cb, cr, r, g, b);
}

void bt601_ycbcr_to_rgb_double(	double y, 
								double cb, 
								double cr, 
								double * const r, 
								double * const g, 
								double * const b)
{
	ycbcr_to_rgb_base_double(00.114, 0.299, y, cb, cr, r, g, b);
}