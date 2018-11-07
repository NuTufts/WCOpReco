#include "COphit.h"

using namespace wcopreco;

wcopreco::COphit::COphit(int ch_no, OpWaveform *wfm, double time, double gain, double gain_err)
  : channel_no(ch_no)
  , time(time)
  , gain(gain)
  , gain_err(gain_err)
{
  // calculate baseline
  baseline = wfm->at(0);

  // calculate peak and integral
  peak = 0;
  integral = 0;

  for (int i=0; i!=40; i++){
    double content = wfm->at(i) - baseline;
    if (content > peak){
      peak  = content;
    }
    integral += content;
  }

  // calculate PE and its error ...
  good_baseline = false;
  if (integral > _COphit_integral_thresh || fabs(baseline-_baseline_default)<_COphit_baseline_diff_thresh) good_baseline = true;

  // special treatment of FEM channel 28 ...
  if (channel_no == 28) integral = cal_integral(peak);
  if (!good_baseline) integral = cal_integral(peak);

  if (good_baseline){
    PE = integral / gain * _pe_factor; // taking into account factor of 2 for 0.6 us window ...
    // take care of PE ...
    if (PE < 0) PE = 0;

    PE_err = sqrt(pow(PE * gain_err/gain ,2) // gain uncertainties
		  + 2 * PE // statistical term ...
		  + pow(40/sqrt(3.)/gain * 2,2)  // basline (1/sqrt(3.) ADC with 40 time tics ...)
		  + pow(PE*_Baseline_uncertainty,2) // 3% relative uncertainties (Baseline guess) ...
		  );

  }else{
    PE = integral/gain * _pe_factor;
    if (PE < 0) PE = 0;
    PE_err = _Baseline_unc_bad_baseline * PE; 
  }

}

wcopreco::COphit::~COphit(){
}

double wcopreco::COphit::cal_integral(double peak){
  double content;
  if (peak <=_cal_integral_p0){
    content = _cal_integral_p1 * peak + _cal_integral_p2 * pow(peak,2);
  }else{
    content = _cal_integral_p3  + _cal_integral_p4 * (peak - _cal_integral_p0) + _cal_integral_p5 * pow(peak-_cal_integral_p0,2);
  }
  return content;
}
