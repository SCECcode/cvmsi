/**
   test_cvmsi_exec.c

   invoke cvmsi api
**/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include "unittest_defs.h"
#include "test_helper.h"
#include "ucvm_model_dtypes.h"

extern int isMacOS;

int CVMSI_TESTS=5;

int test_setup()
{
  printf("Test: model_init() and model_finalize()\n");

  char *envstr=getenv("UCVM_INSTALL_PATH");
  if(envstr != NULL) {
    if (test_assert_int(model_init(envstr, "cvmsi"), 0) != 0) {
      return(1);
    }
  } else if (test_assert_int(model_init("..", "cvmsi"), 0) != 0) {
    return(1);
  }

  if (test_assert_int(model_finalize(), 0) != 0) {
    return(1);
  }

  printf("PASS\n");
  return(0);
}

int test_setparam()
{
  printf("Test: model_setparam() with depth\n");

// Initialize the model, try to use Use UCVM_INSTALL_PATH
  char *envstr=getenv("UCVM_INSTALL_PATH");
  if(envstr != NULL) {
    if (test_assert_int(model_init(envstr, "cvmsi"), 0) != 0) {
      return(1);
    }
  } else if (test_assert_int(model_init("..", "cvmsi"), 0) != 0) {
    return(1);
  }

  int zmode = UCVM_COORD_GEO_DEPTH;
  if (test_assert_int(model_setparam(0, UCVM_PARAM_QUERY_MODE, zmode), 0) != 0) {
      return(1);
  }

  // Close the model.
  assert(model_finalize() == 0);

  printf("PASS\n");
  return(0);
}


int test_query_by_depth()
{
  printf("Test: model_query() by depth\n");

  cvmsi_point_t pt;
  cvmsi_properties_t ret;

// Initialize the model, try to use Use UCVM_INSTALL_PATH
  char *envstr=getenv("UCVM_INSTALL_PATH");
  if(envstr != NULL) {
    if (test_assert_int(model_init(envstr, "cvmsi"), 0) != 0) {
      return(1);
    }
  } else if (test_assert_int(model_init("..", "cvmsi"), 0) != 0) {
    return(1);
  }

  int zmode = UCVM_COORD_GEO_DEPTH;
  if (test_assert_int(model_setparam(0, UCVM_PARAM_QUERY_MODE, zmode), 0) != 0) {
      return(1);
  }

  // Query a point.
  pt.longitude = -118.1;
  pt.latitude = 34.0;
  pt.depth = 1500; // surface 55.837, vs30 293.5

  if (test_assert_int(model_query(&pt, &ret, 1), 0) != 0) {
      return(1);
  }

  if ((test_assert_double(ret.vs, 1624.956), 0) != 0) {
      return(1);
  }
  if ((test_assert_double(ret.vp, 2873.24), 0) != 0) {
      return(1);
  }
  if ((test_assert_double(ret.rho, 2332.979), 0) != 0) {
      return(1);
  }
  // printf("Query was successful.\n");

  // Close the model.
  assert(model_finalize() == 0);

  printf("PASS\n");
  return(0);
}

int test_query_by_elevation()
{
  printf("Test: model_query() by elevation\n");

  cvmsi_point_t pt;
  cvmsi_properties_t ret;

// Initialize the model, try to use Use UCVM_INSTALL_PATH
  char *envstr=getenv("UCVM_INSTALL_PATH");
  if(envstr != NULL) {
    if (test_assert_int(model_init(envstr, "cvmsi"), 0) != 0) {
      return(1);
    }
  } else if (test_assert_int(model_init("..", "cvmsi"), 0) != 0) {
    return(1);
  }

  int zmode = UCVM_COORD_GEO_ELEV;
  if (test_assert_int(model_setparam(0, UCVM_PARAM_QUERY_MODE, zmode), 0) != 0) {
      return(1);
  }

  // Query a point.
  pt.longitude = -118.1;
  pt.latitude = 34.0;
  double pt_elevation = -1500;
  double pt_surf = 55.837; // 49.9;
  pt.depth = pt_surf - pt_elevation; // elevation
//  fprintf(stderr,"depth would be %lf \n",pt.depth);

  if (test_assert_int(model_query(&pt, &ret, 1), 0) != 0) {
      return(1);
  }

  if ((test_assert_double(ret.vs, 1659.86), 0) != 0) {
      return(1);
  }
  if ((test_assert_double(ret.vp, 2897.349), 0) != 0) {
      return(1);
  }
  if ((test_assert_double(ret.rho, 2338.714), 0) != 0) {
      return(1);
  }
  //printf("Query was successful.\n");

  // Close the model.
  assert(model_finalize() == 0);

  printf("PASS\n");
  return(0);
}

