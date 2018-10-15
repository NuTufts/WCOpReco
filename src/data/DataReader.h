#ifndef DATAREADER_H
#define DATAREADER_H

#include "EventOpWaveforms.h"
#include <string>
#include "OpWaveform.h"
#include "OpWaveformCollection.h"
#include "EventOpWaveforms.h"
#include "UBEventWaveform.h"


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
#include "TCanvas.h"


#include <iostream>
#include <sstream>
#include <vector>
#include <string>

namespace wcopreco  {

  class DataReader {
  public:
    DataReader(std::string filepath);
    ~DataReader() {};

    UBEventWaveform Reader(int event_num);

    void LoopThroughWfms(std::vector<short> ch,
      std::vector<double> timestamp,
      TClonesArray Eventwaveform,
      int type,
      OpWaveformCollection &wfm_collection);

    void IAMTHENIGHT();

    //Make a bunch of root reading datamembers:
    Int_t nevents;
    TFile *file;
    TTree *tree;
    //These will be branches we'll need to read
    std::vector<short> * cosmic_hg_opch = 0; //or =NULL if it complains
    std::vector<short> * cosmic_lg_opch = 0; //or =NULL if it complains
    std::vector<short> * beam_hg_opch = 0; //or =NULL if it complains
    std::vector<short> * beam_lg_opch = 0; //or =NULL if it complains

    std::vector<double> * cosmic_hg_timestamp = 0; //or =NULL if it complains
    std::vector<double> * cosmic_lg_timestamp = 0; //or =NULL if it complains
    std::vector<double> * beam_hg_timestamp = 0; //or =NULL if it complains
    std::vector<double> * beam_lg_timestamp = 0; //or =NULL if it complains

    TClonesArray * cosmic_hg_wf;
    TClonesArray * cosmic_lg_wf;
    TClonesArray * beam_hg_wf;
    TClonesArray * beam_lg_wf;
    int eventNo;

    UBEventWaveform _UB_Ev_wfm;
    int type;

  protected:

  };

}
#endif
