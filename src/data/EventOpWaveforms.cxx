#include "EventOpWaveforms.h"
#include "OpWaveformCollection.h"
#include "OpWaveform.h"
#include <vector>
#include <map>


using namespace wcopreco ;

void wcopreco::EventOpWaveforms::set_type2index(std::map <int,int> input_map)
  {type2index = input_map;}

void wcopreco::EventOpWaveforms::set_index2type(std::map <int,int> input_map)
  {index2type = input_map;}

void wcopreco::EventOpWaveforms::set__wfm_v(std::vector<OpWaveformCollection> input_vector)
  {_wfm_v = input_vector;}

void wcopreco::EventOpWaveforms::set__wfm_v(OpWaveformCollection input_collection)
  {
    _wfm_v.resize(0);
    _wfm_v.emplace_back(std::move(input_collection));
  }

void wcopreco::EventOpWaveforms::emplace_back__wfm_v(OpWaveformCollection input_collection)
  {_wfm_v.emplace_back(std::move(input_collection));}

void wcopreco::EventOpWaveforms::emplace_back__wfm_v(std::vector<OpWaveformCollection> input_vector_collection)
  {
    //This may not be the most efficient way to perform this whole function:

    _wfm_v.resize( _wfm_v.size() + input_vector_collection.size() );

    for (int i = 0; i<input_vector_collection.size(); i++) {

      _wfm_v.emplace_back(std::move(input_vector_collection[i]));

    }
  }
void wcopreco::EventOpWaveforms::add_entry(OpWaveformCollection input_collection, int index, int type ) {
    _wfm_v.emplace_back(std::move(input_collection));
    type2index.insert(std::pair<int,int>(type,index));
    index2type.insert(std::pair<int,int>(index,type));
  }
