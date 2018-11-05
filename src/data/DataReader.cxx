#include "DataReader.h"
#include <cmath>


namespace wcopreco {

wcopreco::DataReader::DataReader(std::string filepath) :
  cosmic_hg_opch(nullptr),
  cosmic_lg_opch(nullptr),
  beam_hg_opch(nullptr),
  beam_lg_opch(nullptr),

  cosmic_hg_timestamp(nullptr),
  cosmic_lg_timestamp(nullptr),
  beam_hg_timestamp(nullptr),
  beam_lg_timestamp(nullptr),
  op_gain(nullptr),
  op_gainerror(nullptr)
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
    tree->SetBranchAddress("triggerTime",&triggerTime);


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

    tree->SetBranchAddress("op_gain", &op_gain);
    tree->SetBranchAddress("op_gainerror", &op_gainerror);

    //Acquire # of Entries in file
    nevents = tree->GetEntries();
    std::cout << "Number of Events Constructed:    " << tree->GetEntries() << std::endl;

  }

UBEventWaveform wcopreco::DataReader::Reader(int event_num) {
    if ( event_num > nevents)
      {
        std::cout << "There aren't that many events, didn't work!" << std::endl;
        UBEventWaveform UB_Ev;
        return UB_Ev;
      }
    tree->GetEntry(event_num);

    std::vector<OpWaveformCollection> empty_vec;
    _UB_Ev_wfm.set_wfm_v( empty_vec );
    _UB_Ev_wfm.set_op_gain(*op_gain);
    _UB_Ev_wfm.set_op_gainerror(*op_gainerror);

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
    OpWaveformCollection CHG_wfm_collection;
    CHG_wfm_collection.set_op_gain(*op_gain);
    CHG_wfm_collection.set_op_gainerror(*op_gainerror);

    OpWaveformCollection CLG_wfm_collection;
    CLG_wfm_collection.set_op_gain(*op_gain);
    CLG_wfm_collection.set_op_gainerror(*op_gainerror);

    OpWaveformCollection BHG_wfm_collection;
    BHG_wfm_collection.set_op_gain(*op_gain);
    BHG_wfm_collection.set_op_gainerror(*op_gainerror);

    OpWaveformCollection BLG_wfm_collection;
    BLG_wfm_collection.set_op_gain(*op_gain);
    BLG_wfm_collection.set_op_gainerror(*op_gainerror);

    //Fill up wfm collections
    LoopThroughWfms(*beam_hg_opch, *beam_hg_timestamp, *beam_hg_wf, kbeam_hg, BHG_wfm_collection);
    LoopThroughWfms(*beam_lg_opch, *beam_lg_timestamp, *beam_lg_wf, kbeam_lg, BLG_wfm_collection);
    LoopThroughWfms(*cosmic_hg_opch, *cosmic_hg_timestamp, *cosmic_hg_wf, kcosmic_hg, CHG_wfm_collection);
    LoopThroughWfms(*cosmic_lg_opch, *cosmic_lg_timestamp, *cosmic_lg_wf, kcosmic_lg, CLG_wfm_collection);

    _UB_Ev_wfm.add_entry(BHG_wfm_collection, kbeam_hg );

    _UB_Ev_wfm.add_entry(BLG_wfm_collection, kbeam_lg );

    _UB_Ev_wfm.add_entry(CHG_wfm_collection, kcosmic_hg );

    _UB_Ev_wfm.add_entry(CLG_wfm_collection, kcosmic_lg );

    std::map <int,int> testmap = _UB_Ev_wfm.get_type2index();

    return _UB_Ev_wfm;
  }


  void DataReader::LoopThroughWfms(std::vector<short> ch,
    std::vector<double> timestamp,
    TClonesArray Eventwaveform_root,
    int type,
    OpWaveformCollection &wfm_collection) {
    int count = 0;

    for (unsigned j=0; j < ch.size(); j++){
      TH1S *waveform = (TH1S*)Eventwaveform_root.At(j);
      Int_t n = waveform->GetNbinsX();

      //These IF statements enforces cosmic wf to have 40 bins, and Beam to have 1500
      if (((type == kbeam_hg)||(type==kbeam_lg) )&& n-1 > 1000 ){
          wcopreco::OpWaveform wfm(ch[j]%100, timestamp[j]-triggerTime, type, 1500);
          //Ignore first bin in waveform->GetArray (underflow bin), copy only 1500 bins, not 1501 bins (n-1), 40 not 41
          for (int bin=0; bin<1500; bin++) {
            wfm[bin]=((double)waveform->GetBinContent(bin+1));
            if( ch[j] == 28 ) {
            }
          }

          // This line takes each opwaveform and pushes them to the end of the slowly growing wfm_collection
          wfm_collection.add_waveform(wfm);
        }

      if (((type == kcosmic_hg)||(type==kcosmic_lg) )&& n-1 < 100 ){
          wcopreco::OpWaveform wfm(ch[j]%100, timestamp[j]-triggerTime, type, 40);
          //Ignore first bin in waveform->GetArray (underflow bin), copy only 1500 bins, not 1501 bins (n-1), 40 not 41

          for (int bin=0; bin<40; bin++) {
            wfm[bin]=((double)waveform->GetBinContent(bin+1));
          }
          // This line takes each opwaveform and pushes them to the end of the slowly growing wfm_collection
          wfm_collection.add_waveform(wfm);
        }

    };

    Eventwaveform_root.Clear();
    return;
  };


}
