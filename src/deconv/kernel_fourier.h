#ifndef KERNEL_FOURIER_H
#define KERNEL_FOURIER_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

namespace wcopreco {

  class kernel_fourier {
  public:
    kernel_fourier(std::string word, bool flag);
    virtual ~kernel_fourier() {};

    virtual std::vector<float> Get_wfm(int nbins, float tick_width_ns) = 0;
    virtual std::vector<float> Get_pow_spec(int nbins, float tick_width_ns) = 0;
    std::string name;
    // 0 = divide 1 = multiply
    bool mult_div;

  protected:



  };

}

#endif
