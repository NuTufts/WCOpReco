#ifndef UB_NOISEREM_H
#define UB_NOISEREM_H

#include "noise_remover.h"
#include "WCOpReco/OpWaveform.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

namespace wcopreco {

  class UB_noiserem : public noise_remover {
  public:
     UB_noiserem() {};
     virtual ~UB_noiserem() {};

    std::vector<float> Get_wfm(int nbins, float tick_width_ns);
    float Get_baseline(OpWaveform wfm);
    void Remove_baseline(OpWaveform wfm, float baseline);

    float gain;

  protected:

  };

}
#endif
