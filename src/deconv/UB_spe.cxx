#include "UB_spe.h"


namespace wcopreco {

wcopreco::UB_spe::UB_spe(std::string nm, bool mult_flag)
: kernel_fourier (nm,mult_flag)
 {

 }

std::vector<float> wcopreco::UB_spe::Get_wfm(int nbins, float tick_width_ns)

  {
    std::vector<float> wfm(nbins,0);
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



std::vector<float> wcopreco::UB_spe::Get_pow_spec(int nbins, float tick_width_ns)

  {
    std::vector<float> vec(1,0);
    std::cout << nbins << " bins POWER  " << tick_width_ns << "  tick width POWER" << std::endl;
    return vec;
  }

}
