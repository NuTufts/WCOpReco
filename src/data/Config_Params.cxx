#include "Config_Params.h"

namespace wcopreco {

  //Constructor sets default parameters
  Config_Params::Config_Params(){
    num_channels = 32;
    num_types = 6;
    nbins_by_type = {1500, 1500, 40, 40, 1500, 40};
    sat_threshold = 4080;
    baseline_default =2050;
    baseline_difference_max = 8;
    cosmic_tick_window = 20;
    tick_width_us = .015625; //Microseconds
    low_bound_baseline_search = 1500;
    high_bound_baseline_search = 2500;
    nbins_baseline_search = 20;
    nbins_saturation_threshold = 3;
    scaling_by_channel = {10.13, 10.20, 10.13, 10.05, 9.96, 9.95, 10.04, 9.58, 9.42, 9.81, 9.25, 9.61, 9.56, 9.35, 9.99, 9.66, 10.26, 9.82, 10.32, 10.08, 9.77, 9.64, 10.14, 9.74, 9.76, 10.10, 10.48, 9.81, 9.99, 9.79, 9.93, 10.01};
    high_freq_p0 = 0.45;
    high_freq_p1 = 3.07;
    latelight_filter_p0 = 0.05;
    latelight_filter_p1 = 0.45;
    latelight_filter_p2 = 3.07;
    baseline_safety_subtraction = 100;
    xq = 0.5 ;
    xq_diff = 0.34 ;
    beam_rebin_size = 250 ;
    frac_G_t2_first = 0.75 ;
    frac_G_sametime = 0.25 ;
    G_p0 = 6.0 ;
    G_p1 = 3.0 ;
    G_p2 = 1.5 ;
    Lasso_p0 = 5.0 ;
    Lasso_p1 = 100000 ;
    Lasso_p2 = 0.05 ;
    totPE_v_thresh = 0.2 ;
    mult_v_thresh = 1.5 ;
    l1_mult_v_thresh = 1.0 ;
    ophit_group_t_diff_max = 0.1 ;
    bflash_pe_thresh = 6.0 ;
    bflash_mult_thresh = 3.0 ;
    bflash_bin_diff_p0 = 78 ;
    bflash_bin_diff_p1 = 4 ;
    bflash_bin_diff_p2 = 15 ;
    KS_test_thresh = 0.1 ;
    bflash_bin_start_cushion = 2 ;
    flash_filter_time_thresh = 2.4 ;
    flash_filter_pe_thresh = 0.7 ;
    rc_tau_badch = 28.6 ;
    rc_tau_goodch = 800.0 ;
    spe_p0 = 19.6348 ;
    spe_p1 = 8.18450e-01 ;
    COphit_integral_thresh = 20e3 ;
    COphit_baseline_diff_thresh = 50 ;
    pe_factor = 2.0;
    Baseline_uncertainty = 0.03 ;
    Baseline_unc_bad_baseline = 2.0 ;
    cal_integral_p0 = 4000;
    cal_integral_p1 = 1.06241e+01;
    cal_integral_p2 = 2.01214e-04;
    cal_integral_p3 = 4.5715824e4;
    cal_integral_p4 = 8.62296e+00;
    cal_integral_p5 = 6.76898e-04;
    PE_err_cosmic = 6.4;
    PE_subtract = 0.15; //250 kHz at 6 us
    flash_low_time_cushion = -3;
    flash_high_time_cushion = +37;
    PE_err_beam = 0.2;
    PE_content_thresh = 0.2;
    mult_content_thresh = 1.5;
    mult_required = 3;
    PE_noise = 1.875; // 7.5 us * random noise
    PE_err_statist_beam = 1.875;
    PE_err_unc_perc_beam = 0.02;
    do_swap_channels = true ;
    addl1_pe_thres = 10.0 ;
    addl1_mult_thresh = 3.0 ;




    std::cout << "\n\nConfiguration File Constructed, Have a Nice Day\n\n";
  }


  void wcopreco::Config_Params::set_num_types_and_bins_per__type(int n, std::vector<int> bins_per_type) {
      if (n == bins_per_type.size()) {
        num_types = n;
        nbins_by_type = bins_per_type;
      }
      else{
        std::cout << "Number of types not equal to size of bins_per_type vector\n";
      }

  }

  void wcopreco::Config_Params::set_scaling_by_channel(std::vector<float> scalings_v) {
    scaling_by_channel = scalings_v;
    if (scalings_v.size() != num_channels) {
      std::cout << "Careful, size of scaling vector is not the same as the number of channels currently set.\n";
      std::cout << num_channels << " Is the number of channels, " << scalings_v.size() << "  Is the size of scalings vector set\n";
    }

  }

}
