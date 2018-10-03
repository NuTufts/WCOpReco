#ifndef SPE_CONTAINER_H
#define SPE_CONTAINER_H



#include "spe_shape.h"
#include <vector>

namespace wcopreco {

  class spe_container : public std::vector<spe_shape> {

  public:
    spe_container();
    virtual ~spe_container() {};


  protected:

  };

}

#endif
