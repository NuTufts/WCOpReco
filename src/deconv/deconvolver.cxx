#include "deconvolver.h"

namespace wcopreco {

void wcopreco::deconvolver::deconv_test()

  {
    std::cout << "Within Tester Function!" <<std::endl;

    UB_spe spe;
    std::vector<float> vec(1,0);
    std::vector<float> vec2(1,0);
    vec = spe.Get_wfm(5, 10.0);
    vec2 = spe.Get_pow_spec(-5, 13.333);

    
  }

}
