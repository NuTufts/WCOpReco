#include "saturation_merger.h"


namespace wcopreco {

  saturation_merger::saturation_merger(UBEventWaveform UB_Ev) {

    OpWaveformCollection BHG_WFs;
    OpWaveformCollection BLG_WFs;
    OpWaveformCollection CHG_WFs;
    OpWaveformCollection CLG_WFs;

    BHG_WFs = (UB_Ev.get__wfm_v() [0]);
    BLG_WFs = (UB_Ev.get__wfm_v() [1]);
    CHG_WFs = (UB_Ev.get__wfm_v() [2]);
    CLG_WFs = (UB_Ev.get__wfm_v() [3]);

    // std::cout << "BeamLowGainWf 1 BEFORE Scaling: " << UB_Ev.get__wfm_v().at(1).at(18).at(750) << "\n";
    // std::cout << "CosmicLowGainWf 1 BEFORE  Scaling: " << UB_Ev.get__wfm_v().at(3).at(18).at(20) << "\n";

    scale_lowgains(&BLG_WFs,&CLG_WFs);
    //Note the original waveforms in UB_Ev do not change, just those in our copies
    // std::cout << "BeamLGWF_COPY 1 AFTER  Scaling: " << BLG_WFs.at(18).at(750) << "\n";
    // std::cout << "CosmicLGWF_COPY 1 AFTER  Scaling: " << CLG_WFs.at(18).at(20) << "\n";

    //testing makeBeamPairs (event 18)
    OpWaveform BHG_wfm = BHG_WFs.at(18);
    OpWaveform BLG_wfm = BLG_WFs.at(18);
    OpWaveformCollection merged_beam = beam_merger(&BHG_WFs, &BLG_WFs);
    //saturation_merger::timeOrder_wfm ordered_wfms(BHG_wfm,BLG_wfm);

    // typedef std::set<OpWaveform,timeOrder_wfm> pmtSet;
    // typedef std::map<short,pmtSet> pmtMapSet;
    // typedef std::pair<OpWaveform,OpWaveform> pmtPair;
    // typedef std::map<short,pmtPair> pmtMapPair;
    // pmtMapPair makeBeamPairs(pmtMapSet &high, pmtMapSet &low);







  }//End of Class Constructor

  // void wcopreco::saturation_merger::deconv_test()
  //
  //   {}


  void saturation_merger::scale_lowgains(OpWaveformCollection *BLG_WFs, OpWaveformCollection *CLG_WFs){
      //First lets do the Beam Low Gain Waveform Rescaling
      double baseline = 2050;
      double temp_baseline;
      float scalefactor;
      int channel=-1;
      int nbins;
      //Start with a loop through the beam lg waveforms
      for (int n=0; n < BLG_WFs->size() ; n++){
        nbins = BLG_WFs->at(n).size();
        temp_baseline = findBaselineLg(&BLG_WFs->at(n), nbins);
        if (fabs(temp_baseline-baseline) <= 8 ) {
          baseline = temp_baseline;
        }
        //Now let's do the actual rescaling by looping through the current waveform's bins:
        channel =  BLG_WFs->at(n).get_ChannelNum();
        scalefactor = findScaling(channel);

        for (int bin = 0; bin < nbins; bin++){
          BLG_WFs->at(n).at(bin) = ( (BLG_WFs->at(n).at(bin)-baseline)*scalefactor ) + baseline ;
        }
      }

      //Now let's scale the Cosmic Lowgains,  easier
      for (int n=0; n < CLG_WFs->size() ; n++){
        nbins = CLG_WFs->at(n).size();
        //Baseline is first value at first tick
        baseline = CLG_WFs->at(n).at(0);
        //Now let's do the actual rescaling by looping through the current waveform's bins:
        channel =  CLG_WFs->at(n).get_ChannelNum();
        scalefactor = findScaling(channel);
        for (int bin = 0; bin < nbins; bin++){
          CLG_WFs->at(n).at(bin) = ( (CLG_WFs->at(n).at(bin)-baseline)*scalefactor ) + baseline ;
        }
      }


  }//End of Function

