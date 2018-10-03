#ifndef NOISE_CONTAINER_H
#define NOISE_CONTAINER_H

#include"noise_remover.h"
#include <vector>

namespace wcopreco{

  class noise_container: public std::vector<noise_remover>{

  public:
    noise_container();
    virtual ~noise_container() {};

  protected:

  };

}
#endif
