#include "WCOpReco/OpWaveform.h"
#include "WCOpReco/OpWaveformCollection.h"
#include "WCOpReco/EventOpWaveforms.h"
#include "WCOpReco/UBEventWaveform.h"
#include "WCOpReco/DataReader.h"
#include "WCOpReco/Deconvolver.h"
#include "WCOpReco/saturation_merger.h"
#include "WCOpReco/HitFinder_cosmic.h"

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







  //Set the filepath
  std::string file = "src/data/celltree.root";
  std::cout << "\n\nFilepath is set to:   " << file << std::endl;

  //Open the reader, choose event number, create the UBEventWaveform _UB_Ev_wfm
  wcopreco::DataReader reader(file);
  wcopreco::UBEventWaveform _UB_Ev_wfm;
  int EVENT_NUM =50;

  _UB_Ev_wfm = reader.Reader(EVENT_NUM);
  std::vector<float> op_gain = _UB_Ev_wfm.get_op_gain();
  std::vector<float> op_gainerror = _UB_Ev_wfm.get_op_gainerror();



  //create the merger and then get a Merged UBEventWaveform UB_Ev_Merged
  wcopreco::saturation_merger merger(_UB_Ev_wfm);
  wcopreco::OpWaveformCollection merged_beam = merger.get_merged_beam(); //This is inside UB_Ev_Merged
  wcopreco::OpWaveformCollection merged_cosmic = merger.get_merged_cosmic(); //This is inside UB_Ev_Merged
  wcopreco::UBEventWaveform UB_Ev_Merged = merger.get_merged_UB_Ev();




  // Create the Deconvolver (This should just deconvolves the BEAM)
  wcopreco::Deconvolver tester(&merged_beam, false);
  // std::cout << "Deconvolver declared!" << std::endl;
  std::vector<wcopreco::kernel_fourier_container> kernel_container_v = tester.get_kernel_container_v();

  wcopreco::OpWaveform wfm = merged_beam.at(0);
  std::cout << kernel_container_v.size() << "Size of kernel container_v \n\n\n\n";
  //Construct the vector of kernel containers (one container per channel)
  wcopreco::UB_rc rc(true);
  for (int i =0 ; i<32; i++){
    std::cout << tester.get_kernel_container_v().at(i).size() << " Before\n";
    tester.add_kernel_container_entry(&rc,i);
    std::cout << tester.get_kernel_container_v().at(i).size() << " After \n\n\n\n";

  }
  tester.Deconvolve_One_Wfm(wfm, kernel_container_v.at(wfm.get_ChannelNum()));


  // //Create the Hitfinder for COSMICS (Currently this also does the flashes for cosmics)
  // wcopreco::HitFinder_cosmic hits_found(&merged_cosmic, &op_gain, &op_gainerror);
  // wcopreco::OpflashSelection flashes = hits_found.get_cosmic_flashes();
  // std::cout << flashes.size() << " flashes were found in the cosmic selection\n";







};
