#include "Config_Params.h"

namespace wcopreco {
  Config_Params::Config_Params()
  {
  }

  void Config_Params::set_num_channels(int n) {
      _cfg_deconvolver._num_channels = n ;
      _cfg_flashesbeam._num_channels = n ;
      _cfg_hitfinder_beam._num_channels = n ;
      _cfg_opflash._num_channels = n ;
      _cfg_saturation_merger._num_channels = n ;


  }

  void Config_Params::set_tick_width_us(float width) {
      _cfg_deconvolver._tick_width_us = width ;
      _cfg_hitfinder_beam._tick_width_us = width ;
      _cfg_opflash._tick_width_us = width ;
      _cfg_saturation_merger._tick_width_us = width ;


  }

  void Config_Params::set_rebin_frac(int n) {
      _cfg_flashesbeam._rebin_frac = n ;
      _cfg_hitfinder_beam._rebin_frac = n ;
      _cfg_opflash._rebin_frac = n ;

  }

  void Config_Params::set_nbins_beam(int n) {
      _cfg_deconvolver._nbins_beam = n ;
      _cfg_flashesbeam._nbins_beam = n ;
      _cfg_hitfinder_beam._nbins_beam = n ;
  }

  void Config_Params::set_baseline_difference_max(double p) {
      _cfg_deconvolver._baseline_difference_max = p ;
      _cfg_saturation_merger._baseline_difference_max = p ;
  }

  void Config_Params::set_nbins_baseline_search(int n) {
      _cfg_deconvolver._nbins_baseline_search = n ;
      _cfg_saturation_merger._nbins_baseline_search = n ;
  }

  void Config_Params::set_baseline_default(int baseline) {
      _cfg_cophit._baseline_default = baseline ;
      _cfg_saturation_merger._baseline_default = baseline ;
  }

  void Config_Params::set_nbins_cosmic(int n) {
      _cfg_cophit._nbins_cosmic = n ;
  }

  void Config_Params::set_COphit_integral_thresh(double thresh) {
      _cfg_cophit._COphit_integral_thresh = thresh ;
  }

  void Config_Params::set_COphit_baseline_diff_thresh(double thresh) {
      _cfg_cophit._COphit_baseline_diff_thresh = thresh ;
  }

  void Config_Params::set_pe_factor(double factor) {
      _cfg_cophit._pe_factor = factor ;
  }


  void Config_Params::set_Baseline_uncertainty(double unc) {
      _cfg_cophit._Baseline_uncertainty = unc ;
  }

  void Config_Params::set_Baseline_unc_bad_baseline(double unc) {
      _cfg_cophit._Baseline_unc_bad_baseline = unc ;
  }

  void Config_Params::set_cal_integral_p0(double p) {
      _cfg_cophit._cal_integral_p0 = p ;
  }

  void Config_Params::set_cal_integral_p1(double p) {
      _cfg_cophit._cal_integral_p1 = p ;
  }

  void Config_Params::set_cal_integral_p2(double p) {
      _cfg_cophit._cal_integral_p2 = p ;
  }

  void Config_Params::set_cal_integral_p3(double p) {
      _cfg_cophit._cal_integral_p3 = p ;
  }

  void Config_Params::set_cal_integral_p4(double p) {
      _cfg_cophit._cal_integral_p4 = p ;
  }

  void Config_Params::set_cal_integral_p5(double p) {
      _cfg_cophit._cal_integral_p5 = p ;
  }

  void Config_Params::set_high_freq_p0(double p) {
      _cfg_deconvolver._high_freq_p0 = p ;
  }

  void Config_Params::set_high_freq_p1(double p) {
      _cfg_deconvolver._high_freq_p1 = p ;
  }

  void Config_Params::set_latelight_filter_p0(double p) {
      _cfg_deconvolver._latelight_filter_p0 = p ;
  }

  void Config_Params::set_latelight_filter_p1(double p) {
      _cfg_deconvolver._latelight_filter_p1 = p ;
  }

  void Config_Params::set_latelight_filter_p2(double p) {
      _cfg_deconvolver._latelight_filter_p2 = p ;
  }

  void Config_Params::set_baseline_safety_subtraction(double sub) {
      _cfg_deconvolver._baseline_safety_subtraction = sub ;
  }

