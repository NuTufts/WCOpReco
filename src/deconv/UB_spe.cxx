#include "UB_spe.h"
#include "TH1D.h"
#include "TVirtualFFT.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TMath.h"



namespace wcopreco {

wcopreco::UB_spe::UB_spe(std::string nm, bool mult_flag)
: kernel_fourier (nm,mult_flag)
 {

 }

std::vector<double> wcopreco::UB_spe::Get_wfm(int nbins, float tick_width_ns)

  {
    std::vector<double> wfm(nbins,0);
    double value=0;
    int size = wfm.size();
    double parameter_1 = 8.18450e-01;
    double X;
    std::cout << size << std::endl;

    for (int i=0; i<size; i++) {
      X = (tick_width_ns)*(double(i)+0.5);
      //std::cout << X << std::endl;
      value = 1./19.6348*pow(X/parameter_1,4)*exp(-X/parameter_1)*gain;

      if (i%100 ==0) {std::cout << value << " Is value of the analytical function at X: " << X << std::endl;}
      // if (i%100 ==0) {std::cout << gain << " GAIN " << X << std::endl;}
      wfm[i] = value;
    }



    std::cout << nbins << " bins WFM  " << tick_width_ns << "  tick width WFM" << std::endl;
    std::cout << nbins*tick_width_ns << "ns Is time width of this waveform." <<std::endl << std::endl;;
    return wfm;
  }



std::vector<double> wcopreco::UB_spe::Get_pow_spec(int nbins, float tick_width_ns)

  {
    std::vector<double> power_spec_d(nbins,0);
    power_spec_d = Get_wfm(nbins,tick_width_ns);

    double *in = power_spec_d.data();
    TVirtualFFT *fftr2c = TVirtualFFT::FFT(1, &nbins, "R2C");
    fftr2c->SetPoints(in);
    fftr2c->Transform();
    double re;
    double im;
    for (int i=0; i<nbins; i++)
       {
         fftr2c->GetPointComplex(i, re, im);
       }




    std::cout << nbins << " bins POWER  " << tick_width_ns << "  tick width POWER" << std::endl;
    // std::vector<float> power_spec_f(power_spec_d.begin(), power_spec_d.end());
    return power_spec_d;
  }

}
