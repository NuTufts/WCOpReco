#ifndef CONFIG_HITFINDER_BEAM_H
#define CONFIG_HITFINDER_BEAM_H

namespace wcopreco {
  class Config_Hitfinder_Beam {
  public:
    Config_Hitfinder_Beam();
    ~Config_Hitfinder_Beam() {};
     int     _nbins_beam; //Original number of bins in a beam waveform
     int     _rebin_frac; //Fraction to rebin beam wfms into. By default 1500bin /6frac = 250 bin final waveform size
     double  _l1_content_thresh; // Hitfinder beam 0.3
     double  _frac_G_t2_first; //Hitfinder beam G
     double  _frac_G_sametime; //Hitfinder beam G
     double  _G_p0; //Hitfinder beam G
     double  _G_p1; //Hitfinder beam G
     double  _G_p2 ; //Hitfinder beam G
     double  _Lasso_p0; //Hitfinder beam
     int     _Lasso_p1; //Hitfinder beam
     double  _Lasso_p2; //Hitfinder beam
     double  _totPE_v_thresh; //Hitfinder beam Also appears in Opflash
     double  _mult_v_thresh; //Hitfinder beam, threshold in PE to determine if add to mult
     double  _l1_mult_v_thresh; //Hitfinder beam


  protected:


  };

}
#endif
