#!/bin/bash

export WCOPRECO_BASEDIR=$(pwd)
export WCOPRECO_BUILDDIR=${WCOPRECO_BASEDIR}/build
export WCOPRECO_INCDIR=${WCOPRECO_BUILDDIR}/include
export WCOPRECO_LIBDIR=${WCOPRECO_BUILDDIR}/lib
export WCOPRECO_BINDIR=${WCOPRECO_BUILDDIR}/bin

# clean up previously set env
if [[ -z $EIGEN_INC ]]; then
    where="/usr/includes/eigen3"
    export EIGEN_INCDIR=${where}
else
    export EIGEN_INCDIR=$EIGEN_INC
fi


[[ ":$LD_LIBRARY_PATH:" != *":${WCOPRECO_LIBDIR}:"* ]] && export LD_LIBRARY_PATH="${WCOPRECO_LIBDIR}:${LD_LIBRARY_PATH}"
[[ ":$PATH:" != *":${WCOPRECO_BINDIR}:"* ]] && export PATH="${WCOPRECO_BINDIR}:${PATH}"