  void Config_Params::set_xq(double x) {
      _cfg_deconvolver._xq = x ;
  }

  void Config_Params::set_xq_diff(double diff) {
      _cfg_deconvolver._xq_diff = diff ;
  }

  void Config_Params::set_n_bins_end_wfm(int n) {
      _cfg_deconvolver._n_bins_end_wfm = n ;
  }

  void Config_Params::set_small_content_bump(double bump) {
      _cfg_deconvolver._small_content_bump = bump ;
  }

  void Config_Params::set_bflash_pe_thresh(double thresh) {
      _cfg_flashesbeam._bflash_pe_thresh = thresh ;
  }

  void Config_Params::set_bflash_mult_thresh(double thresh) {
      _cfg_flashesbeam._bflash_mult_thresh = thresh ;
  }

  void Config_Params::set_bflash_bin_diff_p0(int p) {
      _cfg_flashesbeam._bflash_bin_diff_p0 = p ;
  }

  void Config_Params::set_bflash_bin_diff_p1(int p) {
      _cfg_flashesbeam._bflash_bin_diff_p1 = p ;
  }

  void Config_Params::set_bflash_bin_diff_p2(int p) {
      _cfg_flashesbeam._bflash_bin_diff_p2 = p ;
  }

  void Config_Params::set_KS_test_thresh(double thresh) {
      _cfg_flashesbeam._KS_test_thresh = thresh ;
  }

  void Config_Params::set_bflash_bin_start_cushion(int cushion) {
      _cfg_flashesbeam._bflash_bin_start_cushion = cushion ;
  }

  void Config_Params::set_flash_filter_time_thresh(double thresh) {
      _cfg_flashfiltering._flash_filter_time_thresh = thresh ;
  }

  void Config_Params::set_flash_filter_pe_thresh(double thresh) {
      _cfg_flashfiltering._flash_filter_pe_thresh = thresh ;
  }

  void Config_Params::set_do_swap_channels(bool do_swap) {
      _cfg_flashfiltering._do_swap_channels = do_swap ;
  }

  void Config_Params::set_l1_content_thresh(double thresh) {
      _cfg_hitfinder_beam._l1_content_thresh = thresh ;
  }

  void Config_Params::set_frac_G_t2_first(double frac) {
      _cfg_hitfinder_beam._frac_G_t2_first = frac ;
  }

  void Config_Params::set_frac_G_sametime(double frac) {
      _cfg_hitfinder_beam._frac_G_sametime = frac ;
  }

  void Config_Params::set_G_p0(double p) {
      _cfg_hitfinder_beam._G_p0 = p ;
  }

  void Config_Params::set_G_p1(double p) {
      _cfg_hitfinder_beam._G_p1 = p ;
  }

  void Config_Params::set_G_p2(double p) {
      _cfg_hitfinder_beam._G_p2 = p ;
  }
  void Config_Params::set_Lasso_p0(double p) {
      _cfg_hitfinder_beam._Lasso_p0 = p ;
  }

  void Config_Params::set_Lasso_p1(int p) {
      _cfg_hitfinder_beam._Lasso_p1 = p ;
  }

  void Config_Params::set_Lasso_p2(double p) {
      _cfg_hitfinder_beam._Lasso_p2 = p ;
  }
  void Config_Params::set_totPE_v_thresh(double thresh) {
      _cfg_hitfinder_beam._totPE_v_thresh = thresh ;
  }

  void Config_Params::set_mult_v_thresh(double thresh) {
      _cfg_hitfinder_beam._mult_v_thresh = thresh ;
  }

  void Config_Params::set_l1_mult_v_thresh(double thresh) {
      _cfg_hitfinder_beam._l1_mult_v_thresh = thresh ;
  }

  void Config_Params::set_ophit_group_t_diff_max(double max) {
      _cfg_hitfinder_cosmic._ophit_group_t_diff_max = max ;
  }

  void Config_Params::set_PE_err_cosmic(double err) {
      _cfg_opflash._PE_err_cosmic = err ;
  }

  void Config_Params::set_PE_subtract(double sub) {
      _cfg_opflash._PE_subtract = sub ;
  }

  void Config_Params::set_flash_low_time_cushion(int bin) {
      _cfg_opflash._flash_low_time_cushion = bin ;
  }

