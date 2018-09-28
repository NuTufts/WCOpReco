#ifndef EventOpWaveforms_h
#define EventOpWaveforms_h

#include "OpWaveformCollection.h"
#include "OpWaveform.h"
#include <vector>
#include <map>

namespace wcopreco {

  class EventOpWaveforms{
  public:
    EventOpWaveforms();
    virtual ~EventOpWaveforms() {};

  protected:
    std::vector<OpWaveformCollection> _wfm_v;
    //A map linking indices to the type of WaveformCollection
    std::map <int,int> type2index;

  };

}

#endif
