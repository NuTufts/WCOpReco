#ifndef FLASHMATCHING_H
#define FLASHMATCHING_H

#include "Flashes_beam.h"
#include "Flashes_cosmic.h"
#include "WCOpReco/Opflash.h"

namespace wcopreco{


  class FlashMatching {
  public:
    FlashMatching(OpflashSelection &cosmic_flashes, OpflashSelection &beam_flashes);
    ~FlashMatching() {};

    OpflashSelection& get_flashes(){return flashes;};

  protected:

    OpflashSelection flashes;

  };

}

#endif
