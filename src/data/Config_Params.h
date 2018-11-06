#ifndef CONFIG_PARAMS_H
#define CONFIG_PARAMS_H

#include <vector>
#include <iostream>
#include <sstream>

namespace wcopreco {
  float _WIDTH=50.0;


  class Config_Params {
    public:
      Config_Params();
      virtual ~Config_Params() {};

      void set_num_channels(int n){num_channels = n;}
      int get_num_channels(){return num_channels;}

      void set_num_types_and_bins_per__type(int n, std::vector<int> bins_per_type);

      void set_baseline_default(double b){baseline_default = b;}
      double get_baseline_default(){return baseline_default;}

      void set_baseline_difference_max(double b){baseline_difference_max = b;}
      double get_baseline_difference_max(){return baseline_difference_max;}

      void set_cosmic_tick_window(int n){cosmic_tick_window = n;}
      int get_cosmic_tick_window(){return cosmic_tick_window;}

      void set_tick_width_us(float width){tick_width_us = width;}
      float get_tick_width_us(){return tick_width_us;}

      void set_low_bound_baseline_search(double bound){low_bound_baseline_search = bound;}
      double get_low_bound_baseline_search(){return low_bound_baseline_search;}

      void set_high_bound_baseline_search(double bound){high_bound_baseline_search = bound;}
      double get_high_bound_baseline_search(){return high_bound_baseline_search;}

      void set_nbins_baseline_search(int n){nbins_baseline_search = n;}
      int get_nbins_baseline_search(){return nbins_baseline_search;}

      void set_nbins_saturation_threshold(int n){nbins_saturation_threshold = n;}
      int get_nbins_saturation_threshold(){return nbins_saturation_threshold;}

      void set_scaling_by_channel(std::vector<float> scalings_v);
      std::vector<float> get_scaling_by_channel(){return scaling_by_channel;}

      void set_high_freq_p0(double p0){high_freq_p0 = p0;}
      double get_high_freq_p0(){return high_freq_p0;}

      void set_high_freq_p1(double p1){high_freq_p1 = p1;}
      double get_high_freq_p1(){return high_freq_p1;}

      void set_latelight_filter_p0(double p0){latelight_filter_p0 = p0;}
      double get_latelight_filter_p0(){return latelight_filter_p0;}

      void set_latelight_filter_p1(double p1){latelight_filter_p1 = p1;}
      double get_latelight_filter_p1(){return latelight_filter_p1;}

      void set_latelight_filter_p2(double p2){latelight_filter_p2 = p2;}
      double get_latelight_filter_p2(){return latelight_filter_p2;}

      void set_baseline_safety_subtraction(double adjust){baseline_safety_subtraction = adjust;}
      double get_baseline_safety_subtraction(){return baseline_safety_subtraction;}

      void set_xq(double value) {xq = value;}
      double get_xq() {return xq;}

      void set_xq_diff(double value) {xq_diff = value;}
      double get_xq_diff() {return xq_diff;}

      void set_n_bins_end_wfm(int n){n_bins_end_wfm = n;}
      int get_n_bins_end_wfm(){return n_bins_end_wfm;}

      void set_beam_rebin_size(int n){beam_rebin_size = n;}
      int get_beam_rebin_size(){return beam_rebin_size;}

      void set_G_p0(double value) {G_p0 = value;}
      double get_G_p0() {return G_p0;}

      void set_G_p1(double value) {G_p1 = value;}
      double get_G_p1() {return G_p1;}

      void set_G_p2(double value) {G_p2 = value;}
      double get_G_p2() {return G_p2;}

      void set_Lasso_p0(double value) {Lasso_p0 = value;}
      double get_Lasso_p0() {return Lasso_p0;}

      void set_Lasso_p1(int value) {Lasso_p1 = value;}
      int get_Lasso_p1() {return Lasso_p1;}

      void set_Lasso_p2(double value) {Lasso_p2 = value;}
      double get_Lasso_p2() {return Lasso_p2;}

      void set_totPE_v_thresh(double value) {totPE_v_thresh = value;}
      double get_totPE_v_thresh() {return totPE_v_thresh;}

      void set_mult_v_thresh(double value) {mult_v_thresh = value;}
      double get_mult_v_thresh() {return mult_v_thresh;}

