#include "UB_noiserem.h"
#include "/home/kmason/PmtReco/WCOpReco/src/data/OpWaveform.h"

namespace wcopreco {

  std::vector<float> UB_noiserem::Get_wfm(int nbins, float tick_width_ns)
  {
    std::vector<float> vec(1,0);
    std::cout << nbins << " bins WFM" << tick_width_ns << "  tick width WFM" << std::endl;
    return vec;
  }

  float Get_baseline(OpWaveform wfm)
  {
    //baseline = 1st bin content for now, will want to add a check to this like in COphit
    float baseline = wfm[0];
    return baseline;
  }

  void Remove_baseline(OpWaveform wfm, float baseline)
  {
    int numentries = wfm.size();
    for (int i = 0; i < numentries; i++){
      wfm[i] = wfm[i] - baseline;
    }
  }

}
