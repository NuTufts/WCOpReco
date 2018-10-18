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
    // typedef std::vector<std::pair<short,short> > saturationTick;
    float findScaling(int channel);
    void scale_lowgains(OpWaveformCollection *BLG, OpWaveformCollection *CLG);
    double findBaselineLg(OpWaveform *wfm, int nbin);
    std::vector<std::pair<short,short> > findSaturationTick(OpWaveform *wfm, short saturation_threshold );
    OpWaveform replaceSaturatedBin(OpWaveform &high, OpWaveform &low, std::vector<std::pair<short,short>> saturation_ranges);

    OpWaveformCollection* cosmic_merger(OpWaveformCollection *CHG, OpWaveformCollection *CLG, short saturation_threshold =4080);

    OpWaveformCollection* beam_merger(OpWaveformCollection *BHG, OpWaveformCollection *BLG, short saturation_threshold=4080);
    //This function is designed to merge a OpWaveformCollection of Beam High Gain Waveforms
    //with Beam Low Gain Waveforms. High gains are the first argument, and low gains are the
    //second argument. It also assumes the elements in the collection are ordered by channel



  };

}

#endif
