#ifndef HITFINDER_H
#define HITFINDER_H

#include "WCOpReco/DataReader.h"
#include "WCOpReco/COphit.h"
#include "WCOpReco/Opflash.h"

namespace wcopreco{


  class HitFinder {
  public:
    HitFinder(OpWaveformCollection* merged_cosmic, std::vector<float> *op_gain,std::vector<float> *op_gainerror);
    ~HitFinder() {};

    OpflashSelection              get_cosmic_flashes() {return cosmic_flashes;}
    std::vector<COphitSelection>  get_ophits_group() {return ophits_group;}
    COphitSelection               get_left_ophits() {return left_ophits;}
    COphitSelection               get_op_hits(){return op_hits;}

  protected:
    OpflashSelection cosmic_flashes;
    std::vector<COphitSelection> ophits_group;
    COphitSelection left_ophits;
    COphitSelection op_hits;



  };

}

#endif
