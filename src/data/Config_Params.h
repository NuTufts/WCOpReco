#ifndef CONFIG_PARAMS_H
#define CONFIG_PARAMS_H

#include <vector>
#include <iostream>
#include <sstream>
namespace wcopreco {
  int     _num_channels = 32; //lots
  int     _num_types = 6; //lots
  std::vector<int> _nbins_by_type = {1500, 1500, 40, 40, 1500, 40}; //lots?
  short   _sat_threshold = 4080 ; //satmerge, cosmic_merger, probably beam_merger
  double  _baseline_default =2050; //scale_lowgains in satmerge
  double  _baseline_difference_max = 8; //scale_lowgains in satmerge, also deconv Remove_Baseline_Secondary
  int     _cosmic_tick_window = 20; //Cosmic merger in satmerge
  float   _tick_width_us = .015625;  //cosmic merger in satmerge, Deconvolve_One_Wfm in deconv (1/64) for bin_width and 64 for max_freq_MHz, G(i,k) Hitfinder Beam 15.625/1000, also in Opflash.h and .cxx
  double  _low_bound_baseline_search = 1500; //findBaselineLg in SatMerger
  double  _high_bound_baseline_search = 2500; //findBaselineLg in SatMerger
  int     _nbins_baseline_search = 20; //find findBaselineLg satmerger
  int     _nbins_saturation_threshold = 3; //satmerger beam and cosmic mergers
  std::vector<float> _scaling_by_channel = {10.13, 10.20, 10.13, 10.05, 9.96, 9.95, 10.04, 9.58, 9.42, 9.81, 9.25, 9.61, 9.56, 9.35, 9.99, 9.66, 10.26, 9.82, 10.32, 10.08, 9.77, 9.64, 10.14, 9.74, 9.76, 10.10, 10.48, 9.81, 9.99, 9.79, 9.93, 10.01}; // findScaling in satmerger
  double  _high_freq_p0 = 0.45;  //deconv HighFreqFilter
  double  _high_freq_p1 = 3.07;  //deconv HighFreqFilter
  double  _latelight_filter_p0 = 0.05;  //deconv LateLightFilter
  double  _latelight_filter_p1 = 0.45;  //deconv LateLightFilter
  double  _latelight_filter_p2 = 3.07;  //deconv latelight_filter
  double  _baseline_safety_subtraction = 100; // deconv Remove_Baseline_Secondary
  double  _xq  = 0.5 ; //deconv cal_mean_rms
  double  _xq_diff = 0.34 ; //deconv cal_mean_rms
  int     _n_bins_end_wfm = 4 ; //deconv deconv one wfm end loop 1500-4
  int     _beam_rebin_size = 250 ; //HitFinder_beam (sort of in opflash.h shows up as 6 where 1500/250 = 6)
  double  _l1_content_thresh = 0.3 ; // Hitfinder beam 0.3
  double  _frac_G_t2_first = 0.75 ; //Hitfinder beam G
  double  _frac_G_sametime = 0.25  ; //Hitfinder beam G
  double  _G_p0 = 6.0 ; //Hitfinder beam G
  double  _G_p1 = 3.0 ; //Hitfinder beam G
  double  _G_p2 = 1.5 ; //Hitfinder beam G
  double  _Lasso_p0 = 5.0 ; //Hitfinder beam
  int     _Lasso_p1 = 100000; //Hitfinder beam
  double  _Lasso_p2 = 0.05 ; //Hitfinder beam
  double  _totPE_v_thresh = 0.2 ; //Hitfinder beam Also appears in Opflash
  double  _mult_v_thresh  = 1.5 ; //Hitfinder beam, threshold in PE to determine if add to mult
  double  _l1_mult_v_thresh  = 1.0 ; //Hitfinder beam
  double  _ophit_group_t_diff_max  = 0.1 ; // Hitfinder cosmic twice
  double  _bflash_pe_thresh  = 6.0 ; //Flashes beams
  double  _bflash_mult_thresh = 3.0 ; //Flashes beams
  int     _bflash_bin_diff_p0 = 78 ; //Flashes beams 78 is in there 2x
  int     _bflash_bin_diff_p1 = 4  ; //Flashes beams
  int     _bflash_bin_diff_p2  = 15 ; //Flashes beams
  double  _KS_test_thresh  = 0.1 ; //Flashes beams
  int     _bflash_bin_start_cushion = 2  ; //Flashes beam
  double  _flash_filter_time_thresh = 2.4 ; //Flashfiltering
  double  _flash_filter_pe_thresh = 0.7  ; //Flashfiltering
  double  _rc_tau_badch  = 28.6 ; //UB_rc
  double  _rc_tau_goodch = 800.0; //UB_rc
  double  _spe_p0 = 19.6348 ; //UB_spe
  double  _spe_p1 = 8.18450e-01 ; //UB_spe
  double  _COphit_integral_thresh = 20e3 ; //COPHIT
  double  _COphit_baseline_diff_thresh = 50 ;//COPHIT
  double  _pe_factor  = 2.0; //COPHIT
  double  _Baseline_uncertainty  = 0.03 ; //Percent uncertainty COPHIT
  double  _Baseline_unc_bad_baseline  = 2.0 ; //Percent Unc if baseline bad COPHIT
  double  _cal_integral_p0 = 4000;  //COPHIT
  double  _cal_integral_p1 = 1.06241e+01;  //COPHIT
  double  _cal_integral_p2 = 2.01214e-04;  //COPHIT
  double  _cal_integral_p3 = 4.5715824e4;  //COPHIT
  double  _cal_integral_p4 = 8.62296e+00;  //COPHIT
  double  _cal_integral_p5 = 6.76898e-04;  //COPHIT
  double  _PE_err_cosmic = 6.4; //Opflash
  double  _PE_subtract = 0.15; //Opflash
  int     _flash_low_time_cushion  = -3; //Opflash
  int     _flash_high_time_cushion = +37; //Opflash
  double  _PE_err_beam = 0.2; //Opflash
  double  _mult_content_thresh = 1.5; //Opflash
  int     _mult_required = 3; //Opflash
  double  _PE_err_stat_beam = 1.875;//Opflash
  double  _PE_err_unc_beam = 0.02;//Opflash
  bool    _do_swap_channels  = true ;//Opflash
  double  _addl1_pe_thresh = 10.0;//Opflash
  double  _addl1_mult_thresh = 3.0;//Opflash


