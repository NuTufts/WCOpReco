#include "UBEventWaveform.h"
#include "EventOpWaveforms.h"
#include "OpWaveformCollection.h"
namespace wcopreco {

   UBEventWaveform::UBEventWaveform(){

    // setup the eventwaveform map for our types
    EventOpWaveforms::_wfm_v.resize(4);
    insert_type2index( kbeam_hg, 0 );
    insert_type2index( kbeam_lg, 1 );
    insert_type2index( kcosmic_hg, 2 );
    insert_type2index( kcosmic_lg, 3 );

    insert_index2type( 0, kbeam_hg  );
    insert_index2type( 1, kbeam_lg );
    insert_index2type( 2, kcosmic_hg );
    insert_index2type( 3, kcosmic_lg );
  }

  void UBEventWaveform::addWaveform( UBOpWaveformForm_t type, const OpWaveform& wfm ) {
    push_back_wfm( (int)type, wfm );
  }

// void wcopreco::UBEventWaveform::read_in_data(std::string file) {
//     IAMTHENIGHT();
//     TFile *f = TFile::Open(file.c_str(), "read");
//     if (f==0)
//     {
//       printf("Error: cannot open file");
//       return;
//     }

//     //Get branches to different types of events
//     TTree * tree = (TTree *) f->Get("Event/Sim");
//     tree->SetBranchAddress("eventNo",&eventNo);

//     fill_EventWfms("beam_hg_opch" ,"beam_hg_timestamp" ,"beam_hg_wf" ,kbeam_hg, tree);
//     fill_EventWfms("beam_lg_opch" ,"beam_lg_timestamp" ,"beam_lg_wf" ,kbeam_lg, tree);
//     fill_EventWfms("cosmic_hg_opch" ,"cosmic_hg_timestamp" ,"cosmic_hg_wf" ,kcosmic_hg, tree);
//     fill_EventWfms("cosmic_lg_opch" ,"cosmic_lg_timestamp" ,"cosmic_lg_wf" ,kcosmic_lg, tree);

//     /*Structure
//     (This section written by Josh during nightshift, treat all content with skepticism):

//     UBEventWaveform has datamember _EvOpwfms_v which is a vector<EventOpWaveforms>
//     Each EventOpWaveforms has a datamember _wfm_v which is a vector<OpWaveformCollection>
//     Recall that OpWaveformCollection inherits from vector, so it DOESNT hold a datamember vector, instead it acts like a vector
//     Therefore OpWaveformCollection acts like a vector<OpWaveform>
//     Then Recall OpWaveform inherits from vector, and it's vector contains signal hit information
//     Each OpWaveform also has datamembers ChannelNum, time_from_trigger, type
//     */

//     //Now our UBEventWaveform is relatively built (fancy features to come?)
//     //Put stuff here to test that _EvOpWfms_v has correct content
//     int ENTRY_TO_VIEW =0;
//     int TYPE_OF_COLLECTION =0;
//     int WFM_INDEX =0;
//     int SIGNAL_INDEX =1;

//     std::cout << std::endl;
//     std::cout << "Value   Explanation (Anticipated Value)" << std::endl ;
//     std::cout << "---------------------------------------" << std::endl;
//     std::cout << (  ( ( ( ( _EvOpwfms_v[ ENTRY_TO_VIEW ] ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] ) [SIGNAL_INDEX])     <<  "   Attempt at Reading a Waveform Signal Value (~2000 unless first entry?)" <<std::endl;
//     std::cout << (  ( ( ( _EvOpwfms_v[ ENTRY_TO_VIEW ] ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] ).size()     <<  "   How many bins in the waveform? (1501)" <<std::endl;
//     std::cout << (  ( ( _EvOpwfms_v[ ENTRY_TO_VIEW ] ).get__wfm_v() ) [TYPE_OF_COLLECTION] ).size()      <<  "  How many waveforms in the collection (depends)?" <<std::endl;
//     std::cout << (  ( _EvOpwfms_v[ ENTRY_TO_VIEW ] ).get__wfm_v() ) .size()      <<  "   How many Collections in the Event (4)?" <<std::endl;
//     std::cout << (  _EvOpwfms_v ).size()      <<  "   How many Events? (52) " <<std::endl;


//     IAMTHENIGHT();
//     return;
//   }

//   void UBEventWaveform::fill_EventWfms(std::string st_opch,
//         std::string st_timestamp,
//         std::string st_wf,
//         UBEventWaveform::UBOpWaveformForm_t st_gain,
//         TTree * tree){
//     std::vector<short> * opch = 0;
//     std::vector<double> * timestamp = 0;
//     TClonesArray * wf;
//     wf = new TClonesArray("TH1S");
//     tree->SetBranchAddress(st_opch.c_str(), &opch);
//     tree->SetBranchAddress(st_timestamp.c_str(), &timestamp);
//     tree->SetBranchAddress(st_wf.c_str(),&wf);
//     Int_t nevents = tree->GetEntries();
//     std::cout << "Number of Events is:    " << tree->GetEntries() << std::endl;

//     int type;
//     std::vector<short> vec(35,8);

//     std::cout << "Don't forget to change to loop through all events, not just first one!" << std::endl;

//     //Here we start looping through events
//     for (Int_t i =0; i< nevents; i++) {
//       // std::cout << i << std::endl;
//       tree->GetEntry(i);

//       //Make an EventOpWaveforms for this event:
//       EventOpWaveforms Ev_Opwfms;
//       std::vector<OpWaveformCollection> testvector;
//       Ev_Opwfms.set__wfm_v( testvector );

//       //Get Vectors of pmt channel and timestamp for each type of waveform, cosmic/beam and high/low gain
//       std::vector<short> Channel = *opch;
//       std::vector<double> Timestamp = *timestamp;

//       //Get number of histograms
//       TClonesArray Waveform = *wf;
//       Int_t NHist = Waveform.GetEntries();

//       //Create OpWaveformCollection to hold OpWaveforms
//       //Each collection has waveforms from a single event of a specific type
//       // OpWaveformCollection CHG_wfm_collection(CHG_NHist);
//       OpWaveformCollection wfm_collection;
//       wfm_collection.reserve(500);

//       //trying to use enum
//       int gain_type = st_gain;
//       std::cout<< "test enum "<< st_gain <<std::endl;

//       //Fill up wfm collections
//       LoopThroughWfms_UB(*opch, *timestamp, *wf, gain_type, wfm_collection);

//       // Ev_Opwfms.set__wfm_v( BHG_wfm_collection );
//       // Ev_Opwfms.insert_type2index(0,0);
//       // Ev_Opwfms.insert_index2type(0,0);

//       //Here we are filling the Ev_Opwfms with all the different types of waveforms in the event.
//       Ev_Opwfms.add_entry(wfm_collection, gain_type,  gain_type);

//       std::map <int,int> testmap = Ev_Opwfms.get_type2index();

//       _EvOpwfms_v.emplace_back(std::move(Ev_Opwfms));
//       std::cout << "Entries in Vector<EventOpWaveforms>: "<< _EvOpwfms_v.size() << "   Loop Iters:    " << i << std::endl;
//     };
//   }


//   void UBEventWaveform::LoopThroughWfms_UB(std::vector<short> ch,
//     std::vector<double> timestamp,
//     TClonesArray Eventwaveform_root,
//     int type,
//     OpWaveformCollection &wfm_collection) {

//     for (unsigned j=0; j < ch.size(); j++){
//       TH1S *waveform = (TH1S*)Eventwaveform_root.At(j);
//       Int_t n = waveform->GetNbinsX();
//       wcopreco::OpWaveform wfm(ch[j], timestamp[j], type, n);

//       memcpy(wfm.data(),waveform->GetArray(),sizeof(short)*n);

//       // This line takes each opwaveform and pushes them to the end of the slowly growing wfm_collection
//       wfm_collection.emplace_back(std::move(wfm));
//       // std::cout << "length: " << wfm_collection.size() << std::endl;
//       // std::cout << "capacity: " << wfm_collection.capacity() << std::endl;


//       //check output
//       // if (j == 0){
//       //   std::cout << waveform->GetArray()[0] << std::endl;
//       //   std::cout << (wfm_collection.at(j)).get_type() << std::endl;
//       //   std::cout <<"type: " <<wfm.get_type()<< " ch: " <<wfm.get_ChannelNum()<< " timestamp: " << wfm.get_time_from_trigger() <<std::endl;
//       // };
//     };
//     Eventwaveform_root.Clear();
//     return;
//   };

//   void UBEventWaveform::IAMTHENIGHT() {
//     std::cout << std::endl;
//     std::cout << std::endl;

//     std::cout <<  "           X                         X" << std::endl;
//     std::cout <<  "       XXXX          X     X          XXX"<< std::endl;
//     std::cout <<  "     XXXX            XXXXXXX            XXXX"<< std::endl;
//     std::cout <<  "   XXXXXX            XXXXXXX            XXXXXX"<< std::endl;
//     std::cout <<  "  XXXXXXXXX         XXXXXXXXX         XXXXXXXXX"<< std::endl;
//     std::cout <<  " XXXXXXXXXXXxxxxxxxXXXXXXXXXXXxxxxxxxXXXXXXXXXXX"<< std::endl;
//     std::cout <<  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<< std::endl;
//     std::cout <<  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<< std::endl;
//     std::cout <<  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<< std::endl;
//     std::cout <<  " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<< std::endl;
//     std::cout <<  "  XXXXX       XXXXXXXXXXXXXXXXXXXXX       XXXXX"<< std::endl;
//     std::cout <<  "    XXXX       XXX    XXXXX    XXX       XXXX"<< std::endl;
//     std::cout <<  "       XX       X      XXX      X       XX"<< std::endl;
//     std::cout << std::endl;
//     std::cout << std::endl;

//     return;
//   };

}
