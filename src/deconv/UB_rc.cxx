#include "UB_rc.h"

using namespace wcopreco;

 UB_rc::UB_rc(bool mult_flag)
 : kernel_fourier ("UB_RC",mult_flag)
  {

  }

std::vector<double> wcopreco::UB_rc::Get_wfm(int nbins, float tick_width_ns)
{
  std::vector<double> wfm(nbins,0);
  double content=0;
  int size = wfm.size();
  //std::cout << size << std::endl;

  //rc_tau = 800 for all channels except 28
  //rc_tau(28) = 28.6
  //will need to have a funtion for this later (set_parameters
  //changed 800 (tick number) to a time
  double rc_tau = 800;

  double X;
  for (int i=0; i<size; i++) {
    X = i;
    //X = (tick_width_ns)*(double(i)+0.5);
    //std::cout << X << std::endl;
    double content = -1./rc_tau * exp(-X/rc_tau);
    if (i==0) content += 1;
    //if (i%100 == 0) std::cout << content << " Is value of the analytical function at X: " << X << std::endl;
    wfm[i] = content;
  }

  return wfm;

}
