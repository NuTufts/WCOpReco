#ifndef EventOpWaveforms_h
#define EventOpWaveforms_h

#include "WaveformCollection.h"
#include <vector>

class EventOpWaveforms: public std::vector<WaveformCollection> {
public:
  EventOpWaveforms();
  ~EventOpWaveforms();

  //A map linking indices to the type of WaveformCollection
  map<int,int> type2index;

}
