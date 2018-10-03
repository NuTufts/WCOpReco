#include "kernel_fourier.h"
#include <vector>

using namespace wcopreco;

 wcopreco::kernel_fourier::kernel_fourier(std::string nm, bool mult_flag)
  {
    std::cout << name <<" Name before set." <<std::endl <<std::endl;
    name = nm;
    std::cout << name <<" Name after  set." << std::endl <<std::endl;

    std::cout << mult_div <<" flag before set." <<std::endl <<std::endl;
    mult_div = mult_flag;
    std::cout << mult_div <<" flag after  set." << std::endl <<std::endl;



  }
