#include "WCOpReco/OpWaveform.h"
#include "WCOpReco/OpWaveformCollection.h"
#include "WCOpReco/EventOpWaveforms.h"
#include "WCOpReco/UBEventWaveform.h"
#include "WCOpReco/DataReader.h"
#include "WCOpReco/Deconvolver.h"
#include "WCOpReco/saturation_merger.h"
#include "WCOpReco/HitFinder_cosmic.h"
#include "WCOpReco/Flashes_cosmic.h"
#include "WCOpReco/Flashes_beam.h"
#include "WCOpReco/HitFinder_beam.h"
#include "WCOpReco/FlashFiltering.h"
#include "WCOpReco/Run.h"
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

int main(){
  wcopreco::_num_channels = 32; //lots
  wcopreco::_num_types = 6; //lots
  wcopreco::_nbins_by_type = {1500, 1500, 40, 40, 1500, 40}; //lots?
  wcopreco::_sat_threshold = 4080 ; //satmerge, cosmic_merger, probably beam_merger
  wcopreco::_baseline_default =2050; //scale_lowgains in satmerge
  wcopreco::_baseline_difference_max = 8; //scale_lowgains in satmerge, also deconv Remove_Baseline_Secondary
  wcopreco::_cosmic_tick_window = 20; //Cosmic merger in satmerge
  wcopreco::_tick_width_us = .015625;  //cosmic merger in satmerge, Deconvolve_One_Wfm in deconv (1/64) for bin_width and 64 for max_freq_MHz, G(i,k) Hitfinder Beam 15.625/1000, also in Opflash.h and .cxx
  wcopreco::_low_bound_baseline_search = 1500; //findBaselineLg in SatMerger
  wcopreco::_high_bound_baseline_search = 2500; //findBaselineLg in SatMerger
  wcopreco::_nbins_baseline_search = 20; //find findBaselineLg satmerger
  wcopreco::_nbins_saturation_threshold = 3; //satmerger beam and cosmic mergers
  wcopreco::_scaling_by_channel = {10.13, 10.20, 10.13, 10.05, 9.96, 9.95, 10.04, 9.58, 9.42, 9.81, 9.25, 9.61, 9.56, 9.35, 9.99, 9.66, 10.26, 9.82, 10.32, 10.08, 9.77, 9.64, 10.14, 9.74, 9.76, 10.10, 10.48, 9.81, 9.99, 9.79, 9.93, 10.01}; // findScaling in satmerger
  wcopreco::_high_freq_p0 = 0.45;  //deconv HighFreqFilter
  wcopreco::_high_freq_p1 = 3.07;  //deconv HighFreqFilter
  wcopreco::_latelight_filter_p0 = 0.05;  //deconv LateLightFilter
  wcopreco::_latelight_filter_p1 = 0.45;  //deconv LateLightFilter
  wcopreco::_latelight_filter_p2 = 3.07;  //deconv latelight_filter
  wcopreco::_baseline_safety_subtraction = 100; // deconv Remove_Baseline_Secondary
  wcopreco::_xq  = 0.5 ; //deconv cal_mean_rms
  wcopreco::_xq_diff = 0.34 ; //deconv cal_mean_rms
  wcopreco::_n_bins_end_wfm = 4 ; //deconv deconv one wfm end loop 1500-4
  wcopreco::_beam_rebin_size = 250 ; //HitFinder_beam (sort of in opflash.h shows up as 6 where 1500/250 = 6)
  wcopreco::_l1_content_thresh = 0.3 ; // Hitfinder beam 0.3
  wcopreco::_frac_G_t2_first = 0.75 ; //Hitfinder beam G
  wcopreco::_frac_G_sametime = 0.25  ; //Hitfinder beam G
  wcopreco::_G_p0 = 6.0 ; //Hitfinder beam G
  wcopreco::_G_p1 = 3.0 ; //Hitfinder beam G
  wcopreco::_G_p2 = 1.5 ; //Hitfinder beam G
  wcopreco::_Lasso_p0 = 5.0 ; //Hitfinder beam
  wcopreco::_Lasso_p1 = 100000; //Hitfinder beam
  wcopreco::_Lasso_p2 = 0.05 ; //Hitfinder beam
  wcopreco::_totPE_v_thresh = 0.2 ; //Hitfinder beam Also appears in Opflash
  wcopreco::_mult_v_thresh  = 1.5 ; //Hitfinder beam, threshold in PE to determine if add to mult
  wcopreco::_l1_mult_v_thresh  = 1.0 ; //Hitfinder beam
  wcopreco::_ophit_group_t_diff_max  = 0.1 ; // Hitfinder cosmic twice
  wcopreco::_bflash_pe_thresh  = 6.0 ; //Flashes beams
  wcopreco::_bflash_mult_thresh = 3.0 ; //Flashes beams
  wcopreco::_bflash_bin_diff_p0 = 78 ; //Flashes beams 78 is in there 2x
  wcopreco::_bflash_bin_diff_p1 = 4  ; //Flashes beams
  wcopreco::_bflash_bin_diff_p2  = 15 ; //Flashes beams
  wcopreco::_KS_test_thresh  = 0.1 ; //Flashes beams
  wcopreco::_bflash_bin_start_cushion = 2  ; //Flashes beam
  wcopreco::_flash_filter_time_thresh = 2.4 ; //Flashfiltering
  wcopreco::_flash_filter_pe_thresh = 0.7  ; //Flashfiltering
  wcopreco::_rc_tau_badch  = 28.6 ; //UB_rc
  wcopreco::_rc_tau_goodch = 800.0; //UB_rc
  wcopreco::_spe_p0 = 19.6348 ; //UB_spe
  wcopreco::_spe_p1 = 8.18450e-01 ; //UB_spe
  wcopreco::_COphit_integral_thresh = 20e3 ; //COPHIT
  wcopreco::_COphit_baseline_diff_thresh = 50 ;//COPHIT
  wcopreco::_pe_factor  = 2.0; //COPHIT
  wcopreco::_Baseline_uncertainty  = 0.03 ; //Percent uncertay COPHIT
  wcopreco::_Baseline_unc_bad_baseline  = 2.0 ; //Percent Unc if baseline bad COPHIT
  wcopreco::_cal_integral_p0 = 4000;  //COPHIT
  wcopreco::_cal_integral_p1 = 1.06241e+01;  //COPHIT
  wcopreco::_cal_integral_p2 = 2.01214e-04;  //COPHIT
  wcopreco::_cal_integral_p3 = 4.5715824e4;  //COPHIT
  wcopreco::_cal_integral_p4 = 8.62296e+00;  //COPHIT
  wcopreco::_cal_integral_p5 = 6.76898e-04;  //COPHIT
  wcopreco::_PE_err_cosmic = 6.4; //Opflash
  wcopreco::_PE_subtract = 0.15; //Opflash
  wcopreco::_flash_low_time_cushion  = -3; //Opflash
  wcopreco::_flash_high_time_cushion = +37; //Opflash
  wcopreco::_PE_err_beam = 0.2; //Opflash
  wcopreco::_mult_content_thresh = 1.5; //Opflash
  wcopreco::_mult_required = 3; //Opflash
  wcopreco::_PE_err_stat_beam = 1.875;//Opflash
  wcopreco::_PE_err_unc_beam = 0.02;//Opflash
  wcopreco::_do_swap_channels  = true ;//Opflash
  wcopreco::_addl1_pe_thresh = 10.0;//Opflash
  wcopreco::_addl1_mult_thresh = 3.0;//Opflash

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
  wcopreco::Run opreco;
  wcopreco::OpflashSelection flashes = opreco.get_flashes();
  std::cout << flashes.size() << " :Number of flashes\n";
  wcopreco::OpflashSelection flashes_cosmic = opreco.get_flashes_cosmic();
  std::cout << flashes_cosmic.size() << " :Number of cosmic flashes\n";
  wcopreco::OpflashSelection flashes_beam = opreco.get_flashes_beam();
  std::cout << flashes_beam.size() << " :Number of beam flashes\n";
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
