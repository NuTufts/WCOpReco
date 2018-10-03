#ifndef UB_SPE_H
#define UB_SPE_H

#include "kernel_fourier.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

namespace wcopreco {

  class UB_spe : public kernel_fourier {
  public:
     UB_spe(std::string nm, bool mult_flag);
     virtual ~UB_spe() {};

    std::vector<float> Get_wfm(int nbins, float tick_width_ns);
    std::vector<float> Get_pow_spec(int nbins, float tick_width_ns);
    float gain;

  protected:



  };

}

#endif
