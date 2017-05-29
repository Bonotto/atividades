/**
* @file
* @Author: ismaelseidel
* @Date:   2016-08-08 21:47:59
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-11 19:15:19
*/

#include "cuif.h"

/**
 * @brief      Initializes the header with the informed paramenters
 *
 * @param      header   The header
 * @param[in]  version  The version
 * @param[in]  width    The width
 * @param[in]  height   The height
 *
 * @return     Returns true if the header was successfully initialized and false otherwise
 */
bool cuif_init_header(cuif_header_t* header, uint8_t version, uint8_t channels, uint32_t width, uint32_t height)
{
	if (header == NULL)
	{
		fprintf(stderr, "Error: Cannot init a NULL header!\n");
		return false;
	}

	header->signature = SIGNATURE;
	header->version = version;
	header->number_of_students = NUMBER_OF_STUDENTS;
	header->channels = channels;
	header->width = width;
	header->height = height;
	header->student_id = (uint32_t*) malloc(NUMBER_OF_STUDENTS*sizeof(uint32_t));

	if (header->student_id == NULL)
	{
		return false;
	}

	return true;
}

/**
 * @brief      { function_description }
 *
 * @param      header       The header
 * @param[in]  list_of_ids  The list of identifiers
 */
void cuif_add_student_ids_in_header(cuif_header_t* header, const uint32_t* list_of_ids)
{
	int i =0;
	for(;i<header->number_of_students;i++)
	{
		header->student_id[i] = list_of_ids[i];
	}
}

bool cuif_copy_header(const cuif_header_t* from, cuif_header_t* to)
{
	to->signature = from->signature;
	to->version = from->version;
	to->number_of_students = from->number_of_students;
	to->channels = from->channels;
	to->width = from->width;
	to->height = from->height;

	//warning:

	free(to->student_id);
	to->student_id = (uint32_t*) malloc(NUMBER_OF_STUDENTS*sizeof(uint32_t));

	if (to->student_id == NULL)
	{
		return false;
	}

	int i =0;
	for(;i<to->number_of_students;i++)
	{
		to->student_id[i] = from->student_id[i];
	}

	return true;
}