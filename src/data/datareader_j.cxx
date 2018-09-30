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



    int type;
    std::vector<short> vec(35,8);


    std::cout << "Remember to Change Entry loop to more than 1! (nevents)" << std::endl;
    std::cout << "Remember to change each type loop to more than 1! (CHG_NHist)" << std::endl;
    //Here we start looping through events
    for (Int_t i =0; i< 1; i++) {
      // std::cout << i << std::endl;
      tree->GetEntry(i);
      //Get Vectors of pmt channel and timestamp for each type of waveform, cosmic/beam and high/low gain
      std::vector<short> CHG_Channel = *cosmic_hg_opch;
      std::vector<double> CHG_Timestamp = *cosmic_hg_timestamp;
      std::vector<short> CLG_Channel = *cosmic_lg_opch;
      std::vector<double> CLG_Timestamp = *cosmic_lg_timestamp;
      std::vector<short> BHG_Channel = *beam_hg_opch;
      std::vector<double> BHG_Timestamp = *beam_hg_timestamp;
      std::vector<short> BLG_Channel = *beam_lg_opch;
      std::vector<double> BLG_Timestamp = *beam_lg_timestamp;

      //Get number of histograms for each type
      TClonesArray CHG_Waveform = *cosmic_hg_wf;
      Int_t CHG_NHist = CHG_Waveform.GetEntries();
      TClonesArray CLG_Waveform = *cosmic_lg_wf;
      Int_t CLG_NHist = CLG_Waveform.GetEntries();
      TClonesArray BHG_Waveform = *beam_hg_wf;
      Int_t BHG_NHist = BHG_Waveform.GetEntries();
      TClonesArray BLG_Waveform = *beam_lg_wf;
      Int_t BLG_NHist = BLG_Waveform.GetEntries();

      //Create OpWaveformCollection to hold OpWaveforms
      //Each collection has waveforms from a single event of a specific type
      // OpWaveformCollection CHG_wfm_collection(CHG_NHist);
      OpWaveformCollection CHG_wfm_collection;
      OpWaveformCollection CLG_wfm_collection;
      OpWaveformCollection BHG_wfm_collection;
      OpWaveformCollection BLG_wfm_collection;
      // std::cout << "capacity before reserve: " << CHG_wfm_collection.capacity() << std::endl;

      CHG_wfm_collection.reserve(500);
      CLG_wfm_collection.reserve(500);
      BLG_wfm_collection.reserve(500);
      BHG_wfm_collection.reserve(500);
      // std::cout << "capacity after reserve: " << CHG_wfm_collection.capacity() << std::endl;

      // std::cout << CHG_NHist<< "    " << CLG_NHist<< "    " << BHG_NHist<< "    " << BLG_NHist << std::endl;

      //Fill up wfm collections
      LoopThroughWfms(*beam_hg_opch, *beam_hg_timestamp, *beam_hg_wf, 0, BHG_wfm_collection);
      LoopThroughWfms(*beam_lg_opch, *beam_lg_timestamp, *beam_lg_wf, 1, BLG_wfm_collection);
      LoopThroughWfms(*cosmic_hg_opch, *cosmic_hg_timestamp, *cosmic_hg_wf, 2, CHG_wfm_collection);
      LoopThroughWfms(*cosmic_lg_opch, *cosmic_lg_timestamp, *cosmic_lg_wf, 3, CLG_wfm_collection);

      // //Prove to myself the collections get filled
      // std::cout << (CHG_wfm_collection[0]).get_type() << std::endl;
      // std::cout << (BHG_wfm_collection[1]).get_type() << std::endl;
      // std::cout << (CLG_wfm_collection[3]).get_type() << std::endl;
      // std::cout << (BLG_wfm_collection[10]).get_type() << std::endl;

    };


    return;

  };

  void datareader_j::LoopThroughWfms(std::vector<short> ch,
    std::vector<double> timestamp,
    TClonesArray Eventwaveform_root,
    int type,
    OpWaveformCollection &wfm_collection) {

    for (unsigned j=0; j < ch.size(); j++){
      TH1S *waveform = (TH1S*)Eventwaveform_root.At(j);
      Int_t n = waveform->GetNbinsX();
      wcopreco::OpWaveform wfm(ch[j], timestamp[j], type, n);

      memcpy(wfm.data(),waveform->GetArray(),sizeof(short)*n);

      // This line takes each opwaveform and pushes them to the end of the slowly growing wfm_collection
      wfm_collection.emplace_back(std::move(wfm));
      std::cout << "length: " << wfm_collection.size() << std::endl;
      std::cout << "capacity: " << wfm_collection.capacity() << std::endl;


      //check output
      if (j == 0){
        std::cout << (wfm_collection.at(j)).get_type() << std::endl;
        std::cout <<"type: " <<wfm.get_type()<< " ch: " <<wfm.get_ChannelNum()<< " timestamp: " << wfm.get_time_from_trigger() <<std::endl;
      };
    };
    Eventwaveform_root.Clear();
    return;
  };
};


