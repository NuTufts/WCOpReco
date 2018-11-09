#include "UBAlgo.h"

namespace wcopreco{

  wcopreco::UBAlgo::UBAlgo(const Config_Params &cfg_all)
  : _cfg(cfg_all)
  {};

  void UBAlgo::Run(UBEventWaveform * _UB_Ev_wfm,
                  std::vector<float> * op_gain,
                  std::vector<float> * op_gainerror,
                  std::vector<wcopreco::kernel_fourier_container> * kernel_container_v){
      //create the merger and then get a Merged UBEventWaveform UB_Ev_Merged
      wcopreco::Saturation_Merger merger(*_UB_Ev_wfm , _cfg._get_cfg_saturation_merger());
      merged_beam = merger.get_merged_beam(); //This is inside UB_Ev_Merged
      merged_cosmic = merger.get_merged_cosmic(); //This is inside UB_Ev_Merged
      wcopreco::UBEventWaveform UB_Ev_Merged = merger.get_merged_UB_Ev();

      //do beam hitfinding
      wcopreco::HitFinder_beam hits_found_beam(merged_beam, *kernel_container_v, _cfg._get_cfg_hitfinder_beam(), _cfg._get_cfg_deconvolver());

      // do beam flash finding
      std::vector<double> totPE_v = hits_found_beam.get_totPE_v();
      std::vector<double> mult_v =hits_found_beam.get_mult_v();
      std::vector<double> l1_totPE_v =hits_found_beam.get_l1_totPE_v();
      std::vector<double> l1_mult_v = hits_found_beam.get_l1_mult_v();
      std::vector< std::vector<double> > decon_vv = hits_found_beam.get_decon_vv();
      double beam_start_time =merged_beam.at(0).get_time_from_trigger();


      wcopreco::Flashes_beam flashfinder_beam( &totPE_v,
                                              &mult_v,
                                              &l1_totPE_v,
                                              &l1_mult_v,
                                              decon_vv,
                                              beam_start_time,
                                              _cfg._get_cfg_flashesbeam(),
                                              _cfg._get_cfg_opflash());

      flashes_beam = flashfinder_beam.get_beam_flashes();
      // std::cout << "\n\n" << flashes_beam.size() << " Beam Flashes in Event\n";

      // //Create the Hitfinder for COSMICS
      wcopreco::HitFinder_cosmic hits_found(&merged_cosmic,
                                            op_gain,
                                            op_gainerror,
                                            _cfg._get_cfg_hitfinder_cosmic(),
                                            _cfg._get_cfg_cophit());

      //flashes for cosmics
      std::vector<COphitSelection>  hits = hits_found.get_ophits_group();
      hits_found.clear_ophits();
      wcopreco::Flashes_cosmic flashfinder_cosmic(&hits, _cfg._get_cfg_opflash());
      flashes_cosmic = flashfinder_cosmic.get_cosmic_flashes();
      // std::cout << flashes_cosmic.size() << " Cosmic Flashes in Event\n";

      // std::cout << flashes.size() << " flashes were found in the cosmic selection\n";

      //flash filtering
      wcopreco::FlashFiltering flashesfiltered(&flashes_cosmic, &flashes_beam, _cfg._get_cfg_flashfiltering());
      flashes = flashesfiltered.get_flashes();
      // std::cout << flashes.size() << " Matched Flashes in Event\n\n";

      // for (int i =0 ; i<flashes.size(); i++) {
      //     if (flashes.at(i)->get_type() == 2) std::cout << flashes.at(i)->get_total_PE() << "\n";
      // }

  }


   wcopreco::UBAlgo::~UBAlgo(){
    for (auto it = flashes_beam.begin(); it!=flashes_beam.end(); it++){
        delete (*it);
      }
      for (auto it=flashes_cosmic.begin(); it!= flashes_cosmic.end(); it++){
        delete (*it);
      }
      flashes_beam.clear();
      flashes_cosmic.clear();
      flashes.clear();
  }

   void wcopreco::UBAlgo::clear_flashes(){
   for (auto it = flashes_beam.begin(); it!=flashes_beam.end(); it++){
       delete (*it);
     }
     for (auto it=flashes_cosmic.begin(); it!= flashes_cosmic.end(); it++){
       delete (*it);
     }
     flashes_beam.clear();
     flashes_cosmic.clear();
     flashes.clear();
 }


}
