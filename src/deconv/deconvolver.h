#ifndef DECONVOLVER_H
#define DECONVOLVER_H

//deconv functions
#include "kernel_fourier.h"
#include "kernel_fourier_container.h"
#include "noise_remover.h"
#include "noise_container.h"
#include "UB_spe.h"
#include "UB_rc.h"

//data
#include "DataReader.h"

//c++ includes
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

namespace wcopreco{


  class deconvolver {
  public:
    deconvolver() {}; //OpWaveform op_wfm, kernel_fourier_shape kernel_fourier, noise_remover noise, std::vector<short???> LL_shape
    ~deconvolver() {};

    void deconv_test();










  protected:

  };

}
#endif
