#ifndef SATURATION_MERGER_H
#define SATURATION_MERGER_H

#include "WCOpReco/DataReader.h"

namespace wcopreco{


  class saturation_merger {
  public:
    saturation_merger(UBEventWaveform);
    ~saturation_merger() {};

    // makebeampair(){};
    // makecosmicpai(){};
    // mergebeam(){};
    // mergecosmic(){};

  protected:
    float findScaling(int channel);
    void scale_lowgains(OpWaveformCollection *BLG, OpWaveformCollection *CLG);
    double findBaselineLg(OpWaveform *wfm, int nbin)
;
  };

}

#endif
