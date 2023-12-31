#ifndef __PGM_READ__
#define __PGM_READ__
#include "pgmImage.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
PgmImage pgmRead(const char *filename, int *return_value);
char pgmCharWrapper(char c, FILE *file, PgmImage *target, int *err);
int pgmScanWrapper(int input, FILE *file, PgmImage *target, int *err);
void getASCIIContents(int *error_return, PgmImage *target, FILE *input);
void getBinaryContents(int *error_return, PgmImage *target, FILE *input_file);
void freeComments(PgmImage this);
#endif //__PGM_READ__
