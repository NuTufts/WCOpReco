#include "OpWaveformCollection.h"
#include "OpWaveform.h"
#include <vector>

 using namespace wcopreco ;

wcopreco::OpWaveformCollection::OpWaveformCollection()
 : std::vector<wcopreco::OpWaveform> (500,OpWaveform(0, 0.0, 0, (0)))
  {}
