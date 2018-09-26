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
    TFile *f = TFile::Open("/home/jmills/workdir/WCOpReco/src/data/celltree.root");
    if (f==0)
    {
      printf("Error: cannot open file");
      return;
    }
    //Get branches to different types of events
    TTree * tree = (TTree *) f->Get("Event/Sim");
    tree->SetBranchAddress("eventNo",&eventNo);
    std::vector<short> * cosmic_hg_opch = 0; //or =NULL if it complains

    tree->SetBranchAddress("cosmic_hg_opch",&cosmic_hg_opch);
    // tree->SetBranchAddress("cosmic_lg_opch",&cosmic_lg_opch);
    // tree->SetBranchAddress("beam_hg_opch",&beam_hg_opch);
    // tree->SetBranchAddress("beam_lg_opch",&beam_lg_opch);
    // tree->SetBranchAddress("cosmic_hg_wf",&cosmic_hg_wf);
    // tree->SetBranchAddress("cosmic_lg_wf",&cosmic_lg_wf);
    // tree->SetBranchAddress("beam_hg_wf",&beam_hg_wf);
    // tree->SetBranchAddress("beam_lg_wf",&beam_lg_wf);

    //Acquire # of Entries in file
    Int_t nevents = tree->GetEntries();
    std::cout << "Number of Events is:    " << tree->GetEntries() << std::endl;

    for (Int_t i =0; i< nevents;i++) {
      //cout << i << endl;
      tree->GetEntry(i);
      auto test = *cosmic_hg_opch;
      std::cout << "Size of OpCh Vector:    " << test.size() << std::endl;
      std::cout << "EventNumber:    "<< eventNo<< "    CHigh:   "<< std::endl; //<< test[0]  << std::endl <<
      for (int j = 0; j<30; j++) {
        std::cout << test[j] << "   ";

      }
      std::cout << std::endl;
      //std::cout << eventNo; //<< "  CHigh  " << cosmic_hg_opch <<"  CLow  " << cosmic_lg_opch <<"  BLow  " << beam_lg_opch<< "  BHigh  " << beam_hg_opch << std::endl;
    };

    return;

  };
};
