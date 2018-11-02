#ifndef FLASHES_BEAM_H
#define FLASHES_BEAM_H

#include "WCOpReco/DataReader.h"
#include "WCOpReco/Opflash.h"
#include "HitFinder_beam.h"

namespace wcopreco{


  class Flashes_beam {
  public:
    Flashes_beam(std::vector<double> totPE_v, std::vector<double> mult_v, std::vector<double> l1_totPE_v, std::vector<double> l1_mult_v, std::vector< std::vector<double> > decon_vv, double beam_start_time);
    ~Flashes_beam() {};

    OpflashSelection get_beam_flashes(){return beam_flashes;};

  protected:
    double KS_maxdiff(int n, double *array1, double *array2);
    OpflashSelection beam_flashes;

  };

}

#endif
