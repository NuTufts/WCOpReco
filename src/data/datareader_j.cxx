#include "OpWaveform.h"
#include "OpWaveformCollection.h"
#include "EventOpWaveforms.h"
#include "UBEventWaveform.h"
#include "datareader_j.h"

//root includes
#include "TObject.h"
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TTimeStamp.h"





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
    std::vector<short> * cosmic_lg_opch = 0; //or =NULL if it complains
    std::vector<short> * beam_hg_opch = 0; //or =NULL if it complains
    std::vector<short> * beam_lg_opch = 0; //or =NULL if it complains

    std::vector<double> * cosmic_hg_timestamp = 0; //or =NULL if it complains
    std::vector<double> * cosmic_lg_timestamp = 0; //or =NULL if it complains
    std::vector<double> * beam_hg_timestamp = 0; //or =NULL if it complains
    std::vector<double> * beam_lg_timestamp = 0; //or =NULL if it complains

    TClonesArray * cosmic_hg_wf;
    TClonesArray * cosmic_lg_wf;
    TClonesArray * beam_hg_wf;
    TClonesArray * beam_lg_wf;

    cosmic_hg_wf = new TClonesArray("TH1S");
    cosmic_lg_wf = new TClonesArray("TH1S");
    beam_hg_wf = new TClonesArray("TH1S");
    beam_lg_wf = new TClonesArray("TH1S");


    tree->SetBranchAddress("cosmic_hg_opch",&cosmic_hg_opch);
    tree->SetBranchAddress("cosmic_lg_opch",&cosmic_lg_opch);
    tree->SetBranchAddress("beam_hg_opch",&beam_hg_opch);
    tree->SetBranchAddress("beam_lg_opch",&beam_lg_opch);

    tree->SetBranchAddress("cosmic_hg_timestamp", &cosmic_hg_timestamp);
    tree->SetBranchAddress("cosmic_lg_timestamp", &cosmic_lg_timestamp);
    tree->SetBranchAddress("beam_hg_timestamp", &beam_hg_timestamp);
    tree->SetBranchAddress("beam_lg_timestamp", &beam_lg_timestamp);

    tree->SetBranchAddress("cosmic_hg_wf",&cosmic_hg_wf);
    tree->SetBranchAddress("cosmic_lg_wf",&cosmic_lg_wf);
    tree->SetBranchAddress("beam_hg_wf",&beam_hg_wf);
    tree->SetBranchAddress("beam_lg_wf",&beam_lg_wf);

    //Acquire # of Entries in file
    Int_t nevents = tree->GetEntries();
    std::cout << "Number of Events is:    " << tree->GetEntries() << std::endl;



    int type = 2;
    std::vector<short> vec(35,8);



    //Here we start looping through events
    for (Int_t i =0; i< 1; i++) {
      // std::cout << i << std::endl;
      tree->GetEntry(i);

      //Fill some Cosmic High Gains
      std::vector<short> CHG_Channel = *cosmic_hg_opch;
      std::vector<double> CHG_Timestamp = *cosmic_hg_timestamp;
      OpWaveform wfm_CHG(CHG_Channel[0], CHG_Timestamp[0], type, vec);

      //Fill some Cosmic Low Gains
      std::vector<short> CLG_Channel = *cosmic_lg_opch;
      std::vector<double> CLG_Timestamp = *cosmic_lg_timestamp;
      OpWaveform wfm_CLG(CLG_Channel[0], CLG_Timestamp[0], type, vec);

      // //Fill some Beam High Gains
      // std::vector<short> BHG_Channel = *beam_hg_opch;
      // std::vector<double> BHG_Timestamp = *beam_hg_timestamp;
      // OpWaveform wfm_BHG(BHG_Channel[0], BHG_Timestamp[0], type, vec);
      //
      // //Fill some Beam Low Gains
      // std::vector<short> BLG_Channel = *beam_lg_opch;
      // std::vector<double> BLG_Timestamp = *beam_lg_timestamp;
      // OpWaveform wfm_BLG(BLG_Channel[0], BLG_Timestamp[0], type, vec);

      //std::cout << wfm[0] <<"    " <<wfm.get_type() <<"    " <<wfm.get_time_from_trigger() <<"    "<< wfm.get_ChannelNum() << " Did we cout the information?" << std::endl;
      std::cout << CHG_Channel.size() << "   Channel Size"<<std::endl;
      std::cout << cosmic_hg_wf->GetSize() <<"    Histogram Size"<< std::endl;

      TClonesArray CHG_Waveform = *cosmic_hg_wf;
      Int_t NHist = CHG_Waveform.GetEntries();
      TClass * Class = CHG_Waveform.GetClass();

      TH1S *Hist = (TH1S*)CHG_Waveform.At(1);
      Int_t Buffer_size = Hist->GetDefaultBufferSize();
      std::cout  << NHist << "    Number of Histograms in the TClonesArray" << std::endl;
      std::cout << Buffer_size << "   Is size of buffer in Hist" << std::endl;
      // Class->Dump();
    };


    return;

  };
};
