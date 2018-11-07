#include "Config_Params.h"

namespace wcopreco {


  void _set_num_types_and_bins_per__type(int n, std::vector<int> bins_per_type) {
      if (n == bins_per_type.size()) {
        _num_types = n;
        _nbins_by_type = bins_per_type;
      }
      else{
        std::cout << "Number of types not equal to size of bins_per_type vector\n";
      }

  }

  void _set_scaling_by_channel(std::vector<float> scalings_v) {
    _scaling_by_channel = scalings_v;
    if (scalings_v.size() != _num_channels) {
      std::cout << "Careful, size of scaling vector is not the same as the number of channels currently set.\n";
      std::cout << _num_channels << " Is the number of channels, " << scalings_v.size() << "  Is the size of scalings vector set\n";
    }
  }


}
