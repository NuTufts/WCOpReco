#include "WCOpReco/OpWaveform.h"
#include "WCOpReco/OpWaveformCollection.h"
#include "WCOpReco/EventOpWaveforms.h"
#include "WCOpReco/UBEventWaveform.h"
#include "WCOpReco/DataReader.h"
#include "WCOpReco/Deconvolver.h"
#include "WCOpReco/saturation_merger.h"
#include "WCOpReco/HitFinder_cosmic.h"
#include "WCOpReco/Flashes_cosmic.h"
#include "WCOpReco/HitFinder_beam.h"

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
  // wcopreco::Deconvolver tester(&merged_beam, true, true);
  // // std::cout << "Deconvolver declared!" << std::endl;
  // std::vector<wcopreco::kernel_fourier_container> kernel_container_v = tester.get_kernel_container_v();
  //
  // wcopreco::OpWaveform wfm = merged_beam.at(0);
  // std::cout << kernel_container_v.size() << " Size of kernel container_v \n\n\n\n";
  //
  //
  //
  //
  // //do beam hitfinding
  //wcopreco::OpWaveformCollection deconvolved_wfm = tester.Deconvolve_Collection(& merged_beam);
  wcopreco::HitFinder_beam hits_found_beam(wcopreco::OpWaveformCollection merged_beam);


  // //Create the Hitfinder for COSMICS (Currently this also does the flashes for cosmics)
  wcopreco::HitFinder_cosmic hits_found(&merged_cosmic, &op_gain, &op_gainerror);
  std::vector<wcopreco::COphitSelection> hits = hits_found.get_ophits_group();
  wcopreco::Flashes_cosmic flashes_found(hits);
  wcopreco::OpflashSelection flashes = flashes_found.get_cosmic_flashes();
  std::cout << flashes.size() << " flashes were found in the cosmic selection\n";

  std::cout << "\n";
  // Create the Deconvolver (This should just deconvolves the BEAM)
  wcopreco::Deconvolver Does_Nothing(&merged_beam, false, false);
  // wcopreco::OpWaveformCollection DN = Does_Nothing.Deconvolve_Collection(& merged_beam);

  std::cout << "\n";
  // Create the Deconvolver (This should just deconvolves the BEAM)
  wcopreco::Deconvolver All_At_Once(&merged_beam, true, true);
  // wcopreco::OpWaveformCollection AAO = All_At_Once.Deconvolve_Collection(& merged_beam);
  std::cout << "\n";

  // // create the deconvolver in 2 steps
  // wcopreco::Deconvolver Step_One(&merged_beam, true, false);
  // wcopreco::OpWaveformCollection S1 = Step_One.Deconvolve_Collection(& merged_beam);
  // std::cout << "\n";
  //
  // wcopreco::Deconvolver Step_Two(&S1, false, true);
  // wcopreco::OpWaveformCollection S2 = Step_One.Deconvolve_Collection(& S1);
  // std::cout << "\n";
  //
  //Remove Baselines from Original
  wcopreco::OpWaveform orig = merged_beam.at(0);
  All_At_Once.Remove_Baseline_Leading_Edge(&orig);
  All_At_Once.Remove_Baseline_Secondary(&orig);

  std::vector<wcopreco::kernel_fourier_container> kernel_container_v_dn = Does_Nothing.get_kernel_container_v();
  wcopreco::OpWaveform dn = Does_Nothing.Deconvolve_One_Wfm(orig, kernel_container_v_dn.at(orig.get_ChannelNum()));
  wcopreco::OpWaveform dn2 = Does_Nothing.Deconvolve_One_Wfm(dn, kernel_container_v_dn.at(orig.get_ChannelNum()));

  // All_At_Once.Remove_Baseline_Leading_Edge(&dn);
  // All_At_Once.Remove_Baseline_Secondary(&dn);


  std::vector<wcopreco::kernel_fourier_container> kernel_container_v = All_At_Once.get_kernel_container_v();
  wcopreco::OpWaveform aao = All_At_Once.Deconvolve_One_Wfm(orig, kernel_container_v.at(orig.get_ChannelNum()));
  // All_At_Once.Remove_Baseline_Leading_Edge(&aao);
  // All_At_Once.Remove_Baseline_Secondary(&aao);

  All_At_Once.testPlot("Original", orig);
  All_At_Once.testPlot("Do Nothing Dec", dn);
  All_At_Once.testPlot("Do Nothing Dec 2", dn2);


  All_At_Once.testPlot("All at Once", aao);


  // wcopreco::OpWaveform s2 = S2.at(0);
  // std::cout << "=================================================\n";
  // for (int i=0; i<1500;i++){
  //   if (i%100 ==0) {
  //     std::cout << orig.at(i) - dn.at(i) << "\n";
  //     std::cout << orig.at(i) << " Original Waveform\n";
  //     std::cout << dn.at(i) << " 'Does Nothing' Waveform\n";
  //     std::cout << aao.at(i) << " All at once method\n\n";


      // std::cout << s2.at(i) << " Two Step\n";

  //   }
  // }




};
