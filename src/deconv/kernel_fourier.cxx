#include "kernel_fourier.h"
#include <vector>

using namespace wcopreco;

 wcopreco::kernel_fourier::kernel_fourier(std::string nm, bool mult_flag)
  {
    name = nm;
    std::cout << name <<" Name is set to:   " <<  name << std::endl <<std::endl;

    mult_div = mult_flag;
    std::string optioned;
    if (mult_div) {optioned = "|| Multiply || this kernel.";}
    else if (not mult_div) {optioned = "|| Divide || this kernel.";}
    else {optioned = " Bool not true or false...";}
    std::cout << "Flag is set to:  " << mult_div  << "    This means "<< optioned << std::endl <<std::endl;



  }
