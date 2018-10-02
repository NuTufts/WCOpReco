#include "OpWaveformCollection.h"
#include "OpWaveform.h"
#include <vector>

 using namespace wcopreco ;

wcopreco::OpWaveformCollection::OpWaveformCollection()
 : std::vector<OpWaveform> (0,OpWaveform(0, 0.0, 0, (0)))
  {
    reserve(500);
  }
