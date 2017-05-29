/*
* @Author: ismaelseidel
* @Date:   2016-08-22 20:18:53
* @Last Modified by:   ismaelseidel
* @Last Modified time: 2016-08-22 20:32:24
*/

#include "common.h"

char* input_filename;
char* output_filename;

int verbose_flag;
int cui_version;

void common_testing()
{
	test_cuif_2d_rgb_writing();

	test_bitmap_reading();

	test_cuif_2d_bitmap_conversion();
}


void common_print_version(const char* version, const char* name)
{
	printf(_("%s version %s\n"), name, version);
}


/**
 * @brief      Prints a help for this program
 */
void common_print_help(const char* name)
{
	printf(_("%s Copyright (C) 2016  Ismael Seidel\n"), name);
    printf(_("This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"));
    printf(_("This is free software, and you are welcome to redistribute it\n"));
    printf(_("under certain conditions; \n\n")); //type \'show c\' for details.
	
	printf(_("--help (--h)\tShows this help.\n"));

	printf(_("--version (--v)\tSets the CUI version.\n"));
	printf(_("\t\tAvailable CUI versions:\n"));
	printf(_("\t\t\t1) RGB\n"));
	printf(_("\t\t\t2) YCbCr\n"));
	printf(_("\tNotice, however, that this flag is only used when converting bmp2cuif and not the other way arround...\n"));

	printf(_("--test (--t)\tExecutes a series of image tests of this software.\n"));
	//printf(_("--version (--v)\tShows the version of this software.\n"));
	printf(_("--verbose \tEnables all messages.\n"));
}


/**
 * @brief      { function_description }
 *
 * @param[in]  argc  The argc
 * @param      argv  The argv
 */
void common_decode_options(int argc, char** argv, const char* name)
{ //https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
	int c;
	verbose_flag = 0;
	cui_version = 1; //default version
	while (1) 
	{
		static struct option long_options[] =
		{
			/* These options set a flag. */
			{"verbose", no_argument, &verbose_flag, 1},
			/* These options don't set a flag.
			  We distinguish them by their indices. */
			{"color", no_argument, 0, 'c'},
			{"help", no_argument, 0, 'h'},
			{"version", required_argument, 0, 'v'},
			//{"type", required_argument, 0, 't'},
			{"test", no_argument, 0, 't'},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, "hvt", long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0)
					break;
				printf ("option %s", long_options[option_index].name);
				if (optarg)
					printf (" with arg %s", optarg);
				printf ("\n");
				break;
			case 'c':
				color_space_test();
				break;
			case 'h':
				common_print_help(name);
				break;
			case 'v':
				// if (optarg)
				// 	printf (" with arg %s\n\n", optarg);
				cui_version = atoi(optarg);
				break;
			case 't':
				if (optarg)
					printf (" with arg %s\n\n", optarg);
				//printf("iu: %d", atoi(optarg));
				break;
			// case 'T':
			// 	common_print_help(name);				
			// 	break;
			case '?':
				/* getopt_long already printed an error message. */
				break;

			default:
				abort ();
		}
	}

	if (optind < argc-2)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc-2)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }
    if (optind >= argc)
    {
    	fprintf(stderr, _("Error: Expecting an input and an output file! Use --help for help!\n"));
    	return;
    }

    if (verbose_flag)
    {
    	printf("Filein = %s\n", argv[optind]);
    }
    input_filename = argv[optind++];
    
    if (optind >= argc)
    {
    	fprintf(stderr, _("Error: Expecting an output file! Use --help for help!\n"));
    	return;
    }
    if (verbose_flag){
    	printf("Fileout = %s\n", argv[optind]);	
    }
    output_filename = argv[optind++];
    
}