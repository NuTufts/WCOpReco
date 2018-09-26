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
    TFile* file = TFile::Open("/home/kmason/PmtReco/WCOpReco/src/data/celltree.root");
    if (file==0) {
      std::cout<< "Error: Cannot open file" << std::endl;
      return;
    };

    TTree * tree = (TTree*) file->Get("Event/Sim");
    //need to save channel and timestamp
    std::vector<double> * cosmic_hg_timestamp = 0;
    std::vector<double> * cosmic_lg_timestamp = 0;
    std::vector<double> * beam_hg_timestamp = 0;
    std::vector<double> * beam_lg_timestamp = 0;
    tree->SetBranchAddress("cosmic_hg_timestamp",&cosmic_hg_timestamp);
    tree->SetBranchAddress("cosmic_lg_timestamp",&cosmic_lg_timestamp);
    tree->SetBranchAddress("beam_hg_timestamp",&beam_hg_timestamp);
    tree->SetBranchAddress("beam_lg_timestamp",&beam_lg_timestamp);

    //Double_t triggerTime;
    //tree->SetBranchAddress("triggerTime",&triggerTime);

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

      tree->GetEntry(i);

      for (int k = 0; k<4; k++){
        int type = k;
        std::vector<short> ch;
        std::vector<double> timestamp;
        if (k==0){
          ch = *beam_hg_opch;
          timestamp = *beam_hg_timestamp;
        }
        else if (k==1){
          ch = *beam_lg_opch;
          timestamp = *beam_lg_timestamp;
        }
        else if (k==2){
          ch = *cosmic_hg_opch;
          timestamp = *cosmic_hg_timestamp;
        }
        else if (k==3){
          ch = *cosmic_lg_opch;
          timestamp = *cosmic_lg_timestamp;
        };

        for (unsigned j=0; j < ch.size(); j++) {
          OpWaveform wfm(ch[j], timestamp[j], type, std::vector<short> (0));
          //check
          if (j == 1){
            std::cout <<"type: " <<wfm.get_type()<< " ch: " <<wfm.get_ChannelNum()<< " timestamp: " << wfm.get_time_from_trigger() <<std::endl;};
        };
        ch.clear();
        timestamp.clear();
      };


      std::cout <<"  " << std::endl;
      std::cout << "end of event" << std::endl;
    };
    return;
  };

};
