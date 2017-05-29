/**
* @file
* @Author: ismaelseidel
* @Date:   2016-08-08 17:34:21
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-22 20:31:59
*
*************************************************************************
* bmp2cuif -- Tool to convert a bitmap (*.bmp) file to CUIF
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

int verbose_flag;
int cui_version;

void convert_and_write_cuif_v2(cuif_2d_image_t* cuif_v1)
{
	cuif_2d_image_t* cuif_v2 = cuif_v2_new_from_cuif_v1(cuif_v1);

	cuif_2d_write_to_file(cuif_v2, output_filename);


	cuif_2d_image_free(cuif_v2);
	cuif_2d_image_free(cuif_v1);
}

void write_cuif_v1(cuif_2d_image_t* cuif_v1)
{
	cuif_2d_write_to_file(cuif_v1, output_filename);
	cuif_2d_image_free(cuif_v1);
}


int main(int argc, char** argv) 
{

	common_decode_options(argc, argv, "bmp2cuif");

	setup_language();

	bitmap_t* bitmap_from_file = bitmap_read_from_file(input_filename, verbose_flag);

	cuif_2d_image_t* cuif_v1_from_bitmap = cuif_v1_new_from_bitmap(bitmap_from_file);
	bitmap_free(bitmap_from_file);


	/**       EDITAR:      **/

	uint32_t list_of_ids[NUMBER_OF_STUDENTS] = {16104059};

	/** ^^^^^ EDITAR ^^^^^ **/
	

	cuif_add_student_ids_in_header(&cuif_v1_from_bitmap->header, &list_of_ids[0]);

	switch(cui_version) {

		case CUI_V1_ID:
			write_cuif_v1(cuif_v1_from_bitmap);
			break; 

		case CUI_V2_ID:
			convert_and_write_cuif_v2(cuif_v1_from_bitmap);
			break; 
	  
		default:
	   		fprintf(stderr, _("Unsuported CUI version\n"));
	   		exit(EXIT_FAILURE);
	}

    return 0;
}