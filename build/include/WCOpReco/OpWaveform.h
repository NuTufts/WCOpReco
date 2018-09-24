#ifndef OPWAVEFORM_H
#define OPWAVEFORM_H

class OpWaveform: public std::vector<short> {
  int ChannelNum
  float time_from_trigger
  int type
};

#endif
