#ifndef FLASHES_COSMIC_H
#define FLASHES_COSMIC_H

#include "WCOpReco/DataReader.h"
#include "WCOpReco/COphit.h"
#include "WCOpReco/Opflash.h"
#include "WCOpReco/HitFinder_cosmic.h"

namespace wcopreco{


  class Flashes_cosmic {
  public:
    Flashes_cosmic(std::vector<COphitSelection> ophits_group);
    ~Flashes_cosmic() {};

    OpflashSelection get_cosmic_flashes(){return cosmic_flashes;};

  protected:

    OpflashSelection cosmic_flashes;

  };

}

#endif
