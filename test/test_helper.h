#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include "cvmsi.h"

int test_assert_file_exist(const char* filename);

double get_preset_ucvm_surface(double, double);

/* run cvms api */
int runCVMSI(const char *bindir, const char *cvmdir,
          const char *infile, const char *outfile, int mode);

int runCVMSIQuery(const char *bindir, const char *cvmdir,
          const char *infile, const char *outfile);

#endif
