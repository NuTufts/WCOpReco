#include "UBEventWaveform.h"
#include "EventOpWaveforms.h"
#include "OpWaveformCollection.h"
namespace wcopreco {

   UBEventWaveform::UBEventWaveform()  {

    // setup the eventwaveform map for our types
    EventOpWaveforms::_wfm_v.resize(4);
    //  Map elements added when you add waveform collections
    // insert_type2index( kbeam_hg, 0 );
    // insert_type2index( kbeam_lg, 1 );
    // insert_type2index( kcosmic_hg, 2 );
    // insert_type2index( kcosmic_lg, 3 );
    //
    // insert_index2type( 0, kbeam_hg  );
    // insert_index2type( 1, kbeam_lg );
    // insert_index2type( 2, kcosmic_hg );
    // insert_index2type( 3, kcosmic_lg );

  }

  void UBEventWaveform::addWaveform( UBOpWaveformForm_t type, const OpWaveform& wfm ) {
    push_back_wfm( (int)type, wfm );
  }

}
