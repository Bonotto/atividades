/**
* @file
* @Author: ismaelseidel
* @Date:   2016-08-09 17:38:05
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-10 16:52:29
*/

//https://www.gnu.org/software/gettext/manual/gettext.html
//http://www.labri.fr/perso/fleury/posts/programming/a-quick-gettext-tutorial.html
//https://www.gnu.org/software/gettext/manual/html_node/Language-Codes.html#Language-Codes
//https://www.gnu.org/software/gettext/manual/html_node/Country-Codes.html#Country-Codes

#include "language.h"

void setup_language()
{
	setlocale(LC_ALL, "");
	bindtextdomain ("bmp2cuif", "lang");
	textdomain("bmp2cuif");
}