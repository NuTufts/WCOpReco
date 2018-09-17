#include "COphit.h"

using namespace WireCell;

WireCell::COphit::COphit(int ch_no, std::vector<double> *hist, double time, double gain, double gain_err) //TH1S
  : channel_no(ch_no)
  , time(time)
  , gain(gain)
  , gain_err(gain_err)
{
  // calculate baseline
  baseline = hist->at(1);

  // calculate peak and integral
  peak = 0;
  integral = 0;
  for (int i=0; i!=40; i++){
    double content = hist->at(i+1) - baseline;
    if (content > peak){
      peak  = content;
    }
    integral += content;
  }

  // calculate PE and its error ...
  good_baseline = false;
  if (integral > 20e3 || fabs(baseline-2050)<50) good_baseline = true;

  // special treatment of FEM channel 28 ...
  if (channel_no == 28) integral = cal_integral(peak);
  if (!good_baseline) integral = cal_integral(peak);

  if (good_baseline){
    PE = integral / gain * 2; // taking into account factor of 2 for 0.6 us window ...
    // take care of PE ...
    if (PE < 0) PE = 0;

    PE_err = sqrt(pow(PE * gain_err/gain ,2) // gain uncertainties
		  + 2 * PE // statistical term ...
		  + pow(40/sqrt(3.)/gain * 2,2)  // basline (1/sqrt(3.) ADC with 40 time tics ...)
		  + pow(PE*0.03,2) // 3% relative uncertainties (Baseline guess) ...
		  );

    // if (PE < 1000){
    //   PE_err = sqrt(pow(PE * gain_err/gain ,2) + pow(PE*0.02,2)); // standard error below threshold would be 4.6 PE ... 8/sqrt(3)
    // }else if (PE < 2000){
    //   PE_err = sqrt(pow(PE * gain_err/gain ,2) + pow(PE*0.06,2)); // standard error below threshold would be 4.6 PE ... 8/sqrt(3)
    // }else{
    //   PE_err = sqrt(pow(PE * gain_err/gain ,2) + pow(PE*0.18,2)); // standard error below threshold would be 4.6 PE ... 8/sqrt(3)
    // }
    // if (PE < 12){ // too small ...
    //   // some issues ...
    //   PE_err = sqrt(pow(PE_err,2) + pow(4.6,2));
    //   good_baseline = false;
    // }

  }else{
    PE = integral/gain * 2;
    if (PE < 0) PE = 0;
    PE_err = 2 * PE; // give 200% uncertainties ...
  }

}

WireCell::COphit::~COphit(){
}

double WireCell::COphit::cal_integral(double peak){
  double content;
  if (peak <=4000){
    content = 1.06241e+01 * peak + 2.01214e-04 * pow(peak,2);
  }else{
    content = 4.5715824e4 + 8.62296e+00 * (peak - 4000) + 6.76898e-04 * pow(peak-4000,2);
  }
  return content;
}
