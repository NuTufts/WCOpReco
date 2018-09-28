#ifndef UBEventWaveform_h
#define UBEventWaveform_h

#include "EventOpWaveforms.h"

namespace wcopreco {

  class UBEventWaveform {
  public:

    typedef enum {HGBeam=0, LGBeam, HGCosmic, LGCosmic} UBOpWaveformForm_t;

    UBEventWaveform() {};
    virtual ~UBEventWaveform() {};

  private:
    //need functions here to get data that we want
    //add data that we want.
    //In data reader, we'll just call this class to fill in the data into objects.

  };

}

#endif