  //Params NEEDING set:
  std::vector<float> gain;
  std::vector<float> gainerror;


  void _set_num_channels(int n){_num_channels = n;}
  int _get_num_channels(){return _num_channels;}

  void _set_num_types_and_bins_per__type(int n, std::vector<int> bins_per_type);

  void _set_sat_threshold(short s){_sat_threshold = s;}
  short _get_sat_threshold(){return _sat_threshold;}

  void _set_baseline_default(double b){_baseline_default = b;}
  double _get_baseline_default(){return _baseline_default;}

  void _set_baseline_difference_max(double b){_baseline_difference_max = b;}
  double _get_baseline_difference_max(){return _baseline_difference_max;}

  void _set_cosmic_tick_window(int n){_cosmic_tick_window = n;}
  int _get_cosmic_tick_window(){return _cosmic_tick_window;}

  void _set_tick_width_us(float width){_tick_width_us = width;}
  float _get_tick_width_us(){return _tick_width_us;}

  void _set_low_bound_baseline_search(double bound){_low_bound_baseline_search = bound;}
  double _get_low_bound_baseline_search(){return _low_bound_baseline_search;}

  void _set_high_bound_baseline_search(double bound){_high_bound_baseline_search = bound;}
  double _get_high_bound_baseline_search(){return _high_bound_baseline_search;}

  void _set_nbins_baseline_search(int n){_nbins_baseline_search = n;}
  int _get_nbins_baseline_search(){return _nbins_baseline_search;}

  void _set_nbins_saturation_threshold(int n){_nbins_saturation_threshold = n;}
  int _get_nbins_saturation_threshold(){return _nbins_saturation_threshold;}

  void _set_scaling_by_channel(std::vector<float> scalings_v);
  std::vector<float> _get_scaling_by_channel(){return _scaling_by_channel;}

  void _set_high_freq_p0(double p0){_high_freq_p0 = p0;}
  double _get_high_freq_p0(){return _high_freq_p0;}

  void _set_high_freq_p1(double p1){_high_freq_p1 = p1;}
  double _get_high_freq_p1(){return _high_freq_p1;}

