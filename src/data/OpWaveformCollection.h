#ifndef OPWAVEFORMCOLLECTION_H
#define OPWAVEFORMCOLLECTION_H

#include "OpWaveform.h"
#include <vector>

namespace wcopreco {

  class OpWaveformCollection : public std::vector<short> {

  public:
    OpWaveformCollection(int type_from_Waveform, const int nelems);
    virtual ~OpWaveformCollection() {};


    int get_type() {return type;};

  protected:
    int type;
    //void clear_opreco() {};
    //void pushback_opreco() {};
  };

}

#endif
