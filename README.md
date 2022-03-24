# The Tomography improved Southern California Velocity Model with geotechnical layer (cvmsi)

<a href="https://github.com/sceccode/cvmsi.git"><img src="https://github.com/sceccode/cvmsi/wiki/images/cvmsi_logo.png"></a>

[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
![GitHub repo size](https://img.shields.io/github/repo-size/sceccode/cvmsi)
[![cvmsi-ci Actions Status](https://github.com/SCECcode/cvmsi/workflows/cvmsi-ci/badge.svg)](https://github.com/SCECcode/cvmsi/actions)
[![cvmsi-ucvm-ci Actions Status](https://github.com/SCECcode/cvmsi/workflows/cvmsi-ucvm-ci/badge.svg)](https://github.com/SCECcode/cvmsi/actions)

## Description

Tomography improved Southern California Velocity Model developed
by SCEC, Caltech and USGS with geotechnical layer

## Table of Contents
1. [Software Documentation](https://github.com/SCECcode/cvmsi/wiki)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Contributing](#contributing)
5. [Credits](#credit)
6. [License](#license)

## Installation

This package is intended to be installed as part of the UCVM framework,
version 19.4.0 or higher. 

This package can also be build as a standalone program

<pre>
$ aclocal
$ autoconf
$ automake
$ ./configure --prefix=/path/to/install
$ make
$ make install
</pre>

## Usage

### UCVM

As part of [UCVM](https://github.com/SCECcode/ucvm) installation, use 'cvmsi' as the model.

### cvmsi_query

ASCII query interface accepts points from stdin with format (lat, lon, dep (m))

## Support
Support for CVMSI is provided by the Southern California Earthquake Center
(SCEC) Research Computing Group.  Users can report issues and feature requests
using CVMSI's github-based issue tracking link below. Developers will also
respond to emails sent to the SCEC software contact listed below.
1. [CVMSI Github Issue Tracker](https://github.com/SCECcode/cvmsi/issues)
2. Email Contact: software@scec.usc.edu

## Credits

## Contributing
We welcome contributions to the CVMSI, please contact us at software@scec.usc.edu.

## License
This software is distributed under the BSD 3-Clause open-source license.
Please see the [LICENSE.txt](LICENSE.txt) file for more information.
