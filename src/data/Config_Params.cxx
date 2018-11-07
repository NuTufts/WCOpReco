#include "Config_Params.h"

namespace wcopreco {
    // _num_channels = 32; //lots
    // _num_types = 6; //lots
    // _nbins_by_type = {1500, 1500, 40, 40, 1500, 40}; //lots?
    // _sat_threshold = 4080 ; //satmerge, cosmic_merger, probably beam_merger
    // _baseline_default =2050; //scale_lowgains in satmerge
    // _baseline_difference_max = 8; //scale_lowgains in satmerge, also deconv Remove_Baseline_Secondary
    // _cosmic_tick_window = 20; //Cosmic merger in satmerge
    // _tick_width_us = .015625;  //cosmic merger in satmerge, Deconvolve_One_Wfm in deconv (1/64) for bin_width and 64 for max_freq_MHz, G(i,k) Hitfinder Beam 15.625/1000, also in Opflash.h and .cxx
    // _low_bound_baseline_search = 1500; //findBaselineLg in SatMerger
    // _high_bound_baseline_search = 2500; //findBaselineLg in SatMerger
    // _nbins_baseline_search = 20; //find findBaselineLg satmerger
    // _nbins_saturation_threshold = 3; //satmerger beam and cosmic mergers
    // _scaling_by_channel = {10.13, 10.20, 10.13, 10.05, 9.96, 9.95, 10.04, 9.58, 9.42, 9.81, 9.25, 9.61, 9.56, 9.35, 9.99, 9.66, 10.26, 9.82, 10.32, 10.08, 9.77, 9.64, 10.14, 9.74, 9.76, 10.10, 10.48, 9.81, 9.99, 9.79, 9.93, 10.01}; // findScaling in satmerger
    // _high_freq_p0 = 0.45;  //deconv HighFreqFilter
    // _high_freq_p1 = 3.07;  //deconv HighFreqFilter
    // _latelight_filter_p0 = 0.05;  //deconv LateLightFilter
    // _latelight_filter_p1 = 0.45;  //deconv LateLightFilter
    // _latelight_filter_p2 = 3.07;  //deconv latelight_filter
    // _baseline_safety_subtraction = 100; // deconv Remove_Baseline_Secondary
    // _xq  = 0.5 ; //deconv cal_mean_rms
    // _xq_diff = 0.34 ; //deconv cal_mean_rms
    // _n_bins_end_wfm = 4 ; //deconv deconv one wfm end loop 1500-4
    // _beam_rebin_size = 250 ; //HitFinder_beam (sort of in opflash.h shows up as 6 where 1500/250 = 6)
    // _l1_content_thresh = 0.3 ; // Hitfinder beam 0.3
    // _frac_G_t2_first = 0.75 ; //Hitfinder beam G
    // _frac_G_sametime = 0.25  ; //Hitfinder beam G
    // _G_p0 = 6.0 ; //Hitfinder beam G
    // _G_p1 = 3.0 ; //Hitfinder beam G
    // _G_p2 = 1.5 ; //Hitfinder beam G
    // _Lasso_p0 = 5.0 ; //Hitfinder beam
    // _Lasso_p1 = 100000; //Hitfinder beam
    // _Lasso_p2 = 0.05 ; //Hitfinder beam
    // _totPE_v_thresh = 0.2 ; //Hitfinder beam Also appears in Opflash
    // _mult_v_thresh  = 1.5 ; //Hitfinder beam, threshold in PE to determine if add to mult
    // _l1_mult_v_thresh  = 1.0 ; //Hitfinder beam
    // _ophit_group_t_diff_max  = 0.1 ; // Hitfinder cosmic twice
    // _bflash_pe_thresh  = 6.0 ; //Flashes beams
    // _bflash_mult_thresh = 3.0 ; //Flashes beams
    // _bflash_bin_diff_p0 = 78 ; //Flashes beams 78 is in there 2x
    // _bflash_bin_diff_p1 = 4  ; //Flashes beams
    // _bflash_bin_diff_p2  = 15 ; //Flashes beams
    // _KS_test_thresh  = 0.1 ; //Flashes beams
    // _bflash_bin_start_cushion = 2  ; //Flashes beam
    // _flash_filter_time_thresh = 2.4 ; //Flashfiltering
    // _flash_filter_pe_thresh = 0.7  ; //Flashfiltering
    // _rc_tau_badch  = 28.6 ; //UB_rc
    // _rc_tau_goodch = 800.0; //UB_rc
    // _spe_p0 = 19.6348 ; //UB_spe
    // _spe_p1 = 8.18450e-01 ; //UB_spe
    // _COphit_egral_thresh = 20e3 ; //COPHIT
    // _COphit_baseline_diff_thresh = 50 ;//COPHIT
    // _pe_factor  = 2.0; //COPHIT
    // _Baseline_uncertay  = 0.03 ; //Percent uncertay COPHIT
    // _Baseline_unc_bad_baseline  = 2.0 ; //Percent Unc if baseline bad COPHIT
    // _cal_egral_p0 = 4000;  //COPHIT
    // _cal_egral_p1 = 1.06241e+01;  //COPHIT
    // _cal_egral_p2 = 2.01214e-04;  //COPHIT
    // _cal_egral_p3 = 4.5715824e4;  //COPHIT
    // _cal_egral_p4 = 8.62296e+00;  //COPHIT
    // _cal_egral_p5 = 6.76898e-04;  //COPHIT
    // _PE_err_cosmic = 6.4; //Opflash
    // _PE_subtract = 0.15; //Opflash
    // _flash_low_time_cushion  = -3; //Opflash
    // _flash_high_time_cushion = +37; //Opflash
    // _PE_err_beam = 0.2; //Opflash
    // _mult_content_thresh = 1.5; //Opflash
    // _mult_required = 3; //Opflash
    // _PE_err_stat_beam = 1.875;//Opflash
    // _PE_err_unc_beam = 0.02;//Opflash
    // _do_swap_channels  = true ;//Opflash
    // _addl1_pe_thresh = 10.0;//Opflash
    // _addl1_mult_thresh = 3.0;//Opflash

  //
  // void _set_num_types_and_bins_per__type(int n, std::vector<int> bins_per_type) {
  //     if (n == bins_per_type.size()) {
  //       _num_types = n;
  //       _nbins_by_type = bins_per_type;
  //     }
  //     else{
  //       std::cout << "Number of types not equal to size of bins_per_type vector\n";
  //     }
  //
  // }
  //
  // void _set_scaling_by_channel(std::vector<float> scalings_v) {
  //   _scaling_by_channel = scalings_v;
  //   if (scalings_v.size() != _num_channels) {
  //     std::cout << "Careful, size of scaling vector is not the same as the number of channels currently set.\n";
  //     std::cout << _num_channels << " Is the number of channels, " << scalings_v.size() << "  Is the size of scalings vector set\n";
  //   }
  // }


}
