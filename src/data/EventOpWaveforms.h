#ifndef EventOpWaveforms_h
#define EventOpWaveforms_h

#include "OpWaveformCollection.h"
#include "OpWaveform.h"
#include <vector>
#include <map>

namespace wcopreco {

  class EventOpWaveforms {
  public:
    EventOpWaveforms(){};
    virtual ~EventOpWaveforms() {};

    void set__wfm_v(std::vector<OpWaveformCollection>);
    void set__wfm_v(OpWaveformCollection);
    void emplace_back__wfm_v(OpWaveformCollection);
    void emplace_back__wfm_v(std::vector<OpWaveformCollection>);

    void set_type2index(std::map <int,int>);
    void set_index2type(std::map <int,int>);
    void insert_type2index(int type, int index) {type2index.insert(std::pair<int,int>(type,index));};
    void insert_index2type(int index, int type) {index2type.insert(std::pair<int,int>(index,type));};

    void add_entry(OpWaveformCollection, int, int );
    void push_back_wfm( int type, const OpWaveform& wfm );
    // void emplace_back( int type, const OpWaveform& wfm );

    std::vector<OpWaveformCollection> get__wfm_v() {return _wfm_v;};
    std::map <int,int> get_index2type() {return index2type;};
    std::map <int,int> get_type2index() {return type2index;};


  protected:
    std::vector<OpWaveformCollection> _wfm_v;
    std::map <int,int> type2index;
    std::map <int,int> index2type;

  };

}

#endif
