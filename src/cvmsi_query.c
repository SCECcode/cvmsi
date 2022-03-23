/*
 * @file cvmsi_query.c
 * @brief Bootstraps the test framework for the CVM-SI library.
 * @author - SCEC
 * @version 1.0
 *
 * Tests the CVMS library by loading it and executing the code as
 * UCVM would.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include "cvmsi.h"

/* Getopt flags */
extern char *optarg;
extern int optind, opterr, optopt;

int cvmsi_query_debug = 0;

#define MAX_READ_POINTS 1000000

/* Usage function */
void usage() {
  printf("\n     cvmsi_query - (c) SCEC\n");
  printf("Extract velocities from SCEC CVM-SI. Accepts\n");
  printf("geographic coordinates coordinates in lon,lat,dep columns.\n\n");
  printf("\tusage: cvmsi_query < file.in\n\n");
  printf("Flags:\n");
  printf("\t-h This help message.\n");
  printf("\t-m Path to model files.\n\n");
  printf("Output format is:\n");
  printf("\tlon lat dep(m) x y z vp(m/s) vs(m/s) rho\n\n");
  printf("Notes:\n");
  printf("\t- If running interactively, type Cntl-D to end input coord list.\n");
  exit (0);
}


int main(int argc, char **argv)
{
  // Declare the structures.
  cvmsi_point_t *pnts = malloc(sizeof(cvmsi_point_t) * MAX_READ_POINTS);
  cvmsi_properties_t *ret = malloc(sizeof(cvmsi_properties_t) * MAX_READ_POINTS);
  int rc;
  int opt, i;
  int counter = 0;

  /* Config variables */
  char modelpath[CVMSI_MAX_STR_LEN];

  strcpy(modelpath, "../data/i26");

  /* Parse options */
  while ((opt = getopt(argc, argv, "hm:")) != -1) {
    switch (opt) {
    case 'h':
      usage();
      exit(0);
      break;
    case 'm':
      strcpy(modelpath, optarg);
      break;
    default: /* '?' */
      usage();
      exit(1);
    }
  }


  // Initialize the model.
  // try to use Use UCVM_INSTALL_PATH
  char *envstr=getenv("UCVM_INSTALL_PATH");
  if(envstr != NULL) {
     assert(cvmsi_init(envstr, "cvmsi") == 0);
     } else {
       assert(cvmsi_init("..", "cvmsi") == 0);
  }
  printf("Loaded the model successfully.\n");

  char line[1001];
  while (counter < MAX_READ_POINTS && fgets(line, 1000, stdin) != NULL) {
    if(line[0]=='#') continue; // comment line
      if (sscanf(line,"%lf %lf %lf",
           &pnts[counter].longitude,&pnts[counter].latitude,&pnts[counter].depth) == 3) {
           counter++;
           continue;
      }
  }

  if(counter > 0) {
    rc=cvmsi_query(pnts, ret, counter);

  /* Display results */
    for (i = 0; i < counter; i++) {
      printf("%lf %lf %lf : vs(%lf) vp(%lf) rho(%lf)\n",
        pnts[i].longitude, pnts[i].latitude, pnts[i].depth,
        ret[i].vs, ret[i].vp, ret[i].rho);
    }
  }

  /* Finalize */
  assert(cvmsi_finalize() == 0);
  printf("Model closed successfully.\n");



  return(0);
}
