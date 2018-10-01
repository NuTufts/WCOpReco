#include "WCOpReco/OpWaveform.h"
#include "WCOpReco/OpWaveformCollection.h"
#include "WCOpReco/EventOpWaveforms.h"
#include "WCOpReco/UBEventWaveform.h"
#include "WCOpReco/datareader_j.h"
#include "WCOpReco/DataReader.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"
#include "TFile.h"

#include <iostream>
#include <sstream>

int main(){

  std::cout << "Hello world" << std::endl;

  wcopreco::UBEventWaveform reader_ub;

  std::string file = "/home/jmills/workdir/WCOpReco/src/data/celltree.root";
  reader_ub.read_in_data(file);
};
