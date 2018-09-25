#ifndef DATAREADER_J_H
#define DATAREADER_J_H

#include "OpWaveform.h"
#include "OpWaveformCollection.h"
#include "EventOpWaveforms.h"
#include "UBEventWaveform.h"
#include "datareader_j.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"

#include <iostream>

namespace wcopreco  {

  class datareader_j {
  public:
    datareader_j() {};
    ~datareader_j() {};

    void Reader();
    int eventNo;
  };

}
#endif
