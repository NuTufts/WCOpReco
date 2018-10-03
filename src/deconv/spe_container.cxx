#include "spe_container.h"
#include <vector>

using namespace wcopreco ;

wcopreco::spe_container::spe_container()
 : std::vector<spe_shape> (0,spe_shape())
  {
  reserve(36);
  }
