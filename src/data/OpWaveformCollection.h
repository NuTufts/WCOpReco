#ifndef OPWAVEFORMCOLLECTION_H
#define OPWAVEFORMCOLLECTION_H

#include "OpWaveform.h"
#include <vector>
#include <map>

namespace wcopreco {

  class OpWaveformCollection : public std::vector<OpWaveform> {

  public:
    OpWaveformCollection();
    virtual ~OpWaveformCollection() {};

    void set_channel2index(std::map <int,std::vector<int>>);
    void set_index2channel(std::map <int,int>);
    void insert_channel2index(int channel, int index) {
      std::vector<int> v = channel2index[channel];
      v.emplace_back(index);
      channel2index.insert(std::pair<int,std::vector<int>>(channel,v));
    };
    void insert_index2channel(int index, int channel) {index2channel.insert(std::pair<int,int>(index,channel));};
    std::map <int,int> get_index2channel() {return index2channel;};
    std::map <int,std::vector<int>> get_channel2index() {return channel2index;};

  protected:

    std::map <int,std::vector<int>> channel2index;
    std::map <int,int> index2channel;

  };

}

#endif
