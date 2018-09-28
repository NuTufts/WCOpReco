#ifndef DATAREADER_H
#define DATAREADER_H

#include "OpWaveform.h"
#include "OpWaveformCollection.h"
#include "EventOpWaveforms.h"
#include "UBEventWaveform.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"

#include <iostream>

namespace wcopreco  {

  class DataReader {
  public:
    DataReader() {};
    ~DataReader() {};

    void Reader();
    void LoopThroughWfms(std::vector<short> ch,
      std::vector<double> timestamp,
      TClonesArray Eventwaveform,
      int type);
  };

}
#endif
