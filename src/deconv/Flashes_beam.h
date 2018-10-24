#ifndef FLASHES_BEAM_H
#define FLASHES_BEAM_H

#include "WCOpReco/DataReader.h"
#include "WCOpReco/Opflash.h"
#include "HitFinder_beam.h"

namespace wcopreco{


  class Flashes_beam {
  public:
    Flashes_beam(std::vector<COphitSelection> ophits_group);
    ~Flashes_beam() {};

    OpflashSelection get_beam_flashes(){return beam_flashes;};

  protected:

    OpflashSelection beam_flashes;

  };

}

#endif
