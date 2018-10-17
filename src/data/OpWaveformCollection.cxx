#include "OpWaveformCollection.h"
#include "OpWaveform.h"

#include <vector>
#include <map>

namespace wcopreco{

  OpWaveformCollection::OpWaveformCollection()
   : std::vector<OpWaveform> (0,OpWaveform(0, 0.0, 0, (0)))
    {
      reserve(500);
    }

  void OpWaveformCollection::set_channel2index(std::map <int,int> input_map)
  {channel2index = input_map;}

  void OpWaveformCollection::set_index2channel(std::map <int,int> input_map)
  {index2channel = input_map;}

};