      void set_l1_mult_v_thresh(double value) {l1_mult_v_thresh = value;}
      double get_l1_mult_v_thresh() {return l1_mult_v_thresh;}

      void set_ophit_group_t_diff_max(double value) {ophit_group_t_diff_max = value;}
      double get_ophit_group_t_diff_max() {return ophit_group_t_diff_max;}

      void set_bflash_pe_thresh(double value) {bflash_pe_thresh = value;}
      double get_bflash_pe_thresh() {return bflash_pe_thresh;}

      void set_bflash_mult_thresh(double value) {bflash_mult_thresh = value;}
      double get_bflash_mult_thresh() {return bflash_mult_thresh;}

      void set_bflash_bin_diff_p0(int value) {bflash_bin_diff_p0 = value;}
      int get_bflash_bin_diff_p0() {return bflash_bin_diff_p0;}

      void set_bflash_bin_diff_p1(int value) {bflash_bin_diff_p1 = value;}
      int get_bflash_bin_diff_p1() {return bflash_bin_diff_p1;}

      void set_bflash_bin_diff_p2(int value) {bflash_bin_diff_p2 = value;}
      int get_bflash_bin_diff_p2() {return bflash_bin_diff_p2;}

      void set_KS_test_thresh(double value) {KS_test_thresh = value;}
      double get_KS_test_thresh() {return KS_test_thresh;}

      void set_bflash_bin_start_cushion(int value) {bflash_bin_start_cushion = value;}
      int get_bflash_bin_start_cushion() {return bflash_bin_start_cushion;}

      void set_flash_filter_time_thresh(double value) {flash_filter_time_thresh = value;}
      double get_flash_filter_time_thresh() {return flash_filter_time_thresh;}

      void set_flash_filter_pe_thresh(double value) {flash_filter_pe_thresh = value;}
      double get_flash_filter_pe_thresh() {return flash_filter_pe_thresh;}

      void set_rc_tau_badch(double value) {rc_tau_badch = value;}
      double get_rc_tau_badch() {return rc_tau_badch;}

      void set_rc_tau_goodch(double value) {rc_tau_goodch = value;}
      double get_rc_tau_goodch() {return rc_tau_goodch;}

      void set_spe_p0(double value) {spe_p0 = value;}
      double get_spe_p0() {return spe_p0;}

      void set_spe_p1(double value) {spe_p1 = value;}
      double get_spe_p1() {return spe_p1;}

      void set_COphit_integral_thresh(double value) {COphit_integral_thresh = value;}
      double get_COphit_integral_thresh() {return COphit_integral_thresh;}

      void set_COphit_baseline_diff_thresh(double value) {COphit_baseline_diff_thresh = value;}
      double get_COphit_baseline_diff_thresh() {return COphit_baseline_diff_thresh;}

      void set_pe_factor(double value) {pe_factor = value;}
      double get_pe_factor() {return pe_factor;}

      void set_Baseline_uncertainty(double value) {Baseline_uncertainty = value;}
      double get_Baseline_uncertainty() {return Baseline_uncertainty;}

      void set_Baseline_unc_bad_baseline(double value) {Baseline_unc_bad_baseline = value;}
      double get_Baseline_unc_bad_baseline() {return Baseline_unc_bad_baseline;}

      void set_cal_integral_p0(double value) {cal_integral_p0 = value;}
      double get_cal_integral_p0() {return cal_integral_p0;}

      void set_cal_integral_p1(double value) {cal_integral_p1 = value;}
      double get_cal_integral_p1() {return cal_integral_p1;}

      void set_cal_integral_p2(double value) {cal_integral_p2 = value;}
      double get_cal_integral_p2() {return cal_integral_p2;}

      void set_cal_integral_p3(double value) {cal_integral_p3 = value;}
      double get_cal_integral_p3() {return cal_integral_p3;}

      void set_cal_integral_p4(double value) {cal_integral_p4 = value;}
      double get_cal_integral_p4() {return cal_integral_p4;}

      void set_cal_integral_p5(double value) {cal_integral_p5 = value;}
      double get_cal_integral_p5() {return cal_integral_p5;}

      void set_PE_err(double value) {PE_err = value;}
      double get_PE_err() {return PE_err;}

      void set_PE_subtract(double value) {PE_subtract = value;}
      double get_PE_subtract() {return PE_subtract;}

