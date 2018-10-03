#include "deconvolver.h"

namespace wcopreco {

void wcopreco::deconvolver::deconv_test()

  {
    std::cout << "Within Tester Function!" <<std::endl;

    // UB_spe spe;
    std::vector<float> vec(1,0);
    std::vector<float> vec2(1,0);
    std::string word = "Josh" ;

    UB_spe spe(word, true);

    // spe.gain = 1.0;
    // vec = spe.Get_wfm(1500, (1/(64e6) ) );
    // vec2 = spe.Get_pow_spec(1500, (1/(64e6) ) );


  }

}
