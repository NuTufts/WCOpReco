#ifndef NOISE_REMOVER_h
#define NOISE_REMOVER_h

#include <vector>

namespace wcopreco{

  class noise_remover{
  public:
    noise_remover();
    virtual ~noise_remover() {};

    virtual std::vector<float> Get_wfm(int nbins, float tick_width_ns) = 0;

  protected:

  };

}

#endif
