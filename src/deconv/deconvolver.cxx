#include "deconvolver.h"

namespace wcopreco {

void wcopreco::deconvolver::deconv_test()

  {
    std::cout << "Within Tester Function!" <<std::endl;

    // UB_spe spe;

    std::string word = "Josh" ;

    UB_spe spe(word, true);
    // spe.gain = 1;
    int nbins = 1500;
    float bin_width = (1.0/(64e6) );

    std::vector<double> vec = spe.Get_wfm(nbins,bin_width);
    std::cout << vec.size() << "    Is size of vector." << std::endl;
    std::cout << vec.at(1) << "    Is first element." << std::endl;
    std::cout << vec.at(500) << "    Is 500 element." << std::endl;

    std::vector<double> vec_transform = spe.Get_pow_spec(nbins,bin_width);
    std::cout << vec_transform.size() << "    Is size of vector." << std::endl;
    std::cout << vec_transform.at(1) << "    Is first element." << std::endl;
    std::cout << vec_transform.at(500) << "    Is 500 element." << std::endl;

  }

}
