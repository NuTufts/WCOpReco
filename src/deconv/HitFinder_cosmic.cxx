#include "HitFinder_cosmic.h"

namespace wcopreco {

  wcopreco::HitFinder_cosmic::HitFinder_cosmic(OpWaveformCollection* merged_cosmic, std::vector<float> *op_gain, std::vector<float> *op_gainerror){
    //Module for hit finding for cosmics
    //Much of this code can be left the way it is in WC

      std::cout << merged_cosmic->size() << "   Is the number of waveforms in merged_cosmic\n";
      for (int i=0; i!=merged_cosmic->size(); i++){
        OpWaveform wfm_cosmic = merged_cosmic->at(i);
        int channel = wfm_cosmic.get_ChannelNum();
        double timestamp = wfm_cosmic.get_time_from_trigger();
        COphit *op_hit = new COphit(channel, &wfm_cosmic, timestamp, op_gain->at(channel), op_gainerror->at(channel));

        op_hits.push_back(op_hit);

        if (op_hit->get_type()){
          //get_type returns flag for good baseline
          bool flag_used = false;

          //first time through, make ophits_group
          if (ophits_group.size()==0){
          	COphitSelection ophits;
          	ophits.push_back(op_hit);
          	ophits_group.push_back(ophits);
          	flag_used = true;
          }

          else{
          	for (size_t j=0; j!=ophits_group.size();j++){
          	  for (size_t k=0; k!= ophits_group.at(j).size(); k++){
          	    if (fabs(op_hit->get_time() - ophits_group.at(j).at(k)->get_time()) < 0.1 ){  // time unit??? 0.1 us?
          	      ophits_group.at(j).push_back(op_hit);
          	      flag_used = true;
          	      break;
          	    }
          	  }
          	  if (flag_used)
          	    break;
          	}
          }

          if (!flag_used){
          	COphitSelection ophits;
          	ophits.push_back(op_hit);
          	ophits_group.push_back(ophits);
          }
        }

        //if not good baseline
        else{
          left_ophits.push_back(op_hit);
        }
      }

      for (size_t i=0;i!=left_ophits.size();i++){
        bool flag_used = false;
        for (size_t j=0; j!=ophits_group.size();j++){
          for (size_t k=0; k!= ophits_group.at(j).size(); k++){
          	if (fabs(left_ophits.at(i)->get_time() - ophits_group.at(j).at(k)->get_time())<0.1){
          	  ophits_group.at(j).push_back(left_ophits.at(i));
          	  flag_used = true;
          	  break;
          	}
          }
          if (flag_used)
      	     break;
        }
      }

      //MOVE TO FLASHES_COSMIC CLASS
      int count =0;
      int count_d=0;
      for (size_t j=0; j!=ophits_group.size();j++){
        Opflash *flash = new Opflash(ophits_group.at(j));
        if (flash->get_total_PE()!=0){
          count++;
          std::cout << count << " Is now the count of the flashes\n";
          cosmic_flashes.push_back(flash);
        }
        else{
          delete flash;
          count_d++;
          std::cout << count_d << " Have been deleted\n";

        }
        //    std::cout << ophits_group.at(j).size() << " " << flash->get_time() << std::endl;
      }

      // std::cout << cosmic_flashes.size() << std::endl;

      // for (auto flash : cosmic_flashes){
      //   std::cout << flash->get_time() << std::endl;
      // }


      //I don't think the following is specific to hitfinding
      // Do we need this?
      /*
      for (int i=0;i!=32;i++){
        TH1S *hsignal = (TH1S*)fop_wf->At(i);
        for (int j=0;j!=1500;j++){
          hraw[i]->SetBinContent(j+1,hsignal->GetBinContent(j+1)-2050);
        }
        gain[i] = op_gain->at(i);
        beam_dt[i] = fop_timestamp->at(i) - triggerTime;
      }
      */

  }

}
