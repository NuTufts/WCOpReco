#ifndef OPWAVEFORM_H
#define OPWAVEFORM_H

#include <vector>

namespace wcopreco {

  class OpWaveform : public std::vector<short> {
  public:
    OpWaveform(int ChanNum, double time_from_trig, int typ, const std::vector<short>& wfm );

    OpWaveform(int ChanNum, double time_from_trig, int typ, const int nelems );
    virtual ~OpWaveform() {};

    int get_ChannelNum() {return ChannelNum;};
    double get_time_from_trigger() {return time_from_trigger;};
    int get_type() {return type;};
    int set_ChannelNum(int ch) {ChannelNum = ch;};
    int set_time_from_trigger(int time_diff) {time_from_trigger = time_diff;};
    int set_type(int typ) {type = typ;};



  protected:
    int ChannelNum;
    double time_from_trigger;
    int type;
  };

}

#endif
