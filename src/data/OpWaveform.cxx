#include "OpWaveform.h"


using namespace wcopreco;

wcopreco::OpWaveform::OpWaveform(int ChanNum, double time_from_trig, int typ, const std::vector<short>& wfm)
 : std::vector<short>(wfm)
  {
    ChannelNum = ChanNum;
    time_from_trigger = time_from_trig;
    type = typ;
  }
