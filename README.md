# CVM-S4.26.M01 (cvmsi)

<a href="https://github.com/sceccode/cvmsi.git"><img src="https://github.com/sceccode/cvmsi/wiki/images/cvmsi_logo.png"></a>

[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
![GitHub repo size](https://img.shields.io/github/repo-size/sceccode/cvmsi)
[![cvmsi-ucvm-ci Actions Status](https://github.com/SCECcode/cvmsi/workflows/cvmsi-ucvm-ci/badge.svg)](https://github.com/SCECcode/cvmsi/actions)

Tomography improved Southern California Velocity Model developed
by SCEC, Caltech and USGS with geotechnical layer

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
  cd data; ./make_data_files.py
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