  void Config_Params::set_flash_high_time_cushion(int bin) {
      _cfg_opflash._flash_high_time_cushion = bin ;
  }

  void Config_Params::set_PE_err_beam(double err) {
      _cfg_opflash._PE_err_beam = err ;
  }

  void Config_Params::set_mult_content_thresh(double thresh) {
      _cfg_opflash._mult_content_thresh = thresh ;
  }

  void Config_Params::set_mult_required(int req) {
      _cfg_opflash._mult_required = req ;
  }

  void Config_Params::set_PE_err_stat_beam(double err) {
      _cfg_opflash._PE_err_stat_beam = err ;
  }

  void Config_Params::set_PE_err_unc_beam(double err) {
      _cfg_opflash._PE_err_unc_beam = err ;
  }

  void Config_Params::set_addl1_pe_thresh(double thresh) {
      _cfg_opflash._addl1_pe_thresh = thresh ;
  }

  void Config_Params::set_addl1_mult_thresh(double thresh) {
      _cfg_opflash._addl1_mult_thresh = thresh ;
  }

  void Config_Params::set_sat_threshold(short thresh) {
      _cfg_saturation_merger._sat_threshold = thresh ;
  }

  void Config_Params::set_cosmic_tick_window(int n) {
      _cfg_saturation_merger._cosmic_tick_window = n ;
  }

  void Config_Params::set_low_bound_baseline_search(double d) {
      _cfg_saturation_merger._low_bound_baseline_search = d ;
  }

  void Config_Params::set_high_bound_baseline_search(double d) {
      _cfg_saturation_merger._high_bound_baseline_search = d ;
  }

  void Config_Params::set_nbins_saturation_threshold(int n) {
      _cfg_saturation_merger._nbins_saturation_threshold = n ;
  }

  void Config_Params::set_scaling_by_channel(std::vector<float> scales_v) {
      _cfg_saturation_merger._scaling_by_channel = scales_v ;
  }
  // void Config_Params::set(double p) {
  //     _cfg_saturation_merger. = p ;
  // }
  //
  // void Config_Params::set(double p) {
  //     _cfg_saturation_merger. = p ;
  // }
  //
  // void Config_Params::set(double p) {
  //     _cfg_saturation_merger. = p ;
  // }
  // void Config_Params::set(double p) {
  //     _cfg_saturation_merger. = p ;
  // }
  //
  // void Config_Params::set(double p) {
  //     _cfg_saturation_merger. = p ;
  // }

  // void Config_Params::set(double p) {
  //     _cfg_deconvolver. = p ;
  // }
}


