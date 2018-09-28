#include "OpWaveformCollection.h"



 using namespace wcopreco ;

wcopreco::OpWaveformCollection::OpWaveformCollection(const int nelems)
 : std::vector<OpWaveform> (nelems,0)
  {
    // OpWaveform = std::vector<short> empty_v(10,0);

  }
