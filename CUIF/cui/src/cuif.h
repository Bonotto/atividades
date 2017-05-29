#ifndef CUIF_H__
#define CUIF_H__

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include <math.h>

#include <string.h> 
#include <errno.h>

#include <libintl.h>

/*

This is the definition of INE5431 image file format:

header:

	#-----------#-----------#-----------------------------------------------------------#
	|	offset	|	size	|						description							|
	#-----------#-----------#-----------------------------------------------------------#
	|	0		|	2		|	signature, must be 5431(dec)							|
	|	2		|	1		|	CUI version... see version map bellow!					|
	|	3		|	1		|	number of students in group	(NUMBER_OF_STUDENTS)		|
	|	4		|	4		|	image width in pixels									|
	|	8		|	4		|	image height in pixels				 					|
	#-----------#-----------#-----------------------------------------------------------#

initial data:

	for i=0 to NUMBER_OF_STUDENTS-1:
	#-----------#-----------#-----------------------------------------------------------#
	|	offset	|	size	|						description							|
	#-----------#-----------#-----------------------------------------------------------#
	|	12+i*4	|	4		|	student id number										|
	#-----------#-----------#-----------------------------------------------------------#

------- THE REMAING FILE WILL CONTAIN DATA ACCORDING WITH THE FILE VERSION ------------------------------------------------

For instance, for pixel data (version 1):
	#-------------------------------------------#--------------#-----------------------------------------------------------#
	|	offset									|	size	   |						description						   |
	#-------------------------------------------#--------------#-----------------------------------------------------------#
	|	12+NUMBER_OF_STUDENTS*4					| width*height |		pixels from Red channel	(raster) 				   |
	|	12+NUMBER_OF_STUDENTS*4+width*height	| width*height |		pixels from Green channel (raster)				   |
	|	12+NUMBER_OF_STUDENTS*4+width*height*2	| width*height |		pixels from Blue channel (raster)				   |
	#-------------------------------------------#--------------#-----------------------------------------------------------#
	*raster: left to right, top to bottom
			 e.g: 0  1  2  3
			 	  4  5  6  7
			 	  8  9  10 11
			 	  12 13 14 15
			 becomes:
			      0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

Versions:

	0: not valid;
	1: contains R, G, B planes
	2: contains Y, Cb, Cr planes
	3: contains Y, Cb (subsampled), Cr (subsampled) planes
*/

//definitions

/**
 * Signature of the file
 */
#define SIGNATURE 5431

/**
 * Defines the number of students in a group. Can be set in the code, or may use a parameter.
 */
#define NUMBER_OF_STUDENTS 1


#ifndef CUI_V1_ID
#define CUI_V1_ID 1
#endif


#ifndef CUI_V2_ID
#define CUI_V2_ID 2
#endif

//Structs:


typedef struct {
	uint16_t signature; /**< Must have the file signature, used to identify the cuif format */
	uint8_t version; /**< Identifies the version of the cuif */
	uint8_t number_of_students; /**< Number of students in the group who edited the code */
	uint8_t channels; /**< The number of channels in the image */
	uint32_t width; /**< The full image width */
	uint32_t height; /**< The full image height */
	uint32_t* student_id; /**< A list of numeric student IDs */
} cuif_header_t;




bool cuif_init_header(cuif_header_t* header, uint8_t version, uint8_t channels, uint32_t width, uint32_t height);

void cuif_add_student_ids_in_header(cuif_header_t* header, const uint32_t* list_of_ids);

bool cuif_copy_header(const cuif_header_t* from, cuif_header_t* to);

#endif /* end of include guard: CUIF_H__ */