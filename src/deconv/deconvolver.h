#ifndef DECONVOLVER_H
#define DECONVOLVER_H

#include "spe_shape.h"
#include "spe_container.h"
#include "noise_remover.h"
#include "noise_container.h"
#include "UB_spe.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

namespace wcopreco{


  class deconvolver {
  public:
    deconvolver() {}; //OpWaveform op_wfm, spe_shape spe, noise_remover noise, std::vector<short???> LL_shape
    ~deconvolver() {};

    void deconv_test();










  protected:

  };

}
#endif
