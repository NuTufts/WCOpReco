#ifndef CONFIG_PARAMS_H
#define CONFIG_PARAMS_H

#include <vector>
#include <iostream>
#include <sstream>
namespace wcopreco {
  extern int     _num_channels; //lots
  extern int     _num_types; //lots
  extern std::vector<int> _nbins_by_type; //lots?
  extern short   _sat_threshold; //satmerge, cosmic_merger, probably beam_merger
  extern double  _baseline_default; //scale_lowgains in satmerge
  extern double  _baseline_difference_max; //scale_lowgains in satmerge, also deconv Remove_Baseline_Secondary
  extern int     _cosmic_tick_window; //Cosmic merger in satmerge
  extern float   _tick_width_us;  //cosmic merger in satmerge, Deconvolve_One_Wfm in deconv (1/64) for bin_width and 64 for max_freq_MHz, G(i,k) Hitfinder Beam 15.625/1000, also in Opflash.h and .cxx
  extern double  _low_bound_baseline_search; //findBaselineLg in SatMerger
  extern double  _high_bound_baseline_search; //findBaselineLg in SatMerger
  extern int     _nbins_baseline_search; //find findBaselineLg satmerger
  extern int     _nbins_saturation_threshold; //satmerger beam and cosmic mergers
  extern std::vector<float> _scaling_by_channel; // findScaling in satmerger
  extern double  _high_freq_p0;  //deconv HighFreqFilter
  extern double  _high_freq_p1;  //deconv HighFreqFilter
  extern double  _latelight_filter_p0;  //deconv LateLightFilter
  extern double  _latelight_filter_p1;  //deconv LateLightFilter
  extern double  _latelight_filter_p2;  //deconv latelight_filter
  extern double  _baseline_safety_subtraction; // deconv Remove_Baseline_Secondary
  extern double  _xq; //deconv cal_mean_rms
  extern double  _xq_diff; //deconv cal_mean_rms
  extern int     _n_bins_end_wfm; //deconv deconv one wfm end loop 1500-4
  extern int     _beam_rebin_size; //HitFinder_beam (sort of in opflash.h shows up as 6 where 1500/250 = 6)
  extern double  _l1_content_thresh; // Hitfinder beam 0.3
  extern double  _frac_G_t2_first; //Hitfinder beam G
  extern double  _frac_G_sametime; //Hitfinder beam G
  extern double  _G_p0; //Hitfinder beam G
  extern double  _G_p1; //Hitfinder beam G
  extern double  _G_p2 ; //Hitfinder beam G
  extern double  _Lasso_p0; //Hitfinder beam
  extern int     _Lasso_p1; //Hitfinder beam
  extern double  _Lasso_p2; //Hitfinder beam
  extern double  _totPE_v_thresh; //Hitfinder beam Also appears in Opflash
  extern double  _mult_v_thresh; //Hitfinder beam, threshold in PE to determine if add to mult
  extern double  _l1_mult_v_thresh; //Hitfinder beam
  extern double  _ophit_group_t_diff_max; // Hitfinder cosmic twice
  extern double  _bflash_pe_thresh; //Flashes beams
  extern double  _bflash_mult_thresh; //Flashes beams
  extern int     _bflash_bin_diff_p0; //Flashes beams 78 is in there 2x
  extern int     _bflash_bin_diff_p1; //Flashes beams
  extern int     _bflash_bin_diff_p2; //Flashes beams
  extern double  _KS_test_thresh; //Flashes beams
  extern int     _bflash_bin_start_cushion; //Flashes beam
  extern double  _flash_filter_time_thresh; //Flashfiltering
  extern double  _flash_filter_pe_thresh; //Flashfiltering
  extern double  _rc_tau_badch; //UB_rc
  extern double  _rc_tau_goodch; //UB_rc
  extern double  _spe_p0; //UB_spe
  extern double  _spe_p1; //UB_spe
  extern double  _COphit_integral_thresh; //COPHIT
  extern double  _COphit_baseline_diff_thresh;//COPHIT
  extern double  _pe_factor; //COPHIT
  extern double  _Baseline_uncertainty; //Percent uncertainty COPHIT
  extern double  _Baseline_unc_bad_baseline; //Percent Unc if baseline bad COPHIT
  extern double  _cal_integral_p0;  //COPHIT
  extern double  _cal_integral_p1;  //COPHIT
  extern double  _cal_integral_p2;  //COPHIT
  extern double  _cal_integral_p3;  //COPHIT
  extern double  _cal_integral_p4;  //COPHIT
  extern double  _cal_integral_p5;  //COPHIT
  extern double  _PE_err_cosmic; //Opflash
  extern double  _PE_subtract; //Opflash
  extern int     _flash_low_time_cushion; //Opflash
  extern int     _flash_high_time_cushion; //Opflash
  extern double  _PE_err_beam; //Opflash
  extern double  _mult_content_thresh; //Opflash
  extern int     _mult_required; //Opflash
  extern double  _PE_err_stat_beam;//Opflash
  extern double  _PE_err_unc_beam;//Opflash
  extern bool    _do_swap_channels;//Opflash
  extern double  _addl1_pe_thresh;//Opflash
  extern double  _addl1_mult_thresh;//Opflash


