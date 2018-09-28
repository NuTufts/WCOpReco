#include "OpWaveformCollection.h"
#include "OpWaveform.h"
#include <vector>

 using namespace wcopreco ;

wcopreco::OpWaveformCollection::OpWaveformCollection(int type_from_Waveform, const int nelems)
 : std::vector<wcopreco::OpWaveform> (nelems,OpWaveform(0, 0.0, 0, (0)))
  {
    type = type_from_Waveform;
  }