// using points 'offset' by ucvm's digital elevation
int test_query_points_by_elevation()
{
  printf("Test: model_query() points by elevation\n");

  FILE  *infp, *outfp;
  cvmsi_point_t pt;
  cvmsi_properties_t ret;
  double elev;
  double surf;

  char infile[1280];
  char outfile[1280];
  char reffile[1280];
  char currentdir[1000];

  /* Save current directory */
  getcwd(currentdir, 1000);

// ge part
  sprintf(infile, "%s/%s", currentdir, "./inputs/test_latlons_ucvm_ge.txt");
  sprintf(outfile, "%s/%s", currentdir, "test_latlons_ucvm_ge.out");
  if(isMacOS) {
    sprintf(reffile, "%s/%s", currentdir, "./ref/test_latlons_ucvm_ge_macos.ref");
    } else {
      sprintf(reffile, "%s/%s", currentdir, "./ref/test_latlons_ucvm_ge.ref");
  }

  if (test_assert_file_exist(infile) != 0) {
    printf("file:%s not found\n",infile);
    return(1);
  }

  // pick up every point and convert the elevation to depth in pt structure
  infp = fopen(infile, "r");
  if (infp == NULL) {
    printf("FAIL: cannot open %s\n", infile);
    return(1);
  }
  outfp = fopen(outfile, "w");
  if (outfp == NULL) {
    printf("FAIL: cannot open %s\n", outfile);
    return(1);
  }

  char *envstr=getenv("UCVM_INSTALL_PATH");
  if(envstr != NULL) {
    if (test_assert_int(model_init(envstr, "cvmsi"), 0) != 0) {
      return(1);
    }
  } else if (test_assert_int(model_init("..", "cvmsi"), 0) != 0) {
    return(1);
  }

  int zmode = UCVM_COORD_GEO_ELEV;
  if (test_assert_int(model_setparam(0, UCVM_PARAM_QUERY_MODE, zmode), 0) != 0) {
      return(1);
  }

/* process one term at a time */
  char line[1001];
  while(fgets(line, 1000, infp) != NULL) {
    if(line[0] == '#') continue; // a comment
    if (sscanf(line,"%lf %lf %lf",
         &pt.longitude,&pt.latitude,&elev) == 3) {
      surf = get_preset_ucvm_surface(pt.longitude, pt.latitude);
      pt.depth= surf - elev;
      if (test_assert_int(model_query(&pt, &ret, 1), 0) == 0) {
         fprintf(outfp,"%lf %lf %lf\n",ret.vs, ret.vp, ret.rho);
      }
    }
  }
  fclose(infp);
  fclose(outfp);

  /* Perform diff btw outfile and ref */
  if (test_assert_file(outfile, reffile) != 0) {
    printf("unmatched result\n");
    printf("%s\n",outfile);
    printf("%s\n",reffile);
    return(1);
  }

  // Close the model.
  assert(model_finalize() == 0);

  unlink(outfile);

  printf("PASS\n");
  return(0);
}



int suite_cvmsi_exec(const char *xmldir)
{
  suite_t suite;
  char logfile[256];
  FILE *lf = NULL;

 /* Setup test suite */
  strcpy(suite.suite_name, "suite_cvmsi_exec");
  suite.num_tests = CVMSI_TESTS;
  suite.tests = malloc(suite.num_tests * sizeof(test_t));
  if (suite.tests == NULL) {
    fprintf(stderr, "Failed to alloc test structure\n");
    return(1);
  }
  test_get_time(&suite.exec_time);

  /* Setup test cases */
  strcpy(suite.tests[0].test_name, "test_setup");
  suite.tests[0].test_func = &test_setup;
  suite.tests[0].elapsed_time = 0.0;

  strcpy(suite.tests[1].test_name, "test_separam");
  suite.tests[1].test_func = &test_setparam;
  suite.tests[1].elapsed_time = 0.0;

  strcpy(suite.tests[2].test_name, "test_query_by_depth");
  suite.tests[2].test_func = &test_query_by_depth;
  suite.tests[2].elapsed_time = 0.0;

  strcpy(suite.tests[3].test_name, "test_query_by_elevation");
  suite.tests[3].test_func = &test_query_by_elevation;
  suite.tests[3].elapsed_time = 0.0;

  strcpy(suite.tests[4].test_name, "test_query_points_by_elevation");
  suite.tests[4].test_func = &test_query_points_by_elevation;
  suite.tests[4].elapsed_time = 0.0;

  if (test_run_suite(&suite) != 0) {
    fprintf(stderr, "Failed to execute tests\n");
    return(1);
  }

  if (xmldir != NULL) {
    sprintf(logfile, "%s/%s.xml", xmldir, suite.suite_name);
    lf = init_log(logfile);
    if (lf == NULL) {
      fprintf(stderr, "Failed to initialize logfile\n");
      return(1);
    }
    
    if (write_log(lf, &suite) != 0) {
      fprintf(stderr, "Failed to write test log\n");
      return(1);
    }
    
    close_log(lf);
  }

  free(suite.tests);

  return 0;
}
