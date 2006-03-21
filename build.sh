#!/bin/bash
./autogen.sh
AXIS2C_HOME=`pwd`/deploy
./configure --prefix=${AXIS2C_HOME} --enable-tests=yes --enable-trace=yes  --with-apache2=/usr/include/apache2 --with-apr=/usr/include/apr-0
make
make install
cd samples
sh build.sh
cd ..
