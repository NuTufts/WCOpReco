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

  class UBEventWaveform : public EventOpWaveForms {
  public:

    typedef enum {kbeam_hg = 0, kbeam_lg, kcosmic_hg, kcosmic_lg, kNumTypes } UBOpWaveformForm_t;

    UBEventWaveform();
    virtual ~UBEventWaveform() {};

    void addWaveform( UBOpWaveformForm_t type, const OpWaveform& wfm );
    
  /*   void read_in_data(std::string file); */
  /* protected: */
  /*   std::vector<EventOpWaveforms> _EvOpwfms_v; */

  /* private: */

  /*   //need functions here to get data that we want */
  /*   //add data that we want. */
  /*   //In data reader, we'll just call this class to fill in the data into objects. */

  /*   int eventNo; */

  /*   void LoopThroughWfms_UB(std::vector<short> ch, */
  /*     std::vector<double> timestamp, */
  /*     TClonesArray Eventwaveform, */
  /*     int type, */
  /*     OpWaveformCollection &wfm_collection); */

  /*   void fill_EventWfms(std::string st_opch, */
  /*     std::string st_timestamp, */
  /*     std::string st_wf, */
  /*     UBEventWaveform::UBOpWaveformForm_t st_gain, */
  /*     TTree * tree); */

  /*   void IAMTHENIGHT(); */
  };

}

#endif
