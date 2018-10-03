#include "noise_remover.h"

using namespace wcopreco;

noise_remover::noise_remover(int type, int ch, double timestamp)
  {
    // OpWaveform = std::vector<short> empty_v(10,0);
    ChannelNum = ch;
    time_from_trigger = timestamp;
    event_type = type;
  }
