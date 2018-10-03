#ifndef NOISE_REMOVER_h
#define NOISE_REMOVER_h

#include <vector>

namespace wcopreco{

  class noise_remover{
  public:
    noise_remover(int type, int ch, double timestamp );
    virtual ~noise_remover() {};

    int get_type() {return event_type;};
    int get_channel() {return ChannelNum;};
    double get_time() {return time_from_trigger;};

  protected:
    int event_type;
    double time_from_trigger;
    int ChannelNum;
  };


}

#endif
