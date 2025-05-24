#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <getopt.h>
#include "unittest_defs.h"
#include "test_grid_exec.h"

#if defined(__APPLE__) && defined(__MACH__)
int isMacOS=true;
#elif defined(unix) || defined(__unix__) || defined(__unix)
int isMacOS=false;
#endif

int main (int argc, char *argv[])
{

  char *xmldir;

  if (argc == 2) {  
    xmldir = argv[1];
  } else {
    xmldir = NULL;
  }

  /* Run test suites */
  suite_grid_exec(xmldir);

  return 0;
}
