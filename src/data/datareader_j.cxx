#include "OpWaveform.h"
#include "OpWaveformCollection.h"
#include "EventOpWaveforms.h"
#include "UBEventWaveform.h"
#include "datareader_j.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"
#include "TFile.h"

#include <iostream>
#include <sstream>

namespace wcopreco {

  void datareader_j::Reader() {
    //Open file
    TFile *f = TFile::Open("../files/celltree.root");
    if (f==0)
    {
      printf("Error: cannot open file");
      return;
    }
    //Get branches to different types of events
    TTree * tree = (TTree *) f->Get("Event/Sim");
    tree->SetBranchAddress("eventNo",&eventNo);
    // tree->SetBranchAddress("cosmic_hg_wf",&cosmic_hg_wf);
    // tree->SetBranchAddress("cosmic_lg_wf",&cosmic_lg_wf);
    // tree->SetBranchAddress("beam_hg_wf",&beam_hg_wf);
    // tree->SetBranchAddress("beam_lg_wf",&beam_lg_wf);

    //Acquire # of Entries in file
    Int_t nevents = tree->GetEntries() ;
    std::cout << "Number of Events is:    " << tree->GetEntries() << std::endl;

    for (Int_t i =0; i< nevents;i++) {
      //cout << i << endl;
      tree->GetEntry(i);
      std::cout << eventNo<< std::endl;
      //OpWaveform::ChannelNum ChNum =
    };

    return;

  };
};
