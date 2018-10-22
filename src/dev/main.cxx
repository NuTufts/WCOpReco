#include "WCOpReco/OpWaveform.h"
#include "WCOpReco/OpWaveformCollection.h"
#include "WCOpReco/EventOpWaveforms.h"
#include "WCOpReco/UBEventWaveform.h"
#include "WCOpReco/DataReader.h"
#include "WCOpReco/deconvolver.h"
#include "WCOpReco/saturation_merger.h"
#include "WCOpReco/HitFinder.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"

#include <iostream>
#include <sstream>

int main(){

  std::cout << "Hello world" << std::endl;



  // This tests the reader:
  // std::string file = "src/data/celltree.root";
  // wcopreco::DataReader reader(file);
  // std::cout << "Filepath is set to:   " << file << std::endl;
  // int event_num = 3;
  // reader.Reader(event_num);

  // //This tests the deconvolver:
  // wcopreco::deconvolver tester;
  // std::cout << "Deconvolver declared!" << std::endl;
  // tester.deconv_test();

  //This tests the saturation_merger and HitFinder:
  std::string file = "src/data/celltree.root";
  wcopreco::DataReader reader(file);
  std::cout << "\n\nFilepath is set to:   " << file << std::endl;
  wcopreco::UBEventWaveform _UB_Ev_wfm;
  int EVENT_NUM =50;
  _UB_Ev_wfm = reader.Reader(EVENT_NUM);
  std::vector<float> op_gain = _UB_Ev_wfm.get_op_gain();
  std::vector<float> op_gainerror = _UB_Ev_wfm.get_op_gainerror();

  wcopreco::saturation_merger merger(_UB_Ev_wfm);
  //testing makeBeamPairs (event 18)
  wcopreco::OpWaveformCollection merged_beam = merger.get_merged_beam();
  wcopreco::OpWaveformCollection merged_cosmic = merger.get_merged_cosmic();
  wcopreco::UBEventWaveform UB_Ev_Merged = merger.get_merged_UB_Ev();



  //need to add test for HitFinder
  wcopreco::HitFinder hits_found(&merged_cosmic, &op_gain, &op_gainerror);
  wcopreco::OpflashSelection flashes = hits_found.get_cosmic_flashes();
  std::cout << flashes.size() << " flashes were found in the cosmic selection\n";


  // for (int EVENT_NUM=0;EVENT_NUM<53;EVENT_NUM++){
  //   _UB_Ev_wfm = reader.Reader(EVENT_NUM);
  //   wcopreco::saturation_merger merger(_UB_Ev_wfm);
  //}





};
