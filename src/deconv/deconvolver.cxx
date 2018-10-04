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

    std::vector<double> vec_spe = spe.Get_wfm(nbins,bin_width);
    std::cout << vec_spe.size() << "    Is size of vector." << std::endl;
    std::cout << vec_spe.at(1) << "    Is first element." << std::endl;
    std::cout << vec_spe.at(500) << "    Is 500 element." << std::endl;
    std::cout << *std::max_element(vec_spe.begin(),vec_spe.end()) << "    Is MAX element." << std::endl;

    std::vector<double> mag_spe;
    std::vector<double> phase_spe;

    spe.Get_pow_spec(nbins,bin_width,&mag_spe,&phase_spe);
    std::cout << mag_spe.size() << "    Is size of vector." << std::endl;
    std::cout << mag_spe.at(1) << "    Is first element." << std::endl;
    std::cout << mag_spe.at(500) << "    Is 500 element." << std::endl;
    std::cout << *std::max_element(mag_spe.begin(),mag_spe.end()) << "    Is MAX element." << std::endl;

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

    //for (int i=0; i<nbins; i++) {
      //X = (tick_width_ns)*(double(i)+0.5);
      //std::cout << X << std::endl;

      //hm and hp are the FFT of the raw opWaveForm minus the baseline - should be another object?
      //double rho = hm->GetBinContent(i+1)/ mag_rc.at(i) / mag.at(i)  ;
      //double phi = hp->GetBinContent(i+1) - phase_rc.at(i) - hp_spe.at(i);
    //}

  }

}
