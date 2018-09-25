#ifndef EventOpWaveforms_h
#define EventOpWaveforms_h

#include "OpWaveformCollection.h"
#include <vector>
#include <map>

class EventOpWaveforms: public std::vector<OpWaveformCollection> {
public:
  EventOpWaveforms();
  ~EventOpWaveforms();

  //A map linking indices to the type of WaveformCollection
  std::map<int,int> type2index;


};

#endif