  double wcopreco::saturation_merger::findBaselineLg(OpWaveform *wfm, int nbin){
    // I think this function needs the histogram, it's using fill to bin up the
    // different signals to find the mode in the first 20 ticks of the wfm --Josh
    TH1F *h = new TH1F("h","",1000,1500-0.5,2500-0.5);
    double baseline=0;
    for(int i=0; i!=20; i++){
      double content = wfm->at(i);
      //    baseline += content;
      if(content>1500 && content<2500){ h->Fill(content); }
    }
    //  baseline /= 6.;
    baseline = h->GetBinCenter(h->GetMaximumBin()+1);
    delete h;
    return baseline;
  }//End of Function

OpWaveformCollection saturation_merger::beam_merger(OpWaveformCollection* BHG, OpWaveformCollection* BLG, short saturation_threshold) {
  OpWaveformCollection merged_beam;

  if ((BHG->size() != BLG->size() ) && (BHG->size()>0)) {
    std::cout << "Beam High Gain Collection and Beam Low Gain Collection do not have the same number of entries. Returning Empy merge\n";
    return merged_beam;
  }
  int n_wfms = BHG->size();
  bool is_saturated;
  int count_bin_sat=0;
  //Loop through each waveform
  //(generally one per channel or 32 or 36 waveforms for each gain of beam)
  for(int i =0; i<n_wfms; i++){
    is_saturated = false;
    count_bin_sat=0;
    //Now loop through HG wfm to see if saturated (3+ ticks at value  >4050)
    for (int bin =0; bin<BHG->at(i).size(); bin++){
      if (BHG->at(i).at(bin) > saturation_threshold) {
        count_bin_sat++ ;
        std::cout << count_bin_sat << " Have been counted lated at "<< bin<<"\n";
        if(count_bin_sat >= 3){
          is_saturated = true ;
          break;
        }
      }
    }
    if(is_saturated) {
          std::cout << "Well josh you ended up not in kansas no more\n";
           // std::cout << "Xin: " << b->second.first.channel <<  " " << b->second.first.wfm.at(0) << " " << b->second.second.wfm.at(0) << std::endl;
          std::vector<std::pair<short,short> > tickVec = findSaturationTick(&BHG->at(i), saturation_threshold);
          // b->second.first.wfm = replaceSaturatedBin(b->second.first.wfm,b->second.second.wfm,tickVec);
          // b->second.first.wfm = b->second.second.wfm;
        }
    // result[b->first] = b->second.first;
  }




  std::cout << "\nStill only merging a beam? That's proving tough?\n\n" ;

  return merged_beam;
}


std::vector<std::pair<short,short> > saturation_merger::findSaturationTick(OpWaveform *wfm, short saturation_threshold){
  std::vector<std::pair<short,short> > result;
  bool saturatedStatus = false;
  std::pair<short,short> tempPair;


  for(int i=0; i<(int)wfm->size(); i++){
    if(wfm->at(i)>saturation_threshold){
      if(saturatedStatus == false){ tempPair.first = i; }
      saturatedStatus = true;
    }
    if(wfm->at(i)<saturation_threshold && saturatedStatus == true){
      saturatedStatus = false;
      tempPair.second = i;
      std::cout << i << " Index At which Saturation Occurs\n";
      result.push_back(tempPair);
    }
  }
  return result;
}

  float saturation_merger::findScaling(int channel){
    if(channel == 0){ return 10.13; }
    if(channel == 1){ return 10.20; }
    if(channel == 2){ return 10.13; }
    if(channel == 3){ return 10.05; }
    if(channel == 4){ return 9.96; }
    if(channel == 5){ return 9.95; }
    if(channel == 6){ return 10.04; }
    if(channel == 7){ return 9.58; }
    if(channel == 8){ return 9.42; }
    if(channel == 9){ return 9.81; }
    if(channel == 10){ return 9.25; }
    if(channel == 11){ return 9.61; }
    if(channel == 12){ return 9.56; }
    if(channel == 13){ return 9.35; }
    if(channel == 14){ return 9.99; }
    if(channel == 15){ return 9.66; }
    if(channel == 16){ return 10.26; }
    if(channel == 17){ return 9.82; }
    if(channel == 18){ return 10.32; }
    if(channel == 19){ return 10.08; }
    if(channel == 20){ return 9.77; }
    if(channel == 21){ return 9.64; }
    if(channel == 22){ return 10.14; }
    if(channel == 23){ return 9.74; }
    if(channel == 24){ return 9.76; }
    if(channel == 25){ return 10.10; }
    if(channel == 26){ return 10.48; }
    if(channel == 27){ return 9.81; }
    if(channel == 28){ return 9.99; }
    if(channel == 29){ return 9.79; }
    if(channel == 30){ return 9.93; }
    if(channel == 31){ return 10.01; }
    if(channel>35) {std::cout << "    Error in saturation_merger::findScaling, you you input channel bigger than 31:  " << channel << std::endl;}
    return 0;
  }//End of Function

}//end of namespace
