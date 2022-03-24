/**
   cvmsi_query.c

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "cvmsi.h"

/* Getopt flags */
extern char *optarg;
extern int optind, opterr, optopt;

int cvmsi_query_debug = 0;

#define MAX_READ_POINTS 1000000

int cvmsi_query_debug = 0;

/* Usage function */
void usage() {
  printf("\n     cvmsi_query - (c) SCEC\n");
  printf("Extract velocities from SCEC CVM-SI. Accepts\n");
  printf("geographic coordinates coordinates in lon,lat,dep columns.\n\n");
  printf("\tusage: cvmsi_query < file.in\n\n");
  printf("Flags:\n");
  printf("\t-h This help message.\n");
  printf("\t-m Path to model files.\n\n");
  printf("\t-d Output debug mode.\n\n");
  printf("Output format is:\n");
  printf("\tlon lat dep(m) x y z vp(m/s) vs(m/s) rho\n\n");
  printf("Notes:\n");
  printf("\t- If running interactively, type Cntl-D to end input coord list.\n");
  exit (0);
}


/**
 * Initializes and CVM-SI in standalone mode 
 *
 * @param argc The number of arguments.
 * @param argv The argument strings.
 * @return A zero value indicating success.
 */
int main(int argc, char **argv)
{
  int opt, i;

  /* Config variables */
  char modelpath[CVMSI_MAX_PATH_LEN];


  char *envstr=getenv("UCVM_INSTALL_PATH");
  if(envstr != NULL) {
    strcpy(modelpath,envstr);
    } else {
       strcpy(modelpath, "..");
  }

  /* Parse options */
  while ((opt = getopt(argc, argv, "dhm:")) != -1) {
    switch (opt) {
    case 'h':
      usage();
      exit(0);
      break;
    case 'm':
      strcpy(modelpath, optarg);
      break;
    case 'd':
      cvmsi_query_debug = 1;
      break;
    default: /* '?' */
      usage();
      exit(1);
    }
  }

  /* Init model */
  if (cvmsi_init(modelpath,"cvmsi") != 0) {
    fprintf(stderr, "Failed to initialize model\n");
    return(1);
  }

  printf("Loaded the model successfully.\n");
  
  _cvmsi_point_t *pnts = malloc(sizeof(cvmsi_point_t) * MAX_READ_POINTS);
  int counter = 0;
  
  /* Read in coords */


  char line[1001];
  while (fgets(line, 1000, stdin) != NULL) {
    if(line[0]=='#') continue; // comment line
    if (fscanf(stdin,"%lf %lf %lf", &(pnts[counter].coord[0]), &(pnts[counter].coord[1]), &(pnts[counter].coord[2])) == 3) {
      /* Check for scan failure */
      if ((pnts[counter].coord[0] == 0.0) || (pnts[counter].coord[1] == 0.0)) {
        continue;
      }
      counter++;
    }
  }

  _cvmsi_data_t *data = malloc(sizeof(_cvmsi_data_t) * MAX_READ_POINTS);
  
  /* Query the model */
  _cvmsi_query(pnts, data, counter);

  /* Display results */
  if(cvmsi_query_debug) {
    printf("longitude latitude depth \n");
    printf("    data[i].xyz.coord[0]+1, data[i].xyz.coord[1]+1, data[i].xyz.coord[2]+1 \n");
    printf("    data[i].prop.vp, data[i].prop.vs, data[i].prop.rho \n");
    printf("    data[i].prop.diff_vp, data[i].prop.diff_vs, data[i].prop.diff_rho\n");
  }

  for (i = 0; i < counter; i++) {
    if(cvmsi_query_debug) {
      printf("%10.4lf %10.4lf %10.4lf \n",
         pnts[i].coord[0], pnts[i].coord[1], pnts[i].coord[2]); 
      printf("    %6d %6d %6d \n", 
         data[i].xyz.coord[0]+1, data[i].xyz.coord[1]+1, data[i].xyz.coord[2]+1);
      printf("    %10.4lf %10.4lf %10.4lf \n",
         data[i].prop.vp, data[i].prop.vs, data[i].prop.rho);
      printf("    %10.4lf %10.4lf %10.4lf \n", 
         data[i].prop.diff_vp, data[i].prop.diff_vs, data[i].prop.diff_rho);
      } else {
        printf("%10.4lf %10.4lf %10.4lf \n",
            data[i].prop.vp, data[i].prop.vs, data[i].prop.rho);
    }

  }

  /* Finalize */
  cvmsi_finalize();
  printf("Model closed successfully.\n");

  return(0);
}
