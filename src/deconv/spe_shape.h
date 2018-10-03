#ifndef SPE_SHAPE_H
#define SPE_SHAPE_H


#include <vector>

namespace wcopreco {

  class spe_shape : public std::vector<float> {
  public:
    spe_shape( );
    virtual ~spe_shape() {};

    // int get_ChannelNum() {return ChannelNum;};
    // double get_time_from_trigger() {return time_from_trigger;};
    // int get_type() {return type;};

  protected:
    // int ChannelNum;
    // double time_from_trigger;
    // int type;
  };

}

#endif