  void _set_latelight_filter_p0(double p0){_latelight_filter_p0 = p0;}
  double _get_latelight_filter_p0(){return _latelight_filter_p0;}

  void _set_latelight_filter_p1(double p1){_latelight_filter_p1 = p1;}
  double _get_latelight_filter_p1(){return _latelight_filter_p1;}

  void _set_latelight_filter_p2(double p2){_latelight_filter_p2 = p2;}
  double _get_latelight_filter_p2(){return _latelight_filter_p2;}

  void _set_baseline_safety_subtraction(double adjust){_baseline_safety_subtraction = adjust;}
  double _get_baseline_safety_subtraction(){return _baseline_safety_subtraction;}

  void _set_xq(double value) {_xq = value;}
  double _get_xq() {return _xq;}

  void _set_xq_diff(double value) {_xq_diff = value;}
  double _get_xq_diff() {return _xq_diff;}

  void _set_n_bins_end_wfm(int n){_n_bins_end_wfm = n;}
  int _get_n_bins_end_wfm(){return _n_bins_end_wfm;}

  void _set_beam_rebin_size(int n){_beam_rebin_size = n;}
  int _get_beam_rebin_size(){return _beam_rebin_size;}

  void _set_G_p0(double value) {_G_p0 = value;}
  double _get_G_p0() {return _G_p0;}

  void _set_G_p1(double value) {_G_p1 = value;}
  double _get_G_p1() {return _G_p1;}

  void _set_G_p2(double value) {_G_p2 = value;}
  double _get_G_p2() {return _G_p2;}

  void _set_Lasso_p0(double value) {_Lasso_p0 = value;}
  double _get_Lasso_p0() {return _Lasso_p0;}

  void _set_Lasso_p1(int value) {_Lasso_p1 = value;}
  int _get_Lasso_p1() {return _Lasso_p1;}

  void _set_Lasso_p2(double value) {_Lasso_p2 = value;}
  double _get_Lasso_p2() {return _Lasso_p2;}

  void _set_totPE_v_thresh(double value) {_totPE_v_thresh = value;}
  double _get_totPE_v_thresh() {return _totPE_v_thresh;}

  void _set_mult_v_thresh(double value) {_mult_v_thresh = value;}
  double _get_mult_v_thresh() {return _mult_v_thresh;}

  void _set_l1_mult_v_thresh(double value) {_l1_mult_v_thresh = value;}
  double _get_l1_mult_v_thresh() {return _l1_mult_v_thresh;}

  void _set_ophit_group_t_diff_max(double value) {_ophit_group_t_diff_max = value;}
  double _get_ophit_group_t_diff_max() {return _ophit_group_t_diff_max;}

  void _set_bflash_pe_thresh(double value) {_bflash_pe_thresh = value;}
  double _get_bflash_pe_thresh() {return _bflash_pe_thresh;}

  void _set_bflash_mult_thresh(double value) {_bflash_mult_thresh = value;}
  double _get_bflash_mult_thresh() {return _bflash_mult_thresh;}

  void _set_bflash_bin_diff_p0(int value) {_bflash_bin_diff_p0 = value;}
  int _get_bflash_bin_diff_p0() {return _bflash_bin_diff_p0;}

  void _set_bflash_bin_diff_p1(int value) {_bflash_bin_diff_p1 = value;}
  int _get_bflash_bin_diff_p1() {return _bflash_bin_diff_p1;}

  void _set_bflash_bin_diff_p2(int value) {_bflash_bin_diff_p2 = value;}
  int _get_bflash_bin_diff_p2() {return _bflash_bin_diff_p2;}

  void _set_KS_test_thresh(double value) {_KS_test_thresh = value;}
  double _get_KS_test_thresh() {return _KS_test_thresh;}

  void _set_bflash_bin_start_cushion(int value) {_bflash_bin_start_cushion = value;}
  int _get_bflash_bin_start_cushion() {return _bflash_bin_start_cushion;}

  void _set_flash_filter_time_thresh(double value) {_flash_filter_time_thresh = value;}
  double _get_flash_filter_time_thresh() {return _flash_filter_time_thresh;}

  void _set_flash_filter_pe_thresh(double value) {_flash_filter_pe_thresh = value;}
  double _get_flash_filter_pe_thresh() {return _flash_filter_pe_thresh;}

