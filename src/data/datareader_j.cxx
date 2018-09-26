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
    std::vector<double> * cosmic_hg_timestamp = 0; //or =NULL if it complains

    tree->SetBranchAddress("cosmic_hg_opch",&cosmic_hg_opch);
    tree->SetBranchAddress("cosmic_hg_timestamp", &cosmic_hg_timestamp);
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



    int type = 2;
    std::vector<short> vec(35,8);



    //Here we start looping through events
    for (Int_t i =0; i< nevents; i++) {
      //cout << i << endl;
      tree->GetEntry(i);
      std::vector<short> CHG_Channel = *cosmic_hg_opch;
      std::vector<double> CHG_Timestamp = *cosmic_hg_timestamp;

      OpWaveform wfm(CHG_Channel[0], CHG_Timestamp[0], type, vec);
      std::cout << wfm[0] <<"    " <<wfm.get_type() <<"    " <<wfm.get_time_from_trigger() <<"    "<< wfm.get_ChannelNum() << " Did we cout the information?" << std::endl;


      // std::cout << "Size of OpCh Vector:    " << test.size() << std::endl;
      // std::cout << "EventNumber:    "<< eventNo<< "    CHigh:   "<< std::endl; //<< test[0]  << std::endl <<
      // for (int j = 0; j<test.size(); j++) {
      //   std::cout << test[j] << "   ";
      //   if (j%10 == 9) {
      //     std::cout << std::endl;
      //   }
      // }
      // std::cout << std::endl;
    };


    return;

  };
};
