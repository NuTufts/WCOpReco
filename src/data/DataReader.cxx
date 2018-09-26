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

namespace wcopreco {

  void DataReader::Reader() {
    //std::cout<<"start"<<std::endl;
    printf("start");
    TFile* file = TFile::Open("/home/kmason/PmtReco/WCOpReco/src/data/celltree.root");
    if (file==0) {
      std::cout<< "Error: Cannot open file" << std::endl;
      return;
    };

    TTree * tree = (TTree*) file->Get("Event/Sim");
    //point to the branches we'll need
    std::vector<double> * cosmic_hg_timestamp = 0;
    std::vector<double> * cosmic_lg_timestamp = 0;
    std::vector<double> * beam_hg_timestamp = 0;
    std::vector<double> * beam_lg_timestamp = 0;
    tree->SetBranchAddress("cosmic_hg_timestamp",&cosmic_hg_timestamp);
    tree->SetBranchAddress("cosmic_lg_timestamp",&cosmic_lg_timestamp);
    tree->SetBranchAddress("beam_hg_timestamp",&beam_hg_timestamp);
    tree->SetBranchAddress("beam_lg_timestamp",&beam_lg_timestamp);

    Double_t triggerTime;
    tree->SetBranchAddress("triggerTime",&triggerTime);

    std::vector<short> * cosmic_hg_opch = 0;
    std::vector<short> * cosmic_lg_opch = 0;
    std::vector<short> * beam_hg_opch = 0;
    std::vector<short> * beam_lg_opch = 0;
    tree->SetBranchAddress("cosmic_hg_opch",&cosmic_hg_opch);
    tree->SetBranchAddress("cosmic_lg_opch",&cosmic_lg_opch);
    tree->SetBranchAddress("beam_hg_opch",&beam_hg_opch);
    tree->SetBranchAddress("beam_lg_opch",&beam_lg_opch);

    int nevents = tree->GetEntries();
    std::cout << "Number of Events is: " << tree->GetEntries() << std::endl;

    for (Int_t i =0; i< nevents;i++) {
      //std::cout << i << std::endl;
      //for each event save an OpWaveform with necessary info
      tree->GetEntry(i);
      std::cout<<"triggerTime " << triggerTime << std::endl;
      wcopreco::OpWaveform(0, triggerTime, 0);
      //std::cout << wcopreco::OpWaveform.get_time_from_trigger() <<std::endl;
      // for (unsigned j=0; j < cosmic_hg_opch->size(); j++) {
      //   std::vector<short> test = cosmic_hg_opch[j];
      //   for (unsigned k=0; k < test.size(); k++) {
      //       std::cout<< "test " << test[k] << "k " << k <<std::endl;
      //   };
      //   std::cout << "end of event" <<std::endl;
      // };
    };
    return;
  };

};
