/**
* @file
* @brief {briefing of this file}
* @author: ismaelseidel
* @date:   2016-08-12 17:12:57
* @last Modified by:   ismaelseidel
* @last Modified time: 2016-08-29 17:23:28
*
*
*************************************************************************
* cuif2bmp -- Tool to convert a CUIF file to bitmap (*.bmp)
*************************************************************************
* Copyright (C)2016 Ismael Seidel
*
* Author: Ismael Seidel 	<ismaelseidel@gmail.com;
* 							 ismaelseidel@inf.ufsc.br;
* 							 ismael.seidel@posgrad.ufsc.br;>
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* 
*/

#include <stdio.h>


#include "cuif.h"
#include "language.h"


#include "cuif_test.h"
#include "bitmap_test.h"

#include "bitmap_file_handler.h"
#include "cuif_file_handler.h"

#include "common.h"

char* input_filename;
char* output_filename;



void write_bitmap_from_cuif_v1(cuif_2d_image_t* cuif_v1)
{
	bitmap_t* bitmap_from_cuif = cuif_v1_convert_to_bitmap(cuif_v1);
	cuif_2d_image_free(cuif_v1);

	bitmap_write_to_file(bitmap_from_cuif, output_filename);
	bitmap_free(bitmap_from_cuif);
}


void convert_from_v2_and_write_bitmap_from_cuif_v1(cuif_2d_image_t* cuif_v2)
{
	cuif_2d_image_t* cuif_v1 = cuif_v2_convert_to_cuif_v1(cuif_v2);
	cuif_2d_image_free(cuif_v2);

	write_bitmap_from_cuif_v1(cuif_v1);
}


int main(int argc, char** argv) 
{

	common_decode_options(argc, argv, "cuif2bmp");

	setup_language();

	cuif_2d_image_t* cuif_from_file = cuif_2d_read_from_file(input_filename, verbose_flag);

	switch(cuif_from_file->header.version) {

		case CUI_V1_ID:
			write_bitmap_from_cuif_v1(cuif_from_file);
			break; 

		case CUI_V2_ID:
			convert_from_v2_and_write_bitmap_from_cuif_v1(cuif_from_file);
			break; 
	  
		default:
	   		fprintf(stderr, _("Unsuported CUI version\n"));
	   		exit(EXIT_FAILURE);
	}

    return 0;
}