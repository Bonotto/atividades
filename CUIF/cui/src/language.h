#ifndef __COMPRESSION_LANGUAGE_H
#define __COMPRESSION_LANGUAGE_H

#include <stdio.h>
#include <stdlib.h>

#include <libintl.h>
#include <locale.h>
 
#define _(String) gettext((String))

void setup_language();

#endif /* __COMPRESSION_LANGUAGE_H */