#include "UB_spe.h"


namespace wcopreco {

std::vector<float> wcopreco::UB_spe::Get_wfm(int nbins, float tick_width_ns)

  {
    std::vector<float> vec(1,0);
    std::cout << nbins << " bins WFM" << tick_width_ns << "  tick width WFM" << std::endl;
    return vec;
  }



std::vector<float> wcopreco::UB_spe::Get_pow_spec(int nbins, float tick_width_ns)

  {
    std::vector<float> vec(1,0);
    std::cout << nbins << " bins POWER" << tick_width_ns << "  tick width POWER" << std::endl;
    return vec;
  }

}
