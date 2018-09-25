#ifndef UBEventWaveform_h
#define UBEventWaveform_h

#include "EventOpWaveforms.h"

class UBEventWaveform: public EventOpWaveforms {
public:

  typedef enum {HGBeam=0, LGBeam, HGCosmic, LGCosmic} UBOpWaveformForm_t;
  
  UBEventWaveform() {};
  virtual ~UBEventWaveform() {};

};

#endif
