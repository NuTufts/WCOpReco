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
#include <vector>

namespace wcopreco  {

  class datareader_j {
  public:
    datareader_j() {};
    ~datareader_j() {};

    void Reader();
    int eventNo;
    std::vector<short int> cosmic_hg_opch;
    std::vector<double> cosmic_hg_timestamp;
    int cosmic_lg_opch;
    int beam_lg_opch;
    int beam_hg_opch;
  };

}
#endif
