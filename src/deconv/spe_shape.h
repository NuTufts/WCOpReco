#ifndef SPE_SHAPE_H
#define SPE_SHAPE_H

#include <vector>

namespace wcopreco {

  class spe_shape {
  public:
     spe_shape() {};
    virtual ~spe_shape() {};

    virtual std::vector<float> Get_wfm(int nbins, float tick_width_ns) = 0;
    virtual std::vector<float> Get_pow_spec(int nbins, float tick_width_ns) = 0;


  protected:



  };

}

#endif
