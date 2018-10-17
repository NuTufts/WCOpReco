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

    void set_channel2index(std::map <int,int>);
    void set_index2channel(std::map <int,int>);
    void insert_channel2index(int channel, int index) {channel2index.insert(std::pair<int,int>(channel,index));};
    void insert_index2channel(int index, int channel) {index2channel.insert(std::pair<int,int>(index,channel));};
    std::map <int,int> get_index2channel() {return index2channel;};
    std::map <int,int> get_channel2index() {return channel2index;};

  protected:

    std::map <int,int> channel2index;
    std::map <int,int> index2channel;

  };

}

#endif
