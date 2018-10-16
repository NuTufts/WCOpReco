#!/bin/bash

export WC_BASEDIR=$PWD
export DEVDIR=${WC_BASEDIR}/dev

# OPENCV
export OPENCV_LIBDIR=/usr/local/lib
export OPENCV_INCDIR=/usr/local/include
export USE_OPENCV=1

# setup wc libs
export WC_LIBDIR=${WC_BASEDIR}
[[ ":$LD_LIBRARY_PATH:" != *":${WC_LIBDIR}:"* ]] && LD_LIBRARY_PATH="${WC_LIBDIR}:${LD_LIBRARY_PATH}"

# SETUP EIGEN
export EIGEN_INC_DIR=/usr/include/eigen3
export EIGEN_LIB_DIR=
