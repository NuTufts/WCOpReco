#ifndef OPWAVEFORM_H
#define OPWAVEFORM_H

#include <vector>

namespace wcopreco {

  class OpWaveform : public std::vector<short> {
  public:
    OpWaveform(int ChanNum, double time_from_trig, int typ);
    virtual ~OpWaveform() {};

    int get_ChannelNum() {return ChannelNum;};
    double get_time_from_trigger() {return time_from_trigger;};
    int get_type() {return type;};

  protected:
    int ChannelNum;
    double time_from_trigger;
    int type;
  };

}

#endif
