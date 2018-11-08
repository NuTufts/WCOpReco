#include "WCOpReco/OpWaveform.h"
#include "WCOpReco/OpWaveformCollection.h"
#include "WCOpReco/EventOpWaveforms.h"
#include "WCOpReco/UBEventWaveform.h"
#include "WCOpReco/DataReader.h"
#include "WCOpReco/Deconvolver.h"
#include "WCOpReco/Saturation_Merger.h"
#include "WCOpReco/HitFinder_cosmic.h"
#include "WCOpReco/Flashes_cosmic.h"
#include "WCOpReco/Flashes_beam.h"
#include "WCOpReco/HitFinder_beam.h"
#include "WCOpReco/FlashFiltering.h"
#include "WCOpReco/UBAlgo.h"
#include "WCOpReco/Config_Params.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"

#include <iostream>
#include <sstream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

//Construct the vector of kernel containers (one container per channel)
std::vector<wcopreco::kernel_fourier_container> Build_UB_kernels(wcopreco::Config_Params cfg_all, std::vector<float> op_gain){
  std::vector<wcopreco::kernel_fourier_container> kernel_container_v;
  kernel_container_v.resize(cfg_all._get_cfg_deconvolver()._get_num_channels());
  wcopreco::UB_rc *rc_good_ch = new wcopreco::UB_rc(true, false, cfg_all._get_cfg_ub_rc());
  wcopreco::UB_rc *rc_bad_ch = new wcopreco::UB_rc(true, true, cfg_all._get_cfg_ub_rc());
  for (int i =0 ; i<cfg_all._get_cfg_deconvolver()._get_num_channels(); i++){
    wcopreco::UB_spe *spe = new wcopreco::UB_spe(true, op_gain.at(i), cfg_all._get_cfg_ub_spe()); //Place UB_spe on heap, so object not deleted
    kernel_container_v.at(i).add_kernel(spe);
    if ( false == cfg_all._get_cfg_cophit()._channel_status_v.at(i) ){
      kernel_container_v.at(i).add_kernel(rc_bad_ch);
    }
    else{
      kernel_container_v.at(i).add_kernel(rc_good_ch);
    }
  }
  return kernel_container_v;
}