//   _num_channels = 32; //lots
//   _num_types = 6; //lots
//   _nbins_by_type = {1500, 1500, 40, 40, 1500, 40}; //lots?
//   _sat_threshold = 4080 ; //satmerge, cosmic_merger, probably beam_merger
//   _baseline_default =2050; //scale_lowgains in satmerge
//   _baseline_difference_max = 8; //scale_lowgains in satmerge, also deconv Remove_Baseline_Secondary
//   _cosmic_tick_window = 20; //Cosmic merger in satmerge
//   _tick_width_us = .015625;  //cosmic merger in satmerge, Deconvolve_One_Wfm in deconv (1/64) for bin_width and 64 for max_freq_MHz, G(i,k) Hitfinder Beam 15.625/1000, also in Opflash.h and .cxx
//   _low_bound_baseline_search = 1500; //findBaselineLg in SatMerger
//   _high_bound_baseline_search = 2500; //findBaselineLg in SatMerger
//   _nbins_baseline_search = 20; //find findBaselineLg satmerger
//   _nbins_saturation_threshold = 3; //satmerger beam and cosmic mergers
//   _scaling_by_channel = {10.13, 10.20, 10.13, 10.05, 9.96, 9.95, 10.04, 9.58, 9.42, 9.81, 9.25, 9.61, 9.56, 9.35, 9.99, 9.66, 10.26, 9.82, 10.32, 10.08, 9.77, 9.64, 10.14, 9.74, 9.76, 10.10, 10.48, 9.81, 9.99, 9.79, 9.93, 10.01}; // findScaling in satmerger
//   _high_freq_p0 = 0.45;  //deconv HighFreqFilter
//   _high_freq_p1 = 3.07;  //deconv HighFreqFilter
//   _latelight_filter_p0 = 0.05;  //deconv LateLightFilter
//   _latelight_filter_p1 = 0.45;  //deconv LateLightFilter
//   _latelight_filter_p2 = 3.07;  //deconv latelight_filter
//   _baseline_safety_subtraction = 100; // deconv Remove_Baseline_Secondary
//   _xq  = 0.5 ; //deconv cal_mean_rms
//   _xq_diff = 0.34 ; //deconv cal_mean_rms
//   _n_bins_end_wfm = 4 ; //deconv deconv one wfm end loop 1500-4
//   _beam_rebin_size = 250 ; //HitFinder_beam (sort of in opflash.h shows up as 6 where 1500/250 = 6)
//   _l1_content_thresh = 0.3 ; // Hitfinder beam 0.3
//   _frac_G_t2_first = 0.75 ; //Hitfinder beam G
//   _frac_G_sametime = 0.25  ; //Hitfinder beam G
//   _G_p0 = 6.0 ; //Hitfinder beam G
//   _G_p1 = 3.0 ; //Hitfinder beam G
//   _G_p2 = 1.5 ; //Hitfinder beam G
//   _Lasso_p0 = 5.0 ; //Hitfinder beam
//   _Lasso_p1 = 100000; //Hitfinder beam
//   _Lasso_p2 = 0.05 ; //Hitfinder beam
//   _totPE_v_thresh = 0.2 ; //Hitfinder beam Also appears in Opflash
//   _mult_v_thresh  = 1.5 ; //Hitfinder beam, threshold in PE to determine if add to mult
//   _l1_mult_v_thresh  = 1.0 ; //Hitfinder beam
//   _ophit_group_t_diff_max  = 0.1 ; // Hitfinder cosmic twice
//   _bflash_pe_thresh  = 6.0 ; //Flashes beams
//   _bflash_mult_thresh = 3.0 ; //Flashes beams
//   _bflash_bin_diff_p0 = 78 ; //Flashes beams 78 is in there 2x
//   _bflash_bin_diff_p1 = 4  ; //Flashes beams
//   _bflash_bin_diff_p2  = 15 ; //Flashes beams
//   _KS_test_thresh  = 0.1 ; //Flashes beams
//   _bflash_bin_start_cushion = 2  ; //Flashes beam
//   _flash_filter_time_thresh = 2.4 ; //Flashfiltering
//   _flash_filter_pe_thresh = 0.7  ; //Flashfiltering
//   _rc_tau_badch  = 28.6 ; //UB_rc
//   _rc_tau_goodch = 800.0; //UB_rc
//   _spe_p0 = 19.6348 ; //UB_spe
//   _spe_p1 = 8.18450e-01 ; //UB_spe
//   _COphit_integral_thresh = 20e3 ; //COPHIT
//   _COphit_baseline_diff_thresh = 50 ;//COPHIT
//   _pe_factor  = 2.0; //COPHIT
//   _Baseline_uncertainty  = 0.03 ; //Percent uncertay COPHIT
//   _Baseline_unc_bad_baseline  = 2.0 ; //Percent Unc if baseline bad COPHIT
//   _cal_integral_p0 = 4000;  //COPHIT
//   _cal_integral_p1 = 1.06241e+01;  //COPHIT
//   _cal_integral_p2 = 2.01214e-04;  //COPHIT
//   _cal_integral_p3 = 4.5715824e4;  //COPHIT
//   _cal_integral_p4 = 8.62296e+00;  //COPHIT
//   _cal_integral_p5 = 6.76898e-04;  //COPHIT
//   _PE_err_cosmic = 6.4; //Opflash
//   _PE_subtract = 0.15; //Opflash
//   _flash_low_time_cushion  = -3; //Opflash
//   _flash_high_time_cushion = +37; //Opflash
//   _PE_err_beam = 0.2; //Opflash
//   _mult_content_thresh = 1.5; //Opflash
//   _mult_required = 3; //Opflash
//   _PE_err_stat_beam = 1.875;//Opflash
//   _PE_err_unc_beam = 0.02;//Opflash
//   _do_swap_channels  = true ;//Opflash
//   _addl1_pe_thresh = 10.0;//Opflash
//   _addl1_mult_thresh = 3.0;//Opflash
//
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
//
