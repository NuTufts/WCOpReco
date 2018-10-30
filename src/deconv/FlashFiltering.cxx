#include "FlashFiltering.h"

namespace wcopreco {

  wcopreco::FlashFiltering::FlashFiltering(OpflashSelection &c_flashes, OpflashSelection &b_flashes){
    //code to perform flash matching
    //inputs come from Flashes_cosmic and Flashes_beam
      cosmic_flashes = c_flashes;
      beam_flashes = b_flashes;
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
          }
          else{
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
              //std::cout << bflash->get_time() << " :beam_flashes time, " << prev_cflash->get_time() << " :c" << bflash->get_total_PE() << " " << prev_cflash->get_total_PE() << std::endl;
        }
        flashes.push_back(bflash);
      }

      sort_flashes();
      update_pmt_map();

  }

  void FlashFiltering::sort_flashes(){

    for (auto it= cosmic_flashes.begin(); it!= cosmic_flashes.end(); it++){
      cosmic_set.insert(*it);
    }
    cosmic_flashes.clear();
    std::copy(cosmic_set.begin(), cosmic_set.end(), std::back_inserter(cosmic_flashes));

    for (auto it=beam_flashes.begin(); it!=beam_flashes.end(); it++){
      beam_set.insert(*it);
    }
    beam_flashes.clear();
    std::copy(beam_set.begin(), beam_set.end(), std::back_inserter(beam_flashes));

    for (auto it=flashes.begin(); it!=flashes.end(); it++){
      all_set.insert(*it);
    }
    flashes.clear();
    std::copy(all_set.begin(), all_set.end(), std::back_inserter(flashes));
  }


  void wcopreco::FlashFiltering::update_pmt_map(){
    // std::cout << "Update map!" << std::endl;
    for (auto it=flashes.begin(); it!=flashes.end(); it++){
      Opflash *flash = *it;
      flash->swap_channels(); // hard coded for now ...
    }
  }
}
