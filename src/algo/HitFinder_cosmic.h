#ifndef HITFINDER_COSMIC_H
#define HITFINDER_COSMIC_H

//data
#include "WCOpReco/OpWaveform.h"
#include "WCOpReco/OpWaveformCollection.h"
#include "WCOpReco/EventOpWaveforms.h"
#include "WCOpReco/COphit.h"

#include "WCOpReco/Config_COpHit.h"
#include "WCOpReco/Config_Hitfinder_Cosmic.h"

namespace wcopreco{


  class HitFinder_cosmic {
  public:
    HitFinder_cosmic(OpWaveformCollection* merged_cosmic,
                    std::vector<float> *op_gain,
                    std::vector<float> *op_gainerror ,
                    const Config_Hitfinder_Cosmic &configHC,
                    const Config_COpHit &configCOpH);
    ~HitFinder_cosmic() {};

    std::vector<COphitSelection>  get_ophits_group() {return ophits_group;}
    COphitSelection               get_left_ophits() {return left_ophits;}
    COphitSelection               get_op_hits(){return op_hits;}

  protected:

    std::vector<COphitSelection> ophits_group;
    COphitSelection left_ophits;
    COphitSelection op_hits;

    Config_Hitfinder_Cosmic _cfgHC;
    Config_COpHit _cfgCOpH;



  };

}

#endif
