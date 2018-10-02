#ifndef DATAREADER_H
#define DATAREADER_H

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
#include <vector>
#include <string>

namespace wcopreco  {

  class DataReader {
  public:
    DataReader() {};
    ~DataReader() {};

    void Reader(std::string f);

    void LoopThroughWfms(std::vector<short> ch,
      std::vector<double> timestamp,
      TClonesArray Eventwaveform,
      int type,
      OpWaveformCollection &wfm_collection);

    void IAMTHENIGHT();

  protected:
    std::vector<EventOpWaveforms> _EvOpwfms_v;
    int eventNo;
  };

}
#endif
