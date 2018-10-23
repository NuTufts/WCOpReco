#include "OpWaveform.h"
#include <vector>

using namespace wcopreco;

wcopreco::OpWaveform::OpWaveform(int ChanNum, double time_from_trig, int typ, const std::vector<double>& wfm)
 : std::vector<double> (wfm)
  {
    // OpWaveform = std::vector<short> empty_v(10,0);
    ChannelNum = ChanNum;
    time_from_trigger = time_from_trig;
    type = typ;
  }


wcopreco::OpWaveform::OpWaveform(int ChanNum, double time_from_trig, int typ, const int nelems)
 : std::vector<double> (nelems,0)
  {
    // OpWaveform = std::vector<short> empty_v(10,0);
    ChannelNum = ChanNum;
    time_from_trigger = time_from_trig;
    type = typ;
  }
