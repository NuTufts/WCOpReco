#include "HitFinder_cosmic.h"

namespace wcopreco {

  wcopreco::HitFinder_cosmic::HitFinder_cosmic(OpWaveformCollection* merged_cosmic, std::vector<float> *op_gain, std::vector<float> *op_gainerror){
    //Module for hit finding for cosmics
    //Much of this code can be left the way it is in WC

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

  }

}
