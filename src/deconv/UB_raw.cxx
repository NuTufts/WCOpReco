#include "UB_raw.h"

using namespace wcopreco;

 UB_raw::UB_raw(std::string nm, bool mult_flag)
 : kernel_fourier (nm,mult_flag)
  {

  }

std::vector<double> wcopreco::UB_raw::Get_wfm(int nbins, float tick_width_ns)
{
  std::vector<double> wfm(nbins,0);
  double content=0;
  int size = wfm.size();
  //std::cout << size << std::endl;

  float baseline = wfm[0];

  //remove baseline
  for (int i=0; i<size; i++) {
    wfm[i] = wfm[i] - baseline;

    //if (i ==100) std::cout << content << " Is value of the analytical function at X: " << X << std::endl;
    wfm[i] = content;
  }

  return wfm;

}
