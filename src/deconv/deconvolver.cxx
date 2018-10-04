#include "deconvolver.h"

namespace wcopreco {

void wcopreco::deconvolver::deconv_test()

  {
    // std::cout << "Within Tester Function!" <<std::endl;

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
    std::cout << *std::max_element(vec.begin(),vec.end()) << "    Is MAX element." << std::endl;

    std::vector<double> mag;
    std::vector<double> phase;

    spe.Get_pow_spec(nbins,bin_width,&mag,&phase);
    std::cout << mag.size() << "    Is size of vector." << std::endl;
    std::cout << mag.at(1) << "    Is first element." << std::endl;
    std::cout << mag.at(500) << "    Is 500 element." << std::endl;
    std::cout << *std::max_element(mag.begin(),mag.end()) << "    Is MAX element." << std::endl;

    //testing UB_rc
    UB_rc rc(word,true);

    std::vector<double> vec_rc = rc.Get_wfm(nbins,bin_width);
    std::cout << vec_rc.size() << "    Is size of vector(rc)." << std::endl;
    std::cout << vec_rc.at(1) << "    Is first element(rc)." << std::endl;
    std::cout << vec_rc.at(500) << "    Is 500 element(rc)." << std::endl;
    std::cout << *std::max_element(vec_rc.begin(),vec_rc.end()) << "    Is MAX element(rc)." << std::endl;

    std::vector<double> mag_rc;
    std::vector<double> phase_rc;

    rc.Get_pow_spec(nbins,bin_width,&mag_rc,&phase_rc);
    std::cout << mag_rc.size() << "    Is size of vector(rc)." << std::endl;
    std::cout << mag_rc.at(1) << "    Is first element(rc)." << std::endl;
    std::cout << mag_rc.at(500) << "    Is 500 element(rc)." << std::endl;
    std::cout << *std::max_element(mag_rc.begin(),mag_rc.end()) << "    Is MAX element(rc)." << std::endl;

  }

}
