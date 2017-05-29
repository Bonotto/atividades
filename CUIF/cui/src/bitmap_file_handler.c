/*
* @Author: ismaelseidel
* @Date:   2016-08-10 21:53:46
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-11 18:52:19
*/

#include "bitmap_file_handler.h"

double bitmap_get_bytes_per_pixel(uint8_t bpp)
{
	return bpp/8.0;
}


void bitmap_header_print(bitmap_header_t* bitmap_header)
{
	if(bitmap_header == NULL)
	{
		fprintf(stderr, _("Error: Cannot print a NULL bitmap header!\n"));
		return;
	}
	printf(_("File Size: %u\n"), bitmap_header->size_of_bitmap_file);
	printf(_("Res.: %u\n"), bitmap_header->reserved);
	printf(_("Offset: %u\n"), bitmap_header->offset_to_start_image);
	printf(_("Header: %u\n"), bitmap_header->size_of_header); //must be 40
	printf(_("Width: %u\n"), bitmap_header->width);
	printf(_("Height: %u\n"), bitmap_header->height);
	printf(_("Number of planes:%u\n"), bitmap_header->number_of_planes);
	printf(_("BPP: %u\n"), bitmap_header->number_of_bits_per_pixel);
	printf(_("Compression: %u\n"), bitmap_header->compression_type);
	printf(_("Size: %u\n"), bitmap_header->size_of_image_in_bytes);
	printf(_("H/m: %u\n"), bitmap_header->horizontal_pixels_per_meter);
	printf(_("V/m: %u\n"), bitmap_header->vertical_pixels_per_meter);
	printf(_("Number of colors: %u\n"), bitmap_header->number_of_colors);
	printf(_("Number of important colors: %u\n"), bitmap_header->number_of_important_colors);
}

bitmap_t* bitmap_read_from_file(const char* filename, bool verbose)
{
	FILE* bitmap_file_pointer = fopen(filename, "r+b"); 			// read the bitmap file in binary mode

	if (bitmap_file_pointer == NULL)
	{
		fprintf(stderr, _("Error: The following error ocurred when trying to open the file %s: %s\n"), filename, strerror(errno));
		return NULL;
	}

	uint16_t bitmap_signature;

	if (fread(&bitmap_signature, sizeof(uint16_t), 1, bitmap_file_pointer) != 1)
	{
		fprintf(stderr, _("Error: Something wrong happened when trying to read the bitmap signature from the file %s. \n"), filename);
		return NULL;
	}

	if (bitmap_signature != BITMAP_SIGNATURE)
	{
		fprintf(stderr, _("Error: The file %s is not a valid bmp!"), filename);
		return NULL;
	}

	bitmap_t* bitmap = bitmap_new();

	if (bitmap == NULL)
	{
		fprintf(stderr, _("Error: Something went wrong when trying to (m)allocate the bitmap!\n"));
		bitmap_free(bitmap);
		return NULL;
	}

	if(fread(&bitmap->header, sizeof(bitmap_header_t), 1, bitmap_file_pointer) != 1)
	{
		fprintf(stderr, _("Error: Something wrong happened when trying to read the bitmap header from the file %s. \n"), filename);
		bitmap_free(bitmap);
		return NULL;
	}

	if (verbose)
	{
		bitmap_header_print(&bitmap->header);
	}

	fseek(bitmap_file_pointer, bitmap->header.offset_to_start_image, SEEK_SET); //http://www.cplusplus.com/reference/cstdio/fseek/

	uint8_t padding = bitmap->header.width % 4;

	size_t number_of_bytes_to_read = bitmap_get_bytes_per_pixel(bitmap->header.number_of_bits_per_pixel)*bitmap->header.height*(bitmap->header.width+padding);

	bitmap->bgr_pixel_array = (uint8_t*) malloc(number_of_bytes_to_read);

	if(fread(bitmap->bgr_pixel_array, sizeof(uint8_t), number_of_bytes_to_read, bitmap_file_pointer) != number_of_bytes_to_read)
	{
		fprintf(stderr, _("Error: Something went wrong while reading the bitmap data from the file %s. \n"), filename);
		bitmap_free(bitmap);
		return NULL;
	}

	fclose(bitmap_file_pointer);
	return bitmap;
}

void bitmap_write_to_file(const bitmap_t* bitmap, const char* filename)
{
	if (bitmap == NULL)
	{
		fprintf(stderr, _("Error: Cannot write a NULL bitmap to a file!\n"));
		return;
	}

	FILE* bitmap_file_pointer = fopen(filename, "w+b");

	if (bitmap_file_pointer == NULL)
	{
		fprintf(stderr, _("Error: The following error ocurred when trying to open the file %s for writing: %s\n"), filename, strerror(errno));
		return;
	}

	uint16_t bitmap_signature = BITMAP_SIGNATURE;

	fwrite(&bitmap_signature, sizeof(uint16_t), 1, bitmap_file_pointer);
	fwrite(&bitmap->header, sizeof(bitmap_header_t), 1, bitmap_file_pointer);



	size_t initial_padding = bitmap->header.offset_to_start_image-BITMAP_HEADER_COMMON_SIZE;
	if(initial_padding > 0)
	{
		printf("initial_padding = %lu\n", initial_padding);
		size_t i;
		uint8_t dummy_zero = 0;
		for(i=0;i<initial_padding;i++)	
		{
			fwrite(&dummy_zero, sizeof(uint8_t), 1, bitmap_file_pointer);
		}
	}
	

	uint8_t padding = bitmap->header.width % 4;
	size_t number_of_bytes_to_write = bitmap_get_bytes_per_pixel(bitmap->header.number_of_bits_per_pixel)*bitmap->header.height*(bitmap->header.width+padding);
	fwrite(bitmap->bgr_pixel_array, sizeof(uint8_t), number_of_bytes_to_write, bitmap_file_pointer);

	fclose(bitmap_file_pointer);

}