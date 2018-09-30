#include "UBEventWaveform.h"


namespace wcopreco {


void wcopreco::UBEventWaveform::read_in_data(std::string filepath) {
    IAMTHENIGHT();

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


    std::cout << "Don't forget to change to loop through all events, not just first one!" << std::endl;

    //Here we start looping through events
    for (Int_t i =0; i< nevents; i++) {
      // std::cout << i << std::endl;
      tree->GetEntry(i);

      //Make an EventOpWaveforms for this event:
      EventOpWaveforms Ev_Opwfms;
      std::vector<OpWaveformCollection> testvector;
      Ev_Opwfms.set__wfm_v( testvector );

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
      LoopThroughWfms_UB(*beam_hg_opch, *beam_hg_timestamp, *beam_hg_wf, 0, BHG_wfm_collection);
      LoopThroughWfms_UB(*beam_lg_opch, *beam_lg_timestamp, *beam_lg_wf, 1, BLG_wfm_collection);
      LoopThroughWfms_UB(*cosmic_hg_opch, *cosmic_hg_timestamp, *cosmic_hg_wf, 2, CHG_wfm_collection);
      LoopThroughWfms_UB(*cosmic_lg_opch, *cosmic_lg_timestamp, *cosmic_lg_wf, 3, CLG_wfm_collection);

      // Ev_Opwfms.set__wfm_v( BHG_wfm_collection );
      // Ev_Opwfms.insert_type2index(0,0);
      // Ev_Opwfms.insert_index2type(0,0);
      // Ev_Opwfms.emplace_back__wfm_v(BLG_wfm_collection);
      // Ev_Opwfms.insert_type2index(1,1);
      // Ev_Opwfms.insert_index2type(1,1);
      // Ev_Opwfms.emplace_back__wfm_v(CHG_wfm_collection);
      // Ev_Opwfms.insert_type2index(2,2);
      // Ev_Opwfms.insert_index2type(2,2);
      // Ev_Opwfms.emplace_back__wfm_v(CLG_wfm_collection);
      // Ev_Opwfms.insert_type2index(3,3);
      // Ev_Opwfms.insert_index2type(3,3);


      //Here we are filling the Ev_Opwfms with all the different types of waveforms in the event.
      Ev_Opwfms.add_entry(BHG_wfm_collection, 0, 0 );
      Ev_Opwfms.add_entry(BLG_wfm_collection, 1, 1 );
      Ev_Opwfms.add_entry(CHG_wfm_collection, 2, 2 );
      Ev_Opwfms.add_entry(CLG_wfm_collection, 3, 3 );

      std::map <int,int> testmap = Ev_Opwfms.get_type2index();
      // for (int it=0; it<testmap.size(); it++) {
      //    std::cout << it << "   type versus index    " <<testmap[it] << std::endl;
      //
      // }

      // std::cout << (Ev_Opwfms.get__wfm_v().size()) << " Is address of Ev_Opwfms     " << std::endl;

      // //Prove to myself the collections get filled (They are!)
      // std::cout << (CHG_wfm_collection[0]).get_type() << std::endl;
      // std::cout << (BHG_wfm_collection[1]).get_type() << std::endl;
      // std::cout << (CLG_wfm_collection[3]).get_type() << std::endl;
      // std::cout << (BLG_wfm_collection[10]).get_type() << std::endl;

      _EvOpwfms_v.emplace_back(std::move(Ev_Opwfms));
      std::cout << _EvOpwfms_v.size() << "    Versus loop iteration:    " << i << std::endl;

    };//End of Event Loop

    IAMTHENIGHT();
    return;
  }


  void UBEventWaveform::LoopThroughWfms_UB(std::vector<short> ch,
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
        // std::cout << (wfm_collection.at(j)).get_type() << std::endl;
        // std::cout <<"type: " <<wfm.get_type()<< " ch: " <<wfm.get_ChannelNum()<< " timestamp: " << wfm.get_time_from_trigger() <<std::endl;
      // };
    };
    Eventwaveform_root.Clear();
    return;
  };

  void UBEventWaveform::IAMTHENIGHT() {
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
