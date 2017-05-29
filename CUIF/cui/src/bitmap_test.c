/**
* @file
* @Author: ismaelseidel
* @Date:   2016-08-10 22:11:51
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-22 20:15:38
*/

#include "bitmap_test.h"

/**
 * @brief      { function_description }
 */
void test_bitmap_reading()
{
	printf(_("Testing bitmap reading\n"));
	bitmap_t* bitmap = bitmap_read_from_file("img/lena.bmp", true);
	bitmap_write_to_file(bitmap, "test/lena.bmp");
	bitmap_free(bitmap);
}