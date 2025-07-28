# CVM-S4.26.M01 (cvmsi)

<a href="https://github.com/sceccode/cvmsi.git"><img src="https://github.com/sceccode/cvmsi/wiki/images/cvmsi_logo.png"></a>

[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
![GitHub repo size](https://img.shields.io/github/repo-size/sceccode/cvmsi)
[![cvmsi-ucvm-ci Actions Status](https://github.com/SCECcode/cvmsi/workflows/cvmsi-ucvm-ci/badge.svg)](https://github.com/SCECcode/cvmsi/actions)

Tomography improved Southern California Velocity Model developed
by SCEC, Caltech and USGS with geotechnical layer

CVM-S4.26.M01 is a 3D seismic velocity model based upon CVM-S4.26 which is a tomography improved version of the CVM-S4 model. CVM-S4.26.M01 preserves some of the geotechnical information in the original CVM-S4 model that was lost during the tomography improvements used to create CVM-S4.26. The CVM-S4.26.M01 model combines material properties from the CVM-S4.26 model by Chen et al (2011) together with near surface properties from the original CVM-S4 model. The goal of the CVM-S4.26.M01 model is to generate high resolution velocity meshes (<100m mesh spacing) for use in high frequency ground motion simulations from the low resolution CVM-S4.26 perturbation model. The CVM-S4.26 tomographic process imposed a minimum Vs of 1000m/s and it was performed on a 500m grid. The CVM-S4 geotechnical information is rule based and therefore arbitrary precision. The CVM-S4.26.M01 model integrates CVM-S4.26 perturbations while still honoring the CVM-S4 geotechnical layer (GTL) information in the top 350m. The desired effect is to recover the CVM-S GTL while smoothly adding in positive and negative perturbations of the CVM-S4.26 model. The M01 refers to the method developed to merge the arbitrary near surface information in the top 350m from CVM-S4 into the lower resolution (500m) properties from CVM-S4.26. Since the perturbations were calculated using a Vs minimum of 1000m/s, in certain areas of CVM-S (like boreholes), doing a straight trilinear interpolation of the perturbations with the CVM-S material properties can result in negative Vs and/or Vp values, so specific rules were introduced to avoid these issues. The resulting model, called CVM-S4.26.M01, implements rules to smoothly merge the near surface properties from CVM-S4 in the top 350m with the tomography improved model in CVM-S4.26. Below 350m, CVM-S4.26 and CVM-S4.26.M01 are expected to return identical properties.

Lee, E.-J., P. Chen, T. H. Jordan, P. J. Maechling, M. A. M. Denolle, and G. C.Beroza (2014), Full 3-D tomography for crustal structure in Southern California based on the scattering-integral and the adjoint-wavefield methods, J. Geophys. Res. Solid Earth, 119, doi:10.1002/2014JB011346. SCEC Contribution 6093

Taborda, R., Olsen, K. B., Graves, R. W., Silva, F., Khoshnevis, N., Savran, W. H., Roten, D., Shi, Z., Goulet, C. A., Bielak, J., Maechling, P. J., Cui, Y., & Jordan, T. H. (2016, 09). Verification and Validation of High-Frequency (fmax = 5 Hz) Ground Motion Simulations of the 2014 M 5.1 La Habra, California, earthquake. Poster Presentation at 2016 SCEC Annual Meeting.

## Installation

This package is intended to be installed as part of the UCVM framework,
version 25.7 or higher.

## Library

The library ./lib/libcvmsi.a may be statically linked into any
user application. Also, if your system supports dynamic linking,
you will also have a ./lib/libcvmsi.so file that can be used
for dynamic linking. The header file defining the API is located
in ./include/cvmsi.h.

## Contact the authors

If you would like to contact the authors regarding this software,
please e-mail software@scec.org. Note this e-mail address should
be used for questions regarding the software itself (e.g. how
do I link the library properly?). Questions regarding the model's
science (e.g. on what paper is the CVM-S4.26.M01 based?) should be directed
to the model's authors, located in the AUTHORS file.


## To build in standalone mode

To install this package on your computer, please run the following commands:

<pre>
  aclocal
  autoconf
  automake --add-missing --force-missing
  ./configure --prefix=/path/to/install
  make
  make install
</pre>

## Usage

### cvmsi_query

ASCII query interface accepts points from stdin with format (lat, lon, dep (m))



