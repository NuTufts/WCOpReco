#include "FlashMatching.h"

namespace wcopreco {

  wcopreco::FlashMatching::FlashMatching(OpflashSelection &cosmic_flashes, OpflashSelection &beam_flashes){
    //code to perform flash matching
    //inputs come from Flashes_cosmic and Flashes_beam

      Opflash *prev_cflash = 0;

      for (size_t i=0; i!=cosmic_flashes.size();i++){
        Opflash *cflash = cosmic_flashes.at(i);
        //std::cout << cflash->get_time() << std::endl;
        bool save = true;
        for (size_t j=0; j!=beam_flashes.size();j++){
          Opflash *bflash = beam_flashes.at(j);
          if (cflash->get_time() >= bflash->get_low_time() && cflash->get_time() <= bflash->get_high_time()){
          	save = false;
          	break;
          }
        }
        if (save){
          flashes.push_back(cflash);
          if (prev_cflash==0 ){
    	if (cflash->get_time()<0)
    	  prev_cflash = cflash;
          }else{
    	if (cflash->get_time() < 0 && cflash->get_time() > prev_cflash->get_time())
    	  prev_cflash = cflash;
          }
        }
      }
      for (size_t j=0; j!=beam_flashes.size();j++){
        Opflash *bflash = beam_flashes.at(j);
        if (prev_cflash!=0){

          //std::cout << prev_cflash->get_time() << std::endl;
          if (bflash->get_time() - prev_cflash->get_time() < 2.4 && // veto for 3 us
    	  bflash->get_total_PE() < 0.7 * prev_cflash->get_total_PE())
    	continue;
          // std::cout << bflash->get_time() << " " << prev_cflash->get_time() << " " << bflash->get_total_PE() << " " << prev_cflash->get_total_PE() << std::endl;
        }
        flashes.push_back(bflash);
      }

  }

}
