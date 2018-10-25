#include "Flashes_cosmic.h"

namespace wcopreco {

  wcopreco::Flashes_cosmic::Flashes_cosmic(std::vector<COphitSelection> ophits_group){
    //Module for flash finding for cosmics
    //Much of this code can be left the way it is in WC

    //MOVE TO FLASHES_COSMIC CLASS
    int count =0;
    int count_d=0;
    for (size_t j=0; j!=ophits_group.size();j++){
      Opflash *flash = new Opflash(ophits_group.at(j));
      if (flash->get_total_PE()!=0){
        count++;
        // std::cout << count << " Is now the count of the flashes\n";
        cosmic_flashes.push_back(flash);
      }
      else{
        delete flash;
        count_d++;
        // std::cout << count_d << " Have been deleted\n";

      }
      //    std::cout << ophits_group.at(j).size() << " " << flash->get_time() << std::endl;
    }

      // std::cout << cosmic_flashes.size() << std::endl;

      // for (auto flash : cosmic_flashes){
      //   std::cout << flash->get_time() << std::endl;
      // }
  }

}
