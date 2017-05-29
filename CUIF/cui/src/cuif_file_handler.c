/**
* @file
* @Author: ismaelseidel
* @Date:   2016-08-09 15:28:50
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-30 11:20:42
*/

#include "cuif_file_handler.h"


//File Writing

/**
 * @brief      { function_description }
 *
 * @param      image     The image
 * @param[in]  filename  The filename
 */
void cuif_2d_write_to_file(cuif_2d_image_t* image, const char* filename)
{
	if (image == NULL)
	{
		fprintf(stderr,_("Error: Unable to write a NULL image!\n"));
	}

	FILE* file = fopen(filename, "wb");

	if (file == NULL)
	{
		fprintf(stderr,_("Error: Unable to open file %s to write. %s\n"), filename, strerror(errno));
		return;
	}

	fwrite(&image->header, sizeof(cuif_header_t), 1, file);
	
	fwrite(image->header.student_id, sizeof(uint32_t), image->header.number_of_students, file);

	size_t i, j, k;

	for(k=0;k<image->header.channels;k++)
	{
		for(j=0;j<image->header.height;j++)
		{
			for(i=0;i<image->header.width; i++)
			{
				fwrite(&image->pixel_array[k][i][j], sizeof(uint8_t), 1, file); // must be written one by one, since they are organized as [x][y]...
			}
		}	
	}

	fclose(file);
}

/**
 * @brief      { function_description }
 *
 * @param      image     The image
 * @param[in]  filename  The filename
 */
void cuif_raster_write_to_file(cuif_raster_image_t* image, const char* filename)
{
	if (image == NULL)
	{
		fprintf(stderr,_("Error: Unable to write a NULL raster image! \n"));
	}

	FILE* file = fopen(filename, "wb");

	if (file == NULL)
	{
		fprintf(stderr,_("Error: Unable to open file %s to write. %s\n"), filename, strerror(errno));
		return;
	}

	fwrite(&image->header, sizeof(cuif_header_t), 1, file);
	
	fwrite(image->header.student_id, sizeof(uint32_t), image->header.number_of_students, file);

	size_t number_of_pixels_per_channel = image->header.width*image->header.height;

	size_t k;
	for(k=0;k<image->header.channels;k++)
	{
		fwrite(&image->pixel_array[0], sizeof(uint8_t), number_of_pixels_per_channel, file);	
	}

	fclose(file);
}

//File Reading


cuif_2d_image_t* cuif_2d_read_from_file(const char* filename, bool verbose)
{
	FILE* file = fopen(filename, "rb");

	if (file == NULL)
	{
		fprintf(stderr, _("Unable to open file %s to read. Error: %s\n"), filename, strerror(errno));
		return NULL;
	}

	cuif_header_t header;

	size_t n_read = fread(&header, sizeof(cuif_header_t), 1, file);

	if (n_read != 1)
	{
		fprintf(stderr, _("Error while loading file %s (header). Expecting %lu bytes, got %lu. \n"), filename, sizeof(cuif_header_t), n_read*sizeof(cuif_header_t));
		return NULL;
	}	

	if(verbose)
	{
		printf(_("Reading file %s:\n"), filename);
		printf("-------------------------------------------\n");
		printf(_("\tSignature: \t\t%u\n"), header.signature);
		printf(_("\tCUIF Version: \t\t%u\n"), header.version);
		printf(_("\tStudents in group: \t%u\n"), header.number_of_students);
		printf(_("\tCUIF channels: \t\t%u\n"), header.channels);
		printf(_("\tCUIF width: \t\t%u\n"), header.width);
		printf(_("\tCUIF height: \t\t%u\n"), header.height);
		printf("-------------------------------------------\n");
	}

	cuif_2d_image_t* image = cuif_2d_image_new_with_header(&header);

	n_read = fread(image->header.student_id, sizeof(uint32_t), header.number_of_students, file);
	
	if (n_read != header.number_of_students)
	{
		fprintf(stderr, _("Error while loading file %s. Expecting %u bytes, got %lu. \n"), filename, header.number_of_students, n_read*sizeof(uint32_t));
		return NULL;
	}

	size_t i = 0;

	if (verbose)
	{
		printf(_("\tStudent IDs:\n"));
		for(;i<header.number_of_students;i++)
		{
			printf("\t\t%u\n", image->header.student_id[i]);
		}
		printf("-------------------------------------------\n");
	}
	

	size_t j,k;

	for(k=0;k<image->header.channels;k++)
	{
		for(j=0;j<image->header.height;j++)
		{
			for(i=0;i<image->header.width; i++)
			{
				n_read = fread(&image->pixel_array[k][i][j], sizeof(uint8_t), 1, file);
				if (n_read != sizeof(uint8_t))
				{
					fprintf(stderr, _("Error while loading file %s. Expecting %lu bytes, got %lu. \n"), filename, sizeof(uint8_t), n_read);
					return NULL;
				}
			}
		}	
	}

	fclose(file);

	return image;
}