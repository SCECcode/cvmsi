#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include "cvms.h"

int test_assert_file_exist(const char* filename);

double get_preset_ucvm_surface(double, double);

/* Execute cvms_txt as a child process */
int runCVMSTxt(const char *bindir, const char *infile, const char *outfile);

/* run cvms api */
int runCVMS(const char *bindir, const char *cvmdir,
          const char *infile, const char *outfile, int mode);

int runVXCVMS(const char *bindir, const char *cvmdir,
          const char *infile, const char *outfile);

#endif
