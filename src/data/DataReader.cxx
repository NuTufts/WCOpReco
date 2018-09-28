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
#include "TClonesArray.h"
#include "TObject.h"
#include "TTimeStamp.h"


#include <iostream>
#include <sstream>
#include <vector>

namespace wcopreco {

  void DataReader::Reader() {
    TFile* file = TFile::Open("/home/kmason/PmtReco/WCOpReco/src/data/celltree.root");
    if (file==0) {
      std::cout<< "Error: Cannot open file" << std::endl;
      return;
    };

    TTree * tree = (TTree*) file->Get("Event/Sim");
    //save timestamps
    std::vector<double> * cosmic_hg_timestamp = 0;
    std::vector<double> * cosmic_lg_timestamp = 0;
    std::vector<double> * beam_hg_timestamp = 0;
    std::vector<double> * beam_lg_timestamp = 0;
    tree->SetBranchAddress("cosmic_hg_timestamp",&cosmic_hg_timestamp);
    tree->SetBranchAddress("cosmic_lg_timestamp",&cosmic_lg_timestamp);
    tree->SetBranchAddress("beam_hg_timestamp",&beam_hg_timestamp);
    tree->SetBranchAddress("beam_lg_timestamp",&beam_lg_timestamp);

    //Save waveforms
    TClonesArray * cosmic_hg_wf;
    cosmic_hg_wf = new TClonesArray("TH1S");
    tree->SetBranchAddress("cosmic_hg_wf",&cosmic_hg_wf);
    TClonesArray * cosmic_lg_wf;
    cosmic_lg_wf = new TClonesArray("TH1S");
    tree->SetBranchAddress("cosmic_lg_wf",&cosmic_lg_wf);
    TClonesArray * beam_hg_wf;
    beam_hg_wf = new TClonesArray("TH1S");
    tree->SetBranchAddress("beam_hg_wf",&beam_hg_wf);
    TClonesArray * beam_lg_wf;
    beam_lg_wf = new TClonesArray("TH1S");
    tree->SetBranchAddress("beam_lg_wf",&beam_lg_wf);

    //Save channel info
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
          LoopThroughWfms(*beam_hg_opch, *beam_hg_timestamp, *beam_hg_wf, 0);
        }
        else if (k==1){
          LoopThroughWfms(*beam_lg_opch, *beam_lg_timestamp, *beam_lg_wf, 1);
        }
        else if (k==2){
          LoopThroughWfms(*cosmic_hg_opch, *cosmic_hg_timestamp, *cosmic_hg_wf, 2);
        }
        else if (k==3){
          LoopThroughWfms(*cosmic_lg_opch, *cosmic_lg_timestamp, *cosmic_lg_wf, 3);
        };
      };

      std::cout << "end of event" << std::endl;
      std::cout <<"  " << std::endl;
    };
    return;
  };

  void DataReader::LoopThroughWfms(std::vector<short> ch,
    std::vector<double> timestamp,
    TClonesArray Eventwaveform_root,
    int type) {

    for (unsigned j=0; j < ch.size(); j++){
      TH1S *waveform = (TH1S*)Eventwaveform_root.At(j);
      Int_t n = waveform->GetNbinsX();
      wcopreco::OpWaveform wfm(ch[j], timestamp[j], type, n);
      wcopreco::EventOpWaveforms event_wfm(wfm);
      memcpy(wfm.data(),waveform->GetArray(),sizeof(short)*n);
      //check output
      if (j == 0){
        std::cout <<"type: " <<wfm.get_type()<< " ch: " <<wfm.get_ChannelNum()<< " timestamp: " << wfm.get_time_from_trigger() <<std::endl;
      };
    };
    Eventwaveform_root.Clear();
    return;
  };
};
