#ifndef UB_SPE_H
#define UB_SPE_H

#include "spe_shape.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

namespace wcopreco {

  class UB_spe : public spe_shape {
  public:
     UB_spe() {};
     virtual ~UB_spe() {};

    std::vector<float> Get_wfm(int nbins, float tick_width_ns);
    std::vector<float> Get_pow_spec(int nbins, float tick_width_ns);
    float gain;

  protected:



  };

}

#endif
