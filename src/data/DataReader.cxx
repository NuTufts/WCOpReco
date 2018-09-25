#include "OpWaveform.h"
#include "OpWaveformCollection.h"
#include "EventOpWaveforms.h"
#include "UBEventWaveform.h"
#include "DataReader.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"
#include "TFile.h"

#include <iostream>
#include <sstream>

void Reader(){
  TFile* file = TFile::Open("/WCOpReco/src/data/celltree.root");
  if (file==0) {
    std::cout<< "Error: Cannot open file" << std::endl;
    return;
  };
  TTree * tree = (TTree*) file->Get("Event/Sim");

  int nevents = tree->GetEntries();
  std::cout << "Number of Events is: " << tree->GetEntries() << std::endl;

  for (Int_t i =0; i< nevents;i++) {
    //cout << i << endl;
    tree->GetEntry(i);
    //OpWaveform::ChannelNum ChNum =
  };
};
