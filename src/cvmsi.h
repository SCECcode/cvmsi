#ifndef CVMSI_H
#define CVMSI_H

/**
 * @file cvmsi.h
 * @brief Main header file for CVMSI library.
 * @author - SCEC
 * @version
 *
 *
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Constants */
#define CVMSI_MAX_STR_LEN 256

/* Max array size for Z dimension */
#define CVMSI_MAX_ZGRID 3000

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Point structure */
typedef struct cvmsi_point_t {
  double coord[3];
} cvmsi_point_t;


/* Index structure */
typedef struct cvmsi_index_t {
  int coord[3];
} cvmsi_index_t;


/* Full property structure */
typedef struct cvmsi_prop_t {
  float vp;
  float vs;
  float rho;
  float diff_vp;
  float diff_vs;
  float diff_rho;
} cvmsi_prop_t;

/* Property structure for read-in */
typedef struct cvmsi_prop_read_t {
	float vp;
	float vs;
} cvmsi_prop_read_t;

/* Return data structure */
typedef struct cvmsi_data_t {
  cvmsi_index_t xyz;
  cvmsi_prop_t prop;
} cvmsi_data_t;


/* Initialize */
int cvmsi_init(const char *dir);

/* Finalize */
int cvmsi_finalize();

/* Version ID */
int cvmsi_version(char *ver, int len);

/* Query */
int cvmsi_query(cvmsi_point_t *pnt, cvmsi_data_t *data, int numpts);


#endif
