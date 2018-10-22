#include "HitFinder.h"

namespace wcopreco {

  wcopreco::HitFinder::HitFinder(OpWaveformCollection* merged_cosmic, std::vector<float> *op_gain, std::vector<float> *op_gainerror){
    //Module for hit finding
    //input should be the output of the saturation merger - but I'm not confident in this at all

    //Much of this code can be left the way it is in WC

/*
I copied a duplicate version of the starting code so that we can easily go
over stuff I've changed tomorrow or revert if I do something wrong
-Josh
*/


    //COphitSelection = vector of COphits


      //I'm confused about what  fop_femch is. It's made in dumpPmtVec of ToyLightReco.
      //but I'm confused about what's in it and how it relates to COphit

      /*
      fop_femch is a long vector of channels associated with the waveforms in
      fop_wfm, the first 0-31 are beam in the event 32+ is cosmic. Here we got
      through just the cosmic. We don't use fop_femch, we just have a bunch of
      merged cosmics, so we can go through those -J
      */


      std::cout << merged_cosmic->size() << "   Is the number of waveforms in merged_cosmic\n";
      for (int i=0; i!=merged_cosmic->size(); i++){
        // our code: COphit(int ch_no, OpWaveform *wfm, double time, double gain, double gain_err)
        // original WC: COphit *op_hit = new COphit(fop_femch->at(i), (TH1S*)fop_wf->At(i), fop_timestamp->at(i) - triggerTime, op_gain->at(fop_femch->at(i)), op_gainerror->at(fop_femch->at(i)));
        // My attempt:
        OpWaveform wfm_cosmic = merged_cosmic->at(i);
        int channel = wfm_cosmic.get_ChannelNum();
        double timestamp = wfm_cosmic.get_time_from_trigger();
        //not sure what gain and gain error should be
        COphit *op_hit = new COphit(channel, &wfm_cosmic, timestamp, op_gain->at(channel), op_gainerror->at(channel));


         op_hits.push_back(op_hit);

        if (op_hit->get_type()){ // what type  good baseline ???
      //get_type returns good baseline...for some reason
          bool flag_used = false;

          //first time through, make ophits_group
          if (ophits_group.size()==0){
          	COphitSelection ophits;
          	ophits.push_back(op_hit);
           //ophits_group = a vector of COphitSelections?
          	ophits_group.push_back(ophits);
          	flag_used = true;
          }

          else{
          	for (size_t j=0; j!=ophits_group.size();j++){
          	  for (size_t k=0; k!= ophits_group.at(j).size(); k++){
             //I think this is some sort of time ordering
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
          //if it doesn't fit between any of the other times, put it at the end
          if (!flag_used){
          	COphitSelection ophits;
          	ophits.push_back(op_hit);
          	ophits_group.push_back(ophits);
          }
        }

        //if not good baseline??
        else{
          left_ophits.push_back(op_hit);
        }
      }

      //put in the hits with bad baselines in time order
      for (size_t i=0;i!=left_ophits.size();i++){
        bool flag_used = false;
        for (size_t j=0; j!=ophits_group.size();j++){
          for (size_t k=0; k!= ophits_group.at(j).size(); k++){
          	if (fabs(left_ophits.at(i)->get_time() - ophits_group.at(j).at(k)->get_time())<0.1){ // time unit??? 0.1 us?
          	  ophits_group.at(j).push_back(left_ophits.at(i));
          	  flag_used = true;
          	  break;
          	}
          }
          if (flag_used)
      	     break;
        }
      }

      // should this chunk be with the flash code? either way we have to return something
      // (either cosmic_flashes or ophits_group)
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


      /* Begin Copy of code */


    // //COphitSelection = vector of COphits
    // std::vector<COphitSelection> ophits_group;
    // std::vector<COphitSelection> left_ophits;
    //
    //   //I'm confused about what  fop_femch is. It's made in dumpPmtVec of ToyLightReco.
    //   //but I'm confused about what's in it and how it relates to COphit

      // for (int i=32;i!=fop_femch->size();i++){
      //   // our code: COphit(int ch_no, OpWaveform *wfm, double time, double gain, double gain_err)
      //   // original WC: COphit *op_hit = new COphit(fop_femch->at(i), (TH1S*)fop_wf->At(i), fop_timestamp->at(i) - triggerTime, op_gain->at(fop_femch->at(i)), op_gainerror->at(fop_femch->at(i)));
      //   // My attempt:
      //   OpWaveform wfm_beam = merged_beam.at(i);
      //   int channel = wfm_beam.get_ch_no();
      //   double timestamp = wfm_beam.get_time_from_trigger();
      //   //not sure what gain and gain error should be
      //   COphit *op_hit = new COphit(channel, *wfm_beam, timestamp, op_gain->at(fop_femch->at(i)), op_gainerror->at(fop_femch->at(i)));
      //
      //
      //    op_hits.push_back(op_hit);
      //
      //   if (op_hit->get_type()){ // what type  good baseline ???
      // //get_type returns good baseline...for some reason
      //     bool flag_used = false;

      //     //first time through, make ophits_group
      //     if (ophits_group.size()==0){
      //     	COphitSelection ophits;
      //     	ophits.push_back(op_hit);
      //      //ophits_group = a vector of COphitSelections?
      //     	ophits_group.push_back(ophits);
      //     	flag_used = true;
      //     }

      //     else{
      //     	for (size_t j=0; j!=ophits_group.size();j++){
      //     	  for (size_t k=0; k!= ophits_group.at(j).size(); k++){
      //        //I think this is some sort of time ordering
      //     	    if (fabs(op_hit->get_time() - ophits_group.at(j).at(k)->get_time()) < 0.1 ){  // time unit??? 0.1 us?
      //     	      ophits_group.at(j).push_back(op_hit);
      //     	      flag_used = true;
      //     	      break;
      //     	    }
      //     	  }
      //     	  if (flag_used)
      //     	    break;
      //     	}
      //     }
      //     //if it doesn't fit between any of the other times, put it at the end
      //     if (!flag_used){
      //     	COphitSelection ophits;
      //     	ophits.push_back(op_hit);
      //     	ophits_group.push_back(ophits);
      //     }
      //   }
      //
      //   //if not good baseline??
      //   else{
      //     left_ophits.push_back(op_hit);
      //   }
      // }
      //
      // //put in the hits with bad baselines in time order
      // for (size_t i=0;i!=left_ophits.size();i++){
      //   bool flag_used = false;
      //   for (size_t j=0; j!=ophits_group.size();j++){
      //     for (size_t k=0; k!= ophits_group.at(j).size(); k++){
      //     	if (fabs(left_ophits.at(i)->get_time() - ophits_group.at(j).at(k)->get_time())<0.1){ // time unit??? 0.1 us?
      //     	  ophits_group.at(j).push_back(left_ophits.at(i));
      //     	  flag_used = true;
      //     	  break;
      //     	}
      //     }
      //     if (flag_used)
      // 	     break;
      //   }
      // }
      //
      // // should this chunk be with the flash code? either way we have to return something
      // // (either cosmic_flashes or ophits_group)

      // for (size_t j=0; j!=ophits_group.size();j++){
      //   Opflash *flash = new Opflash(ophits_group.at(j));
      //   if (flash->get_total_PE()!=0){
      //     cosmic_flashes.push_back(flash);
      //   }
      //   else{
      //     delete flash;
      //   }
      //   //    std::cout << ophits_group.at(j).size() << " " << flash->get_time() << std::endl;
      // }
      //
      // // std::cout << cosmic_flashes.size() << std::endl;
      //
      // // for (auto flash : cosmic_flashes){
      // //   std::cout << flash->get_time() << std::endl;
      // // }
      //
      //
      //
      // for (int i=0;i!=32;i++){
      //   TH1S *hsignal = (TH1S*)fop_wf->At(i);
      //   for (int j=0;j!=1500;j++){
      //     hraw[i]->SetBinContent(j+1,hsignal->GetBinContent(j+1)-2050);
      //   }
      //   gain[i] = op_gain->at(i);
      //   beam_dt[i] = fop_timestamp->at(i) - triggerTime;
      // }

  }

}
