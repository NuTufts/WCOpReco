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

  // wcopreco::DataReader reader;
  // reader.Reader();

  // wcopreco::datareader_j reader_j;
  // reader_j.Reader();

  wcopreco::UBEventWaveform reader_ub;

  TFile *f = TFile::Open("/home/jmills/workdir/WCOpReco/src/data/celltree.root");
  if (f==0)
  {
    printf("Error: cannot open file");
    return 0;
  }

  reader_ub.read_in_data(f);
};