//Old code:

//Replace the following Code block with function LoopThroughWfms()
      // int counter=0;
      // for (int j = 0; j<CHG_NHist; j++){
      //   //Fill some Cosmic High Gains
      //   type = 2;
      //   counter++;
      //   TH1S *CHG_Hist = (TH1S*)CHG_Waveform.At(j);
      //   Int_t CHG_nbins = CHG_Hist->GetNbinsX();
      //   // std::vector<short> test_v(CHG_nbins,0);
      //
      //   OpWaveform wfm_CHG(CHG_Channel[j], CHG_Timestamp[j], type, CHG_nbins);
      //
      //
      //   memcpy(wfm_CHG.data(),CHG_Hist->GetArray(), sizeof(short)*CHG_nbins);
      //
      //
      //   // std::cout << "Blah";
      // }
      //
      // std::cout << "CHG_Waveforms Performed:  " <<counter << " Should have done:  " << CHG_NHist << std::endl;
      // counter =0;
      //
      //
      // for (int j =0; j<CLG_NHist; j++){
      //   //Fill some Cosmic Low Gains
      //   type = 3;
      //   counter++;
      //   TH1S *CLG_Hist = (TH1S*)CLG_Waveform.At(j);
      //   Int_t CLG_nbins = CLG_Hist->GetNbinsX();
      //   // std::vector<short> test_v(CLG_nbins,0);
      //
      //   OpWaveform wfm_CLG(CLG_Channel[j], CLG_Timestamp[j], type, CLG_nbins);
      //
      //
      //   memcpy(wfm_CLG.data(),CLG_Hist->GetArray(), sizeof(short)*CLG_nbins);
      //
      //
      //   // std::cout << "Blah";
      // }
      //
      // std::cout << "CLG_Waveforms Performed:  " <<counter << " Should have done:  " << CLG_NHist << std::endl;
      // counter =0;
      //
      // for (int j=0; j<BHG_NHist;j++){
      //   //Fill some Beam High Gains
      //   type = 0;
      //   counter++;
      //   TH1S *BHG_Hist = (TH1S*)BHG_Waveform.At(j);
      //   Int_t BHG_nbins = BHG_Hist->GetNbinsX();
      //   // std::vector<short> test_v(BHG_nbins,0);
      //
      //   OpWaveform wfm_BHG(BHG_Channel[j], BHG_Timestamp[j], type, BHG_nbins);
      //
      //
      //   memcpy(wfm_BHG.data(),BHG_Hist->GetArray(), sizeof(short)*BHG_nbins);
      //
      //
      //   // std::cout << "Blah";
      //
      // }
      //
      // std::cout << "BHG_Waveforms Performed:  " <<counter << " Should have done:  " << BHG_NHist << std::endl;
      // counter =0;
      //
      // for (int j=0;j<BLG_NHist;j++){
      //   //Fill some Beam Low Gains
      //   type = 1;
      //   counter++;
      //   TH1S *BLG_Hist = (TH1S*)BLG_Waveform.At(j);
      //   Int_t BLG_nbins = BLG_Hist->GetNbinsX();
      //   // std::vector<short> test_v(BLG_nbins,0);
      //
      //   OpWaveform wfm_BLG(BLG_Channel[j], BLG_Timestamp[j], type, BLG_nbins);
      //
      //
      //   memcpy(wfm_BLG.data(),BLG_Hist->GetArray(), sizeof(short)*BLG_nbins);
      //
      //
      //   // std::cout << "Blah";
      //
      // }

      // std::cout << "BLG_Waveforms Performed:  " <<counter << " Should have done:  " << BLG_NHist << std::endl;
      // counter =0;
      // // std::cout << CHG_Channel.size() << "   Channel Size"<<std::endl;
      // // std::cout << cosmic_hg_wf->GetSize() <<"    Histogram Size"<< std::endl;



      // for (int x=0; x<test_v.size(); x++) {
      //   std::cout <<"   " <<CHG_nbins << " " << " "<< test_v.size() << "   Number of bins" << std::endl << "    " <<test_v[x] << std::endl << (CHG_Hist->GetArray())[x] << std::endl;
        // std::cout  << CHG_NHist << "    Number of Histograms in the TClonesArray" << std::endl;
        // std::cout << Buffer_size << "   Is size of buffer in CHG_Hist" << std::endl;
        // Class->Dump();
      // }
