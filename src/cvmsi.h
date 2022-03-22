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

#include "ucvm_model_dtypes.h"

/* Constants */
#define CVMSI_MAX_STR_LEN 256
#define CVMSI_MAX_PATH_LEN 1280
#define CVMSI_FORTRAN_MODELDIR_LEN 128

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


// Structures
/** Defines a point (latitude, longitude, and depth) in WGS84 format */
typedef struct cvmsi_point_t {
        /** Longitude member of the point */
        double longitude;
        /** Latitude member of the point */
        double latitude;
        /** Depth member of the point */
        double depth;
} cvmsi_point_t;

/** Defines the material properties this model will retrieve. */
typedef struct cvmsi_properties_t {
        /** P-wave velocity in meters per second */
        double vp;
        /** S-wave velocity in meters per second */
        double vs;
        /** Density in g/m^3 */
        double rho;
        /** NOT USED from basic_property_t */
        double qp;
        /** NOT USED from basic_property_t */
        double qs;
} cvmsi_properties_t;

/** The CVM-SI configuration structure. */
typedef struct cvmsi_configuration_t {
        /** The zone of UTM projection */
        int utm_zone;
        /** The model directory */
        char model_dir[1000];
        /**  The cvms directory */
        char cvms_dir[1000];
} cvmsi_configuration_t;

#ifdef DYNAMIC_LIBRARY

/** Initializes the model */
int model_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int model_finalize();
/** Returns version information */
int model_version(char *ver, int len);
/** Queries the model */
int model_query(cvmsi_point_t *points, cvmsi_properties_t *data, int numpts);
/** Setparam */
int model_setparam(int, int, int);

#endif


// CVMSI Related Functions

/* Initialize */
int cvmsi_init(const char *dir, const char *label);
/* Finalize */
int cvmsi_finalize();
/* Version ID */
int cvmsi_version(char *ver, int len);
/* Query */
int cvmsi_query(cvmsi_point_t *pnt, cvmsi_data_t *data, int numpts);
** Setparam*/
int cvmsi_setparam(int, int, ...);

// Non-UCVM Helper Functions
/** Reads the configuration file. */
int cvmsi_read_configuration(char *file, cvmsi_configuration_t *config);
void cvmsi_print_error(char *err);

* forward declaration */
void utm_geo_(double*, double*, double*, double*, int*, int*);

#endif