  //Params NEEDING set:
  extern std::vector<float> _gain;
  extern std::vector<float> _gainerror;


  // void _set_num_channels(int n){_num_channels = n;}
  //int _get_num_channels(){return _num_channels;}
  //
  // void _set_num_types_and_bins_per__type(int n, std::vector<int> bins_per_type);
  //
  // void _set_sat_threshold(short s){_sat_threshold = s;}
  // short _get_sat_threshold(){return _sat_threshold;}
  //
  // void _set_baseline_default(double b){_baseline_default = b;}
  // double _get_baseline_default(){return _baseline_default;}
  //
  // void _set_baseline_difference_max(double b){_baseline_difference_max = b;}
  // double _get_baseline_difference_max(){return _baseline_difference_max;}
  //
  // void _set_cosmic_tick_window(int n){_cosmic_tick_window = n;}
  // int _get_cosmic_tick_window(){return _cosmic_tick_window;}
  //
  // void _set_tick_width_us(float width){_tick_width_us = width;}
  // float _get_tick_width_us(){return _tick_width_us;}
  //
  // void _set_low_bound_baseline_search(double bound){_low_bound_baseline_search = bound;}
  // double _get_low_bound_baseline_search(){return _low_bound_baseline_search;}
  //
  // void _set_high_bound_baseline_search(double bound){_high_bound_baseline_search = bound;}
  // double _get_high_bound_baseline_search(){return _high_bound_baseline_search;}
  //
  // void _set_nbins_baseline_search(int n){_nbins_baseline_search = n;}
  // int _get_nbins_baseline_search(){return _nbins_baseline_search;}
  //
  // void _set_nbins_saturation_threshold(int n){_nbins_saturation_threshold = n;}
  // int _get_nbins_saturation_threshold(){return _nbins_saturation_threshold;}
  //
  // void _set_scaling_by_channel(std::vector<float> scalings_v);
  // std::vector<float> _get_scaling_by_channel(){return _scaling_by_channel;}
  //
  // void _set_high_freq_p0(double p0){_high_freq_p0 = p0;}
  // double _get_high_freq_p0(){return _high_freq_p0;}
  //
  // void _set_high_freq_p1(double p1){_high_freq_p1 = p1;}
  // double _get_high_freq_p1(){return _high_freq_p1;}
  //
  // void _set_latelight_filter_p0(double p0){_latelight_filter_p0 = p0;}
  // double _get_latelight_filter_p0(){return _latelight_filter_p0;}
  //
  // void _set_latelight_filter_p1(double p1){_latelight_filter_p1 = p1;}
  // double _get_latelight_filter_p1(){return _latelight_filter_p1;}
  //
  // void _set_latelight_filter_p2(double p2){_latelight_filter_p2 = p2;}
  // double _get_latelight_filter_p2(){return _latelight_filter_p2;}
  //
  // void _set_baseline_safety_subtraction(double adjust){_baseline_safety_subtraction = adjust;}
  // double _get_baseline_safety_subtraction(){return _baseline_safety_subtraction;}
  //
  // void _set_xq(double value) {_xq = value;}
  // double _get_xq() {return _xq;}
  //
  // void _set_xq_diff(double value) {_xq_diff = value;}
  // double _get_xq_diff() {return _xq_diff;}
  //
  // void _set_n_bins_end_wfm(int n){_n_bins_end_wfm = n;}
  // int _get_n_bins_end_wfm(){return _n_bins_end_wfm;}
  //
  // void _set_beam_rebin_size(int n){_beam_rebin_size = n;}
  // int _get_beam_rebin_size(){return _beam_rebin_size;}
  //
  // void _set_G_p0(double value) {_G_p0 = value;}
  // double _get_G_p0() {return _G_p0;}
  //
  // void _set_G_p1(double value) {_G_p1 = value;}
  // double _get_G_p1() {return _G_p1;}
  //
  // void _set_G_p2(double value) {_G_p2 = value;}
  // double _get_G_p2() {return _G_p2;}
  //
  // void _set_Lasso_p0(double value) {_Lasso_p0 = value;}
  // double _get_Lasso_p0() {return _Lasso_p0;}
  //
  // void _set_Lasso_p1(int value) {_Lasso_p1 = value;}
  // int _get_Lasso_p1() {return _Lasso_p1;}
  //
  // void _set_Lasso_p2(double value) {_Lasso_p2 = value;}
  // double _get_Lasso_p2() {return _Lasso_p2;}
  //
  // void _set_totPE_v_thresh(double value) {_totPE_v_thresh = value;}
  // double _get_totPE_v_thresh() {return _totPE_v_thresh;}
  //
  // void _set_mult_v_thresh(double value) {_mult_v_thresh = value;}
  // double _get_mult_v_thresh() {return _mult_v_thresh;}
  //
  // void _set_l1_mult_v_thresh(double value) {_l1_mult_v_thresh = value;}
  // double _get_l1_mult_v_thresh() {return _l1_mult_v_thresh;}
  //
  // void _set_ophit_group_t_diff_max(double value) {_ophit_group_t_diff_max = value;}
  // double _get_ophit_group_t_diff_max() {return _ophit_group_t_diff_max;}
  //
  // void _set_bflash_pe_thresh(double value) {_bflash_pe_thresh = value;}
  // double _get_bflash_pe_thresh() {return _bflash_pe_thresh;}
  //
  // void _set_bflash_mult_thresh(double value) {_bflash_mult_thresh = value;}
  // double _get_bflash_mult_thresh() {return _bflash_mult_thresh;}
  //
  // void _set_bflash_bin_diff_p0(int value) {_bflash_bin_diff_p0 = value;}
  // int _get_bflash_bin_diff_p0() {return _bflash_bin_diff_p0;}
  //
  // void _set_bflash_bin_diff_p1(int value) {_bflash_bin_diff_p1 = value;}
  // int _get_bflash_bin_diff_p1() {return _bflash_bin_diff_p1;}
  //
  // void _set_bflash_bin_diff_p2(int value) {_bflash_bin_diff_p2 = value;}
  // int _get_bflash_bin_diff_p2() {return _bflash_bin_diff_p2;}
  //
  // void _set_KS_test_thresh(double value) {_KS_test_thresh = value;}
  // double _get_KS_test_thresh() {return _KS_test_thresh;}
  //
  // void _set_bflash_bin_start_cushion(int value) {_bflash_bin_start_cushion = value;}
  // int _get_bflash_bin_start_cushion() {return _bflash_bin_start_cushion;}
  //
  // void _set_flash_filter_time_thresh(double value) {_flash_filter_time_thresh = value;}
  // double _get_flash_filter_time_thresh() {return _flash_filter_time_thresh;}
  //
  // void _set_flash_filter_pe_thresh(double value) {_flash_filter_pe_thresh = value;}
  // double _get_flash_filter_pe_thresh() {return _flash_filter_pe_thresh;}
  //
  // void _set_rc_tau_badch(double value) {_rc_tau_badch = value;}
  // double _get_rc_tau_badch() {return _rc_tau_badch;}
  //
  // void _set_rc_tau_goodch(double value) {_rc_tau_goodch = value;}
  // double _get_rc_tau_goodch() {return _rc_tau_goodch;}
  //
  // void _set_spe_p0(double value) {_spe_p0 = value;}
  // double _get_spe_p0() {return _spe_p0;}
  //
  // void _set_spe_p1(double value) {_spe_p1 = value;}
  // double _get_spe_p1() {return _spe_p1;}
  //
  // void _set_COphit_integral_thresh(double value) {_COphit_integral_thresh = value;}
  // double _get_COphit_integral_thresh() {return _COphit_integral_thresh;}
  //
  // void _set_COphit_baseline_diff_thresh(double value) {_COphit_baseline_diff_thresh = value;}
  // double _get_COphit_baseline_diff_thresh() {return _COphit_baseline_diff_thresh;}
  //
  // void _set_pe_factor(double value) {_pe_factor = value;}
  // double _get_pe_factor() {return _pe_factor;}
  //
  // void _set_Baseline_uncertainty(double value) {_Baseline_uncertainty = value;}
  // double _get_Baseline_uncertainty() {return _Baseline_uncertainty;}
  //
  // void _set_Baseline_unc_bad_baseline(double value) {_Baseline_unc_bad_baseline = value;}
  // double _get_Baseline_unc_bad_baseline() {return _Baseline_unc_bad_baseline;}
  //
  // void _set_cal_integral_p0(double value) {_cal_integral_p0 = value;}
  // double _get_cal_integral_p0() {return _cal_integral_p0;}
  //
  // void _set_cal_integral_p1(double value) {_cal_integral_p1 = value;}
  // double _get_cal_integral_p1() {return _cal_integral_p1;}
  //
  // void _set_cal_integral_p2(double value) {_cal_integral_p2 = value;}
  // double _get_cal_integral_p2() {return _cal_integral_p2;}
  //
  // void _set_cal_integral_p3(double value) {_cal_integral_p3 = value;}
  // double _get_cal_integral_p3() {return _cal_integral_p3;}
  //
  // void _set_cal_integral_p4(double value) {_cal_integral_p4 = value;}
  // double _get_cal_integral_p4() {return _cal_integral_p4;}
  //
  // void _set_cal_integral_p5(double value) {_cal_integral_p5 = value;}
  // double _get_cal_integral_p5() {return _cal_integral_p5;}
  //
  // void _set_PE_err_cosmic(double value) {_PE_err_cosmic = value;}
  // double _get_PE_err_cosmic() {return _PE_err_cosmic;}
  //
  // void _set_PE_subtract(double value) {_PE_subtract = value;}
  // double _get_PE_subtract() {return _PE_subtract;}
  //
  // void _set_flash_low_time_cushion(int value) {_flash_low_time_cushion = value;}
  // int _get_flash_low_time_cushion() {return _flash_low_time_cushion;}
  //
  // void _set_flash_high_time_cushion(int value) {_flash_high_time_cushion = value;}
  // int _get_flash_high_time_cushion() {return _flash_high_time_cushion;}
  //
  // void _set_PE_err_beam(double value) {_PE_err_beam = value;}
  // double _get_PE_err_beam() {return _PE_err_beam;}
  //
  // void _set_mult_content_thresh(double value) {_mult_content_thresh = value;}
  // double _get_mult_content_thresh() {return _mult_content_thresh;}
  //
  // void _set_mult_required(int value) {_mult_required = value;}
  // int _get_mult_required() {return _mult_required;}
  //
  // void _set_PE_err_stat_beam(double value) {_PE_err_stat_beam = value;}
  // double _get_PE_err_stat_beam() {return _PE_err_stat_beam;}
  //
  // void _set_PE_err_unc_beam(double value) {_PE_err_unc_beam = value;}
  // double _get_PE_err_unc_beam() {return _PE_err_unc_beam;}
  //
  // void _set_do_swap_channels(bool do_swap) {_do_swap_channels = do_swap;}
  // bool _get_do_swap_channels() {return _do_swap_channels;}
  //
  // void _set_addl1_pe_thresh(double value) {_addl1_pe_thresh = value;}
  // double _get_addl1_pe_thresh() {return _addl1_pe_thresh;}
  //
  // void _set_addl1_mult_thresh(double value) {_addl1_mult_thresh = value;}
  // double _get_addl1_mult_thresh() {return _addl1_mult_thresh;}
  }

  #endif