  void _set_rc_tau_badch(double value) {_rc_tau_badch = value;}
  double _get_rc_tau_badch() {return _rc_tau_badch;}

  void _set_rc_tau_goodch(double value) {_rc_tau_goodch = value;}
  double _get_rc_tau_goodch() {return _rc_tau_goodch;}

  void _set_spe_p0(double value) {_spe_p0 = value;}
  double _get_spe_p0() {return _spe_p0;}

  void _set_spe_p1(double value) {_spe_p1 = value;}
  double _get_spe_p1() {return _spe_p1;}

  void _set_COphit_integral_thresh(double value) {_COphit_integral_thresh = value;}
  double _get_COphit_integral_thresh() {return _COphit_integral_thresh;}

  void _set_COphit_baseline_diff_thresh(double value) {_COphit_baseline_diff_thresh = value;}
  double _get_COphit_baseline_diff_thresh() {return _COphit_baseline_diff_thresh;}

  void _set_pe_factor(double value) {_pe_factor = value;}
  double _get_pe_factor() {return _pe_factor;}

  void _set_Baseline_uncertainty(double value) {_Baseline_uncertainty = value;}
  double _get_Baseline_uncertainty() {return _Baseline_uncertainty;}

  void _set_Baseline_unc_bad_baseline(double value) {_Baseline_unc_bad_baseline = value;}
  double _get_Baseline_unc_bad_baseline() {return _Baseline_unc_bad_baseline;}

  void _set_cal_integral_p0(double value) {_cal_integral_p0 = value;}
  double _get_cal_integral_p0() {return _cal_integral_p0;}

  void _set_cal_integral_p1(double value) {_cal_integral_p1 = value;}
  double _get_cal_integral_p1() {return _cal_integral_p1;}

  void _set_cal_integral_p2(double value) {_cal_integral_p2 = value;}
  double _get_cal_integral_p2() {return _cal_integral_p2;}

  void _set_cal_integral_p3(double value) {_cal_integral_p3 = value;}
  double _get_cal_integral_p3() {return _cal_integral_p3;}

  void _set_cal_integral_p4(double value) {_cal_integral_p4 = value;}
  double _get_cal_integral_p4() {return _cal_integral_p4;}

  void _set_cal_integral_p5(double value) {_cal_integral_p5 = value;}
  double _get_cal_integral_p5() {return _cal_integral_p5;}

  void _set_PE_err_cosmic(double value) {_PE_err_cosmic = value;}
  double _get_PE_err_cosmic() {return _PE_err_cosmic;}

  void _set_PE_subtract(double value) {_PE_subtract = value;}
  double _get_PE_subtract() {return _PE_subtract;}

  void _set_flash_low_time_cushion(int value) {_flash_low_time_cushion = value;}
  int _get_flash_low_time_cushion() {return _flash_low_time_cushion;}

  void _set_flash_high_time_cushion(int value) {_flash_high_time_cushion = value;}
  int _get_flash_high_time_cushion() {return _flash_high_time_cushion;}

  void _set_PE_err_beam(double value) {_PE_err_beam = value;}
  double _get_PE_err_beam() {return _PE_err_beam;}

  void _set_mult_content_thresh(double value) {_mult_content_thresh = value;}
  double _get_mult_content_thresh() {return _mult_content_thresh;}

  void _set_mult_required(int value) {_mult_required = value;}
  int _get_mult_required() {return _mult_required;}

  void _set_PE_err_stat_beam(double value) {_PE_err_stat_beam = value;}
  double _get_PE_err_stat_beam() {return _PE_err_stat_beam;}

  void _set_PE_err_unc_beam(double value) {_PE_err_unc_beam = value;}
  double _get_PE_err_unc_beam() {return _PE_err_unc_beam;}

  void _set_do_swap_channels(bool do_swap) {_do_swap_channels = do_swap;}
  bool _get_do_swap_channels() {return _do_swap_channels;}

  void _set_addl1_pe_thresh(double value) {_addl1_pe_thresh = value;}
  double _get_addl1_pe_thresh() {return _addl1_pe_thresh;}

  void _set_addl1_mult_thresh(double value) {_addl1_mult_thresh = value;}
  double _get_addl1_mult_thresh() {return _addl1_mult_thresh;}
  }

  #endif
