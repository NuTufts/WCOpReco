#ifndef DATAREADER_H
#define DATAREADER_H

#include "OpWaveform.h"
#include "OpWaveformCollection.h"
#include "EventOpWaveforms.h"
#include "UBEventWaveform.h"
#include "DataReader.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"

#include <iostream>

class DataReader : public UBEventWaveform {
public:
  void Reader();
};
#endif