      void set_flash_low_time_cushion(int value) {flash_low_time_cushion = value;}
      int get_flash_low_time_cushion() {return flash_low_time_cushion;}

      void set_flash_high_time_cushion(int value) {flash_high_time_cushion = value;}
      int get_flash_high_time_cushion() {return flash_high_time_cushion;}


    protected:
      int num_channels; //lots
      int num_types; //lots
      std::vector<int> nbins_by_type; //lots?
      double baseline_default; //scale_lowgains in satmerge
      double baseline_difference_max; //scale_lowgains in satmerge, also deconv Remove_Baseline_Secondary
      int cosmic_tick_window; //Cosmic merger in satmerge
      float tick_width_us;  //cosmic merger in satmerge, Deconvolve_One_Wfm in deconv (1/64) for bin_width and 64 for max_freq_MHz, G(i,k) Hitfinder Beam 15.625/1000, also in Opflash.h and .cxx
      double low_bound_baseline_search; //findBaselineLg in SatMerger
      double high_bound_baseline_search; //findBaselineLg in SatMerger
      int nbins_baseline_search; //find findBaselineLg satmerger
      int nbins_saturation_threshold; //satmerger beam and cosmic mergers
      std::vector<float> scaling_by_channel; // findScaling in satmerger
      double high_freq_p0;  //deconv HighFreqFilter
      double high_freq_p1;  //deconv HighFreqFilter
      double latelight_filter_p0;  //deconv LateLightFilter
      double latelight_filter_p1;  //deconv LateLightFilter
      double latelight_filter_p2;  //deconv latelight_filter
      double baseline_safety_subtraction; // deconv Remove_Baseline_Secondary
      double xq ; //deconv cal_mean_rms
      double xq_diff ; //deconv cal_mean_rms
      int n_bins_end_wfm ; //deconv deconv one wfm end loop 1500-4
      int beam_rebin_size ; //HitFinder_beam (sort of in opflash.h shows up as 6 where 1500/250 = 6)
      double l1_content_thresh ; // Hitfinder beam 0.3
      double frac_G_t2_first ; //Hitfinder beam G
      double frac_G_sametime ; //Hitfinder beam G
      double G_p0 ; //Hitfinder beam G
      double G_p1 ; //Hitfinder beam G
      double G_p2 ; //Hitfinder beam G
      double Lasso_p0 ; //Hitfinder beam
      int    Lasso_p1 ; //Hitfinder beam
      double Lasso_p2 ; //Hitfinder beam
      double totPE_v_thresh ; //Hitfinder beam
      double mult_v_thresh ; //Hitfinder beam
      double l1_mult_v_thresh ; //Hitfinder beam
      double ophit_group_t_diff_max ; // Hitfinder cosmic twice
      double bflash_pe_thresh ; //Flashes beams
      double bflash_mult_thresh ; //Flashes beams
      int bflash_bin_diff_p0 ; //Flashes beams 78 is in there 2x
      int bflash_bin_diff_p1 ; //Flashes beams
      int bflash_bin_diff_p2 ; //Flashes beams
      double KS_test_thresh ; //Flashes beams
      int bflash_bin_start_cushion ; //Flashes beam
      double flash_filter_time_thresh ; //Flashfiltering
      double flash_filter_pe_thresh ; //Flashfiltering
      double rc_tau_badch ; //UB_rc
      double rc_tau_goodch ; //UB_rc
      double spe_p0; //UB_spe
      double spe_p1; //UB_spe
      double COphit_integral_thresh ; //COPHIT
      double COphit_baseline_diff_thresh ;//COPHIT
      double pe_factor ; //COPHIT
      double Baseline_uncertainty ; //Percent uncertainty COPHIT
      double Baseline_unc_bad_baseline ; //Percent Unc if baseline bad COPHIT
      double cal_integral_p0 ;  //COPHIT
      double cal_integral_p1 ;  //COPHIT
      double cal_integral_p2 ;  //COPHIT
      double cal_integral_p3 ;  //COPHIT
      double cal_integral_p4 ;  //COPHIT
      double cal_integral_p5 ;  //COPHIT
      double PE_err ; //Opflash
      double PE_subtract ; //Opflash
      int flash_low_time_cushion ; //Opflash
      int flash_high_time_cushion ; //Opflash





      //Params NEEDING set:
      std::vector<float> gain;
      std::vector<float> gainerror;






  };

  }

  #endif
