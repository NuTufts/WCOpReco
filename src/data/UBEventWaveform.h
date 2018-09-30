#ifndef UBEventWaveform_h
#define UBEventWaveform_h

#include "EventOpWaveforms.h"
#include <string>
#include "OpWaveform.h"
#include "OpWaveformCollection.h"
#include "EventOpWaveforms.h"
#include "UBEventWaveform.h"
#include "datareader_j.h"

//root includes
#include "TObject.h"
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TTimeStamp.h"

#include <iostream>
#include <sstream>

/*Structure
(This section written by Josh during nightshift, treat all content with skepticism):

UBEventWaveform has datamember _EvOpwfms_v which is a vector<EventOpWaveforms>
Each EventOpWaveforms has a datamember _wfm_v which is a vector<OpWaveformCollection>
Recall that OpWaveformCollection inherits from vector, so it DOESNT hold a datamember vector, instead it acts like a vector
Therefore OpWaveformCollection acts like a vector<OpWaveform>
Then Recall OpWaveform inherits from vector, and it's vector contains signal hit information
Each OpWaveform also has datamembers ChannelNum, time_from_trigger, type
*/

namespace wcopreco {

  class UBEventWaveform {
  public:

    typedef enum {HGBeam=0, LGBeam, HGCosmic, LGCosmic} UBOpWaveformForm_t;

    UBEventWaveform() {};
    virtual ~UBEventWaveform() {};
    void read_in_data(std::string filepath);
  protected:
    std::vector<EventOpWaveforms> _EvOpwfms_v;

  private:

    //need functions here to get data that we want
    //add data that we want.
    //In data reader, we'll just call this class to fill in the data into objects.

    int eventNo;
    std::vector<short int> cosmic_hg_opch;
    std::vector<short int> cosmic_lg_opch;
    std::vector<short int> beam_hg_opch;
    std::vector<short int> beam_lg_opch;

    std::vector<double> cosmic_hg_timestamp;
    std::vector<double> cosmic_lg_timestamp;
    std::vector<double> beam_hg_timestamp;
    std::vector<double> beam_lg_timestamp;

    void LoopThroughWfms_UB(std::vector<short> ch,
      std::vector<double> timestamp,
      TClonesArray Eventwaveform,
      int type,
      OpWaveformCollection &wfm_collection);

    void IAMTHENIGHT();
  };

}

#endif
