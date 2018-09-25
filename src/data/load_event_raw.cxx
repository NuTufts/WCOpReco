// #include "load_event_raw.h"
// #include <Eigen/Dense>
// #include <iostream>
// #include <vector>
// using namespace Eigen;
//
// /*
// Need to break this up much more. It calls a bunch of other functions after filling hraw,
// they should probably be called in a seperate, main, function
//
// This is where the raw wave form is called in ToyLightReco
// In ToyLightReco()
// hraw = new TH1F*[32];
//
// for (int i=0;i!=32;i++){
//   hraw[i] = new TH1F(Form("hraw_%d",i),Form("hraw_%d",i),1500,0,1500);
// }
//
//
// ----Where this function is
//
//
// In ~ToyLightReco()
// for (int i=0;i!=32;i++){
//   delete hraw[i];
//   hraw[i] = nullptr;
// }
// delete hraw;
//
// In clear_flashes()
// for (size_t i=0;i!=32;i++){
//   hraw[i]->Reset();
// }
// */
//
// // Where the raw waveform is made and used
// void WireCell2dToy::ToyLightReco::load_event_raw(int eve_num){
//   //ROOT
//   T->GetEntry(eve_num);
//
//   //Two Problems here. Make pmt containers should maybe be its own code.
//   //Want to get out of wirecell namespace. Either copy and rename or write our own.
//   //Inputs are defined in ToyLightReco as TCloneArrays and root histograms
//
//   //All of WireCell2dToy::* are defined in ToyLightReco.h
//   //Want to make our own file containing these instead
//
//   WireCell2dToy::pmtMapSet beamHG = makePmtContainer(true, true, beam_hg_wf, beam_hg_opch, beam_hg_timestamp);
//
//   WireCell2dToy::pmtMapSet beamLG = makePmtContainer(false, true, beam_lg_wf, beam_lg_opch, beam_lg_timestamp);
//
//   WireCell2dToy::pmtMapSet cosmicHG = makePmtContainer(true, false, cosmic_hg_wf, cosmic_hg_opch, cosmic_hg_timestamp);
//
//   WireCell2dToy::pmtMapSet cosmicLG = makePmtContainer(false, false, cosmic_lg_wf, cosmic_lg_opch, cosmic_lg_timestamp);
//
//   //makeBeamPairs, makeCosmicPairs, mergeBeam, mergeCosmic are each functions in ToyLightReco
//   WireCell2dToy::pmtMapPair beamPair = makeBeamPairs(beamHG, beamLG);
//   WireCell2dToy::pmtMapSetPair cosmicPair = makeCosmicPairs(cosmicHG, cosmicLG);
//
//   WireCell2dToy::pmtMap beamMerge = mergeBeam(beamPair);
//   WireCell2dToy::pmtMapSet cosmicMerge = mergeCosmic(cosmicPair);
//
//   fop_wf->Clear();
//   fop_timestamp->clear();
//   fop_femch->clear();
//
//   //function in ToyLightReco
//   dumpPmtVec(beamMerge, cosmicMerge);
//   //fop_* are all now filled
//
//   std::vector<COphitSelection> ophits_group;
//   COphitSelection left_ophits;
//   //for each pmt, send through COphit
//   for (int i=32;i!=fop_femch->size();i++){
//     COphit *op_hit = new COphit(fop_femch->at(i), (TH1S*)fop_wf->At(i), fop_timestamp->at(i) - triggerTime, op_gain->at(fop_femch->at(i)), op_gainerror->at(fop_femch->at(i)));
//     op_hits.push_back(op_hit);
//
//     //save ophits to ophits_group depending on size of ophits
//     if (op_hit->get_type()){ // what type  good baseline ???
//       bool flag_used = false;
//       if (ophits_group.size()==0){
//   	     COphitSelection ophits;
//   	     ophits.push_back(op_hit);
//   	     ophits_group.push_back(ophits);
//   	     flag_used = true;
//       }
//       else{
//   	     for (size_t j=0; j!=ophits_group.size();j++){
//   	        for (size_t k=0; k!= ophits_group.at(j).size(); k++){
//   	           if (fabs(op_hit->get_time() - ophits_group.at(j).at(k)->get_time()) < 0.1 ){  // time unit??? 0.1 us?
//   	              ophits_group.at(j).push_back(op_hit);
//   	              flag_used = true;
//   	              break;
//   	           }
//   	        }
//   	        if (flag_used)
//   	        break;
//   	    }
//       }
//       if (!flag_used){
//   	     COphitSelection ophits;
//   	     ophits.push_back(op_hit);
//   	     ophits_group.push_back(ophits);
//       }
//     }
//     else{
//       left_ophits.push_back(op_hit);
//     }
//   }
//
//   for (size_t i=0;i!=left_ophits.size();i++){
//     bool flag_used = false;
//     for (size_t j=0; j!=ophits_group.size();j++){
//       for (size_t k=0; k!= ophits_group.at(j).size(); k++){
//   	     if (fabs(left_ophits.at(i)->get_time() - ophits_group.at(j).at(k)->get_time())<0.1){ // time unit??? 0.1 us?
//   	        ophits_group.at(j).push_back(left_ophits.at(i));
//   	        flag_used = true;
//   	        break;
//   	      }
//       }
//       if (flag_used)
//   	  break;
//     }
//   }
//   //go through each COphit and perform opflash
//   for (size_t j=0; j!=ophits_group.size();j++){
//     Opflash *flash = new Opflash(ophits_group.at(j));
//     //save any time non zero flash
//     if (flash->get_total_PE()!=0){
//       cosmic_flashes.push_back(flash);
//     }
//     else{
//       delete flash;
//     }
//   }
//
//   //get rid of root here
//   //fill hraw with optical waveform
//   for (int i=0;i!=32;i++){
//     TH1S *hsignal = (TH1S*)fop_wf->At(i);
//     for (int j=0;j!=1500;j++){
//       hraw[i]->SetBinContent(j+1,hsignal->GetBinContent(j+1)-2050);
//     }
//     //fill gain and time for each pmt
//     gain[i] = op_gain->at(i);
//     beam_dt[i] = fop_timestamp->at(i) - triggerTime;
//   }
//
//   // all funtions in ToyLightReco
//   //commenting out for now, should probably be called later
//
//   //Process_beam_wfs();
//   //sort_flashes();
//   // update map
//   //update_pmt_map();
// }
