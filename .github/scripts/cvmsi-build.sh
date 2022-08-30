#!/bin/bash

tmp=`uname -s`

if [ $tmp == 'Darwin' ]; then
##for macOS, make sure have automake/aclocal
  brew install automake
  brew reinstall gcc
fi

cd data
./make_data_files.py
cd ..

aclocal
automake --add-missing
autoconf
./configure --prefix=$UCVM_INSTALL_PATH/model/cvmsi
make
make install

