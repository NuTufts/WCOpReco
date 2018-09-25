#ifndef OPWAVEFORM_H
#define OPWAVEFORM_H

#include <vector>

namespace wcopreco {

  class OpWaveform : public std::vector<short> {
  public:
    OpWaveform() {};
    virtual ~OpWaveform() {};
    
  protected:
    int ChannelNum;
    float time_from_trigger;
    int type;
  };
  
}

#endif
