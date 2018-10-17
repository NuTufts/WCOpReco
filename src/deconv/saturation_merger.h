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
    double findBaselineLg(OpWaveform *wfm, int nbin);

    struct timeOrder_wfm{
      bool operator()(const OpWaveform& a, const OpWaveform& b) const
      {return a.get_time_from_trigger() < b.get_time_from_trigger();}
    };
    typedef std::set<OpWaveform,timeOrder_wfm> pmtSet;
    typedef std::map<short,pmtSet> pmtMapSet;
    typedef std::pair<OpWaveform,OpWaveform> pmtPair;
    typedef std::map<short,pmtPair> pmtMapPair;
    pmtMapPair makeBeamPairs(pmtMapSet &high, pmtMapSet &low);

  };

}

#endif
