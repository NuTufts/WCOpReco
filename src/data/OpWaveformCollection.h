#ifndef OPWAVEFORMCOLLECTION_H
#define OPWAVEFORMCOLLECTION_H

#include "OpWaveform.h"
#include <vector>

namespace wcopreco {

  class OpWaveformCollection : public std::vector<OpWaveform> {

  public:
    OpWaveformCollection();
    virtual ~OpWaveformCollection() {};


  protected:

    //void clear_opreco() {};
    //void pushback_opreco() {};
  };

}

#endif
