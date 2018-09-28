#include "OpWaveformCollection.h"
#include "OpWaveform.h"
#include <vector>

 using namespace wcopreco ;

wcopreco::OpWaveformCollection::OpWaveformCollection(int type_from_Waveform, const int nelems)
 : std::vector<short> (nelems)
  {
    type = type_from_Waveform;
  }
