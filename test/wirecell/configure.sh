#!/bin/bash
export WC_BASEDIR=$(pwd)
export WC_BUILDDIR=$(pwd)
export WC_INCDIR=$(pwd)
export WC_LIBDIR=$(pwd)
export WC_BINDIR=$(pwd)
[[ ":$LD_LIBRARY_PATH:" != *":${WC_LIBDIR}:"* ]] && export LD_LIBRARY_PATH="${WC_LIBDIR}:${LD_LIBRARY_PATH}"
[[ ":$PATH:" != *":${WC_BINDIR}:"* ]] && export PATH="${WC_BINDIR}:${PATH}"