int main(){
  clock_t t;
//   clock_t dataread;
//   clock_t satmerger;
//   clock_t hitsbeam;
//   clock_t flashbeam;
//   clock_t hitscosmic;
//   clock_t flashcosmic;
//   clock_t flashfilter;
  t=clock();
  //std::cout << wcopreco::_WIDTH << " Did it work?\n";
  //Set the filepath
  std::string file = "src/data/celltree.root";
  std::cout << "\n\nFilepath is set to:   " << file << std::endl;

  //Open the reader, choose event number, create the UBEventWaveform _UB_Ev_wfm
  wcopreco::DataReader reader(&file);
  wcopreco::UBEventWaveform _UB_Ev_wfm;

  wcopreco::Config_Params cfg_all;
  cfg_all.Check_common_parameters();
  wcopreco::UBAlgo opreco_run(cfg_all);

  //change with a config parameter eventually?
  for (int EVENT_NUM = 0; EVENT_NUM < 52; EVENT_NUM ++){

      _UB_Ev_wfm = reader.Reader(EVENT_NUM);
      std::vector<float> op_gain = _UB_Ev_wfm.get_op_gain();
      std::vector<float> op_gainerror = _UB_Ev_wfm.get_op_gainerror();

      //Construct the vector of kernel containers (one container per channel)

      std::vector<wcopreco::kernel_fourier_container> kernel_container_v = Build_UB_kernels(cfg_all, op_gain);

      opreco_run.Run(&_UB_Ev_wfm, &op_gain, &op_gainerror, &kernel_container_v);
      wcopreco::OpWaveformCollection merged_beam = opreco_run.get_merged_beam();
      wcopreco::OpWaveformCollection merged_cosmic = opreco_run.get_merged_cosmic();
      wcopreco::OpflashSelection flashes = opreco_run.get_flashes();
      wcopreco::OpflashSelection flashes_cosmic = opreco_run.get_flashes_cosmic();
      wcopreco::OpflashSelection flashes_beam = opreco_run.get_flashes_beam();

      std::cout << flashes.size() << " :Number of flashes\n";
      std::cout << flashes_cosmic.size() << " :Number of cosmic flashes\n";
      std::cout << flashes_beam.size() << " :Number of beam flashes\n";

  }
//
//
//   //Set the filepath
//   std::string file = "src/data/celltree.root";
//   std::cout << "\n\nFilepath is set to:   " << file << std::endl;
//
//   //Open the reader, choose event number, create the UBEventWaveform _UB_Ev_wfm
//   wcopreco::DataReader reader(file);
//   wcopreco::UBEventWaveform _UB_Ev_wfm;
//   bool do_loop = true;
//   int EVENT_NUM =22;
//   int size = EVENT_NUM+1;
//
//   if (do_loop){
//     EVENT_NUM=0;
//     size = 52;
//   }

//   for (EVENT_NUM;EVENT_NUM<size;EVENT_NUM++){
//     _UB_Ev_wfm = reader.Reader(EVENT_NUM);
//     std::vector<float> op_gain = _UB_Ev_wfm.get_op_gain();
//     std::vector<float> op_gainerror = _UB_Ev_wfm.get_op_gainerror();
//     dataread = clock();
//     // std::cout << "\n";
//     // std::cout << _UB_Ev_wfm.get__wfm_v().at(2).size() << " Number of Waveform in Cosmic HG\n";
//     // std::cout << _UB_Ev_wfm.get__wfm_v().at(3).size() << " Number of Waveform in Cosmic LG\n";
//
//
//
//     //create the merger and then get a Merged UBEventWaveform UB_Ev_Merged
//     wcopreco::saturation_merger merger(_UB_Ev_wfm);
//     wcopreco::OpWaveformCollection merged_beam = merger.get_merged_beam(); //This is inside UB_Ev_Merged
//     wcopreco::OpWaveformCollection merged_cosmic = merger.get_merged_cosmic(); //This is inside UB_Ev_Merged
//     wcopreco::UBEventWaveform UB_Ev_Merged = merger.get_merged_UB_Ev();
//     satmerger = clock();
//     //std::cout << UB_Ev_Merged.get__wfm_v().at(5).size() << " Number of Waveform in Cosmic LG\n";
//     //std::cout << UB_Ev_Merged.get__wfm_v().at(5).size() << " Number of Waveform in Cosmic LG\n";
//     // std::cout << UB_Ev_Merged.get__wfm_v().at(5).size() << " Number of Waveform in Cosmic Merged\n";
//     // std::cout << merged_cosmic.size() << " Number of Waveform in Cosmic Merged (CONFIRMED)\n\n";
//
//
        // //Construct the vector of kernel containers (one container per channel)
        // std::vector<wcopreco::kernel_fourier_container> kernel_container_v;
        // kernel_container_v.resize(32);
        // wcopreco::UB_rc *rc_good_ch = new wcopreco::UB_rc(true, false);
        // wcopreco::UB_rc *rc_bad_ch = new wcopreco::UB_rc(true, true);
        // for (int i =0 ; i<32; i++){
        //    wcopreco::UB_spe *spe = new wcopreco::UB_spe(true, op_gain.at(i)); //Place UB_spe on heap, so object not deleted
        //   kernel_container_v.at(i).add_kernel(spe);
        //   if (i == 28){
        //     kernel_container_v.at(i).add_kernel(rc_bad_ch);
        //   }
        //   else{
        //     kernel_container_v.at(i).add_kernel(rc_good_ch);
        //   }
        // }
        //
        // //do beam hitfinding
        // wcopreco::HitFinder_beam hits_found_beam(merged_beam, kernel_container_v);

//     //wcopreco::OpWaveformCollection deconvolved_wfm = tester.Deconvolve_Collection(& merged_beam);
//     std::vector<double> totPE_v = hits_found_beam.get_totPE_v();
//     std::vector<double> mult_v =hits_found_beam.get_mult_v();
//     std::vector<double> l1_totPE_v =hits_found_beam.get_l1_totPE_v();
//     std::vector<double> l1_mult_v = hits_found_beam.get_l1_mult_v();
//     std::vector< std::vector<double> > decon_vv = hits_found_beam.get_decon_vv();
//     hitsbeam = clock();
//
//     double beam_start_time =merged_beam.at(0).get_time_from_trigger();
//
//
//     wcopreco::Flashes_beam flashfinder_beam( totPE_v, mult_v, l1_totPE_v, l1_mult_v, decon_vv, beam_start_time );
//     wcopreco::OpflashSelection flashes_beam = flashfinder_beam.get_beam_flashes();
//     // std::cout << "\n\n" << flashes_beam.size() << " Beam Flashes in Event\n";
//     flashbeam = clock();
//
//     // //Create the Hitfinder for COSMICS (Currently this also does the flashes for cosmics)
//     wcopreco::HitFinder_cosmic hits_found(&merged_cosmic, &op_gain, &op_gainerror);
//     std::vector<wcopreco::COphitSelection> hits = hits_found.get_ophits_group();
//     hitscosmic = clock();
//
//     wcopreco::Flashes_cosmic flashfinder_cosmic(hits);
//     wcopreco::OpflashSelection flashes_cosmic = flashfinder_cosmic.get_cosmic_flashes();
//     // std::cout << flashes_cosmic.size() << " Cosmic Flashes in Event\n";
//     flashcosmic=clock();
//
//     // std::cout << flashes.size() << " flashes were found in the cosmic selection\n";
//
//     //flash matching
//     wcopreco::FlashFiltering flashesfiltered(flashes_cosmic, flashes_beam);
//     wcopreco::OpflashSelection flashes = flashesfiltered.get_flashes();
//     flashfilter =clock();

//     for (int i =0 ; i<flashes.size(); i++) {
//         if (flashes.at(i)->get_type() ==2) std::cout << flashes.at(i)->get_total_PE() << "\n";
//     }
//
// }

//   flashfilter = flashfilter - flashcosmic;
//   flashcosmic = flashcosmic - hitscosmic;
//   hitscosmic  = hitscosmic  - flashbeam;
//   flashbeam   = flashbeam   - hitsbeam;
//   hitsbeam    = hitsbeam    - satmerger;
//   satmerger   = satmerger   - dataread;
//   dataread    = dataread    - t;
  t = clock() - t;
//
	std::cout << "Total time:           " << t*1.0/CLOCKS_PER_SEC << " seconds" << std::endl << std::endl;
//   // std::cout << "DataRead Time:        " << dataread*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "DataRead Fraction:           " << (double)dataread/t  <<  std::endl << std::endl;
//   // std::cout << "SatMerger Time:       " << satmerger*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "SatMerger Fraction:          " << (double)satmerger/t  <<  std::endl << std::endl;
//   // std::cout << "HitsBeam Time:        " << hitsbeam*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "HitsBeam Fraction:           " << (double)hitsbeam/t  <<  std::endl << std::endl;
//   // std::cout << "Flashbeam Time:       " << flashbeam*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "FlashBeam Fraction:          " << (double)flashbeam/t  <<  std::endl << std::endl;
//   // std::cout << "HitsCosmic Time:      " << hitscosmic*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "HitsCosmic Fraction:         " << (double)hitscosmic/t  <<  std::endl << std::endl;
//   // std::cout << "Flashcosmic Time:     " << flashcosmic*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "Flashcosmic Fraction:        " << (double)flashcosmic/t  <<  std::endl << std::endl;
//   // std::cout << "FlashFilter Time:     " << flashfilter*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "FlashFilter Fraction:        " << (double)flashfilter/t  <<  std::endl << std::endl;
//   // std::cout << "Percentage Check :    " << (double)flashfilter/t+(double)flashcosmic/t+(double)hitscosmic/t+(double)flashbeam/t+(double)hitsbeam/t+(double)satmerger/t+(double)dataread/t << std::endl;
//

return 0;
};
