#include "DataReader.h"

namespace wcopreco {

wcopreco::DataReader::DataReader(std::string filepath)

  {
    //Set datamembers
    file = TFile::Open(filepath.c_str());
    if (file==0)
    {
      printf("Error: cannot open file");
      return;
    }
    //Get branches to different types of events
    tree = (TTree *) file->Get("Event/Sim");
    tree->SetBranchAddress("eventNo",&eventNo);

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
    nevents = tree->GetEntries();
    std::cout << "Number of Events Constructed:    " << tree->GetEntries() << std::endl;
  }

UBEventWaveform wcopreco::DataReader::Reader(int event_num) {
    IAMTHENIGHT();
    std::cout << "You have chosen to read out event number: " << event_num << " out of " << nevents << std::endl;
    if ( event_num > nevents)
      {
        std::cout << "There aren't that many events, didn't work!" << std::endl;
        UBEventWaveform UB_Ev;
        return UB_Ev;
      }
    tree->GetEntry(event_num);

      //Make an EventOpWaveforms for this event:

      std::vector<OpWaveformCollection> empty_vec;
      _UB_Ev_wfm.set__wfm_v( empty_vec );

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


      //Fill up wfm collections
      LoopThroughWfms(*beam_hg_opch, *beam_hg_timestamp, *beam_hg_wf, 0, BHG_wfm_collection);
      LoopThroughWfms(*beam_lg_opch, *beam_lg_timestamp, *beam_lg_wf, 1, BLG_wfm_collection);
      LoopThroughWfms(*cosmic_hg_opch, *cosmic_hg_timestamp, *cosmic_hg_wf, 2, CHG_wfm_collection);
      LoopThroughWfms(*cosmic_lg_opch, *cosmic_lg_timestamp, *cosmic_lg_wf, 3, CLG_wfm_collection);




      //Here we are filling the _UB_Ev_wfm with all the different types of waveforms in the event.
      _UB_Ev_wfm.add_entry(BHG_wfm_collection, 0, 0 );
      _UB_Ev_wfm.add_entry(BLG_wfm_collection, 1, 1 );
      _UB_Ev_wfm.add_entry(CHG_wfm_collection, 2, 2 );
      _UB_Ev_wfm.add_entry(CLG_wfm_collection, 3, 3 );

      std::map <int,int> testmap = _UB_Ev_wfm.get_type2index();

    /*Structure
    (This section written by Josh during nightshift, treat all content with skepticism):
    UBEventWaveform is stored in _UB_Ev_wfm, and is essentially one eventopwaveform
    Each EventOpWaveforms has a datamember _wfm_v which is a vector<OpWaveformCollection>
    Recall that OpWaveformCollection inherits from vector, so it DOESNT hold a datamember vector, instead it acts like a vector
    Therefore OpWaveformCollection acts like a vector<OpWaveform>
    Then Recall OpWaveform inherits from vector, and it's vector contains signal hit information
    Each OpWaveform also has datamembers ChannelNum, time_from_trigger, type
    */

    //Now our UBEventWaveform is relatively built (fancy features to come?)
    //Put stuff here to test that _UB_Ev_wfm has correct content
    // int ENTRY_TO_VIEW =0;
    // int TYPE_OF_COLLECTION =0;
    // int WFM_INDEX =0;
    // int SIGNAL_INDEX =1;
    //
    // std::cout << std::endl;
    // std::cout << "Value   Explanation (Anticipated Value)" << std::endl ;
    // std::cout << "---------------------------------------" << std::endl;
    // std::cout << (  ( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] ) [SIGNAL_INDEX])     <<  "   Attempt at Reading a Waveform Signal Value (~2000 unless first entry?)" <<std::endl;
    // std::cout << (  ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] ).size()     <<  "   How many bins in the waveform? (1501)" <<std::endl;
    // std::cout << (  ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] ).size()      <<  "  How many waveforms in the collection (depends)?" <<std::endl;
    // std::cout << (  ( _UB_Ev_wfm ).get__wfm_v() ) .size()      <<  "   How many Collections in the Event (4)?" <<std::endl;



    // IAMTHENIGHT();
    return _UB_Ev_wfm;
  }


  void DataReader::LoopThroughWfms(std::vector<short> ch,
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
      // std::cout << "length: " << wfm_collection.size() << std::endl;
      // std::cout << "capacity: " << wfm_collection.capacity() << std::endl;


      //check output
      // if (j == 0){
      //   std::cout << waveform->GetArray()[0] << std::endl;
      //   std::cout << (wfm_collection.at(j)).get_type() << std::endl;
      //   std::cout <<"type: " <<wfm.get_type()<< " ch: " <<wfm.get_ChannelNum()<< " timestamp: " << wfm.get_time_from_trigger() <<std::endl;
      // };
    };
    Eventwaveform_root.Clear();
    return;
  };

  void DataReader::IAMTHENIGHT() {
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout <<  "           X                         X" << std::endl;
    std::cout <<  "       XXXX          X     X          XXX"<< std::endl;
    std::cout <<  "     XXXX            XXXXXXX            XXXX"<< std::endl;
    std::cout <<  "   XXXXXX            XXXXXXX            XXXXXX"<< std::endl;
    std::cout <<  "  XXXXXXXXX         XXXXXXXXX         XXXXXXXXX"<< std::endl;
    std::cout <<  " XXXXXXXXXXXxxxxxxxXXXXXXXXXXXxxxxxxxXXXXXXXXXXX"<< std::endl;
    std::cout <<  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<< std::endl;
    std::cout <<  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<< std::endl;
    std::cout <<  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<< std::endl;
    std::cout <<  " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<< std::endl;
    std::cout <<  "  XXXXX       XXXXXXXXXXXXXXXXXXXXX       XXXXX"<< std::endl;
    std::cout <<  "    XXXX       XXX    XXXXX    XXX       XXXX"<< std::endl;
    std::cout <<  "       XX       X      XXX      X       XX"<< std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    return;
  };

}
