#ifndef OPWAVEFORMCOLLECTION_H
#define OPWAVEFORMCOLLECTION_H

#include "OpWaveform.h"
#include <vector>

class OpWaveformCollection : public std::vector<OpWaveform> {
  void clear_opreco();
  void pushback_opreco();
};

#endif
