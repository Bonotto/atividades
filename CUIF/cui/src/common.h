#ifndef COMMON_H__
#define COMMON_H__

#include <getopt.h> //

#include "language.h"
#include "cuif_test.h"
#include "bitmap_test.h"

#include "color_spaces_test.h"


extern int verbose_flag;
extern int cui_version;


extern char* input_filename;
extern char* output_filename;


void common_testing();

void common_print_version(const char* version, const char* name);

void common_print_help(const char* name);

void common_decode_options(int argc, char** argv, const char* name);


#endif /* end of include guard: COMMON_H__ */