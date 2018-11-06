#ifndef RUN_H
#define RUN_H

//WCOpReco includes
#include "WCOpReco/OpWaveform.h"
#include "WCOpReco/OpWaveformCollection.h"
#include "WCOpReco/EventOpWaveforms.h"
#include "WCOpReco/Deconvolver.h"
#include "WCOpReco/HitFinder_cosmic.h"
#include "WCOpReco/Flashes_cosmic.h"
#include "WCOpReco/Flashes_beam.h"
#include "WCOpReco/HitFinder_beam.h"
#include "WCOpReco/FlashFiltering.h"

#include "UBEventWaveform.h"
#include "DataReader.h"
#include "saturation_merger.h"
#include "UB_rc.h"
#include "UB_spe.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"

//c++ includes
#include <iostream>
#include <sstream>
#include <time.h>

namespace wcopreco  {

  //This is a class to run the WCOpReco code, for uboone
  class Run {
  public:
    Run();
    ~Run() {};

    OpflashSelection get_flashes_cosmic(){return flashes_cosmic;};
    OpflashSelection get_flashes_beam(){return flashes_beam;};
    OpflashSelection get_flashes(){return flashes;};

  protected:
    OpflashSelection flashes_cosmic;
    OpflashSelection flashes_beam;
    OpflashSelection flashes;

  };

}
#endif
