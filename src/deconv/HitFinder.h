#ifndef HITFINDER_H
#define HITFINDER_H

#include "WCOpReco/DataReader.h"
#include "WCOpReco/COphit.h"

namespace wcopreco{


  class HitFinder {
  public:
    HitFinder(OpWaveformCollection* merged_beam, OpWaveformCollection* merged_cosmic);
    ~HitFinder() {};


  protected:



  };

}

#endif
