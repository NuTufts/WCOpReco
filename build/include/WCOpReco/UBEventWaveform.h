#ifndef UBEventWaveform_h
#define UBEventWaveform_h

#include "EventOpWaveforms.h"

class UBEventWaveform: public EventOpWaveforms {
public:
  UBEventWaveform();
  ~UBEventWaveform();
  enum {HGBea=0, LGBeam, HGCosmic, LGCosmic};

}
