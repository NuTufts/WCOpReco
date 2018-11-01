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


    //Set data member merged versions of waveforms
    merged_beam = *beam_merger(&BHG_WFs, &BLG_WFs);
    merged_cosmic = *cosmic_merger(&CHG_WFs, &CLG_WFs);

    //Make all the individual waveforms the new type (merged beam or merged cosmic (5 and 6))
    for (int n = 0; n< merged_beam.size(); n++){
      merged_beam.at(n).set_type(4);
    }
    for (int n = 0; n< merged_cosmic.size(); n++){
      merged_cosmic.at(n).set_type(5);
    }


    UB_Ev_Merged.add_entry(merged_beam,   4 );
    UB_Ev_Merged.add_entry(merged_cosmic, 5 );
    UB_Ev_Merged.set_op_gain(   UB_Ev.get_op_gain()   );
    UB_Ev_Merged.set_op_gainerror( UB_Ev.get_op_gainerror()   );


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
          BLG_WFs->at(n).at(bin) = floor(( (BLG_WFs->at(n).at(bin)-baseline)*scalefactor ) + baseline) ;
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
          CLG_WFs->at(n).at(bin) = floor(( (CLG_WFs->at(n).at(bin)-baseline)*scalefactor ) + baseline) ;
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

OpWaveformCollection* saturation_merger::cosmic_merger(OpWaveformCollection* CHG, OpWaveformCollection* CLG, short saturation_threshold){
  //first pair the low and high gain - can probably make as seperate function...
  //want to remove hard coded values eventually
  int tick_window = 20;
  float tick = .015625;
  //std::cout <<"test check" << tick_window*tick <<std::endl;
  // if (CHG->size()!=CLG->size()){
  //   std::cout << "HG AND LG NOT SAME SIZE!!" << std::endl;
  //   std::cout << "HG size: " << CHG->size() <<std::endl;
  //   std::cout << "LG size: " << CLG->size() <<std::endl;
  // };
  /*
  Going to have to loop through the high gains, first we want to see if a waveform is
  saturated. Is so we then need to see if it is isolated from all possible low gains
  If it is isolated, at it to the output, we want that. If not isolated then add the low gain version
  to the output instead. Those should be the 3 cases we care about. The output of this should
  be the same size as the inputted CHGcollection, so we can just update that collection by reference
  instead. That will save us memory.
  */

  //loop through high gain (important) collection:

  //Create a map to ensure we only use each lowgain wfm at most once.
  std::map<int,bool> is_used;
  for (int i =0;i<CLG->size();i++){
    is_used[i] = false;
  }
  bool is_saturated;
  bool is_paired;
  int count_saturated =0;
  int count_bin_sat;
  int count_paired =0;
  int count_sat_no_friends=0;
  int count_good_hg =0;
  int count_continues=0;
  int continues_this_hg;
  int count_lg_unused =0;
  int count_lg_skipped=0;
  int count_fixed=0;
  for (int idx_chg = 0; idx_chg<CHG->size(); idx_chg++){
    continues_this_hg=0;
    //if abs(hightime-lowtime) < tickwindow*tick , then pair the wfms to merge

    //check to make sure times aren't same
    // OpWaveform Hwfm = CHG->at(idx_chg);
    // OpWaveform Lwfm = CLG->at(idx_chg);
    // if (idx_chg%20==0){
    //   std::cout<< "time diff: " << Hwfm.get_time_from_trigger() - Lwfm.get_time_from_trigger() <<std::endl;
    // }

    is_saturated = false;
    count_bin_sat =0;
    //Loop through all bins in this waveform
    for (int bin =0; bin<CHG->at(idx_chg).size(); bin++){
      if (CHG->at(idx_chg).at(bin) > saturation_threshold) {
        count_bin_sat++ ;
        if(count_bin_sat >= 3){
          //Consider it saturated
          is_saturated = true ;
          count_saturated++;
          break;
        }
      }
    }
    //If it's saturated then we need to look for a low gain pair
    if (is_saturated){
      is_paired =0;
      //Get Channel and timestamp of CHG for matching
      float time_High = CHG->at(idx_chg).get_time_from_trigger();
      short ch_High = CHG->at(idx_chg).get_ChannelNum();

      //Loop through all LG looking for a friend
      for (int idx_clg = 0; idx_clg<CLG->size(); idx_clg++){
        /*
        If this lowgain waveform has already been used, skip to the next one
        Meant to duplicate WC's deletion of the low gain wfm after use.
        As far as I can tell all this is doing is saving you the trouble of
        calculating the next few stuff for this waveform
        */
        if (is_used[idx_clg]) {
          count_continues++;
          continues_this_hg++;
          continue;
        }
        //Get potential friend's channel and timestamp
        float time_Low = CLG->at(idx_clg).get_time_from_trigger();
        short ch_Low = CLG->at(idx_clg).get_ChannelNum();

        if (ch_Low == ch_High && fabs(time_High-time_Low) < (float)tick_window*(float)tick){


          // std::cout << "FOUND A PAIR!!!" << std::endl;
          //Replace HG with it's pair
          // std::cout << idx_chg << " index changed \n";
          // std::cout << idx_chg << "   high gain index\n";
          //
          // std::cout << idx_clg << "   Low gain index\n";
          CHG->at(idx_chg) = CLG->at(idx_clg);
          is_used[idx_clg] = true; //set this LG wfm to true so we don't use it again.
          is_paired = true;
          count_paired ++;
          break;
        }

      }//End of loop through low gains
      //Check to see if no low gain pair found
      if(is_paired == false) {
        //Do nothing to change this high gain waveform, is saturated and unfixable
        //Keep it in the collection to be returned

        //std::cout << "No friend found, waveform not paired with a lowgain, and saturated\n";
        count_sat_no_friends ++;
      }
    }
    //Since this is a boolean it should always be true or false, but else if for check
    else if (is_saturated ==false){
      //Do nothing to this waveform, it was unsaturated.
      //Keep it in the collection to be returned.
      count_good_hg ++;

      for (int idx_clg=0; idx_clg<CLG->size(); idx_clg++){
        if (is_used[idx_clg] ==true) {continue;}
        float time_High = CHG->at(idx_chg).get_time_from_trigger();
        float time_Low= CLG->at(idx_clg).get_time_from_trigger();
        short ch_High = CHG->at(idx_chg).get_ChannelNum();
        short ch_Low = CLG->at(idx_clg).get_ChannelNum();
        if ((ch_Low == ch_High) && (fabs(time_High-time_Low) < tick_window*tick)){

          //std::cout << "Time Difference: " <<  fabs(time_High-time_Low) <<std::endl;
          is_used[idx_clg] =true;
          count_fixed++;
          break;
        }
      }

      // std::cout << "Waveform wasn't saturated, happy just the way it is\n";

    }
    else {
      std::cout << "XXXXXXXXXXXXXXXXXXXXXXXxxxxxxxx PROBLEM HG meets no criteria! xxxxxxxxxxxxxXxXXXXXXXXXXXX";
    }
    // std::cout << continues_this_hg << "    The number of times continued for HG wfm    " << idx_chg << "\n";
  }
  //Now we add in all the unpaired low gain waveforms.
  for (int idx_clg=0; idx_clg<CLG->size(); idx_clg++){
    if (is_used[idx_clg] ==false ){
      //Option A
      count_lg_unused++;
      CHG->add_waveform( CLG->at(idx_clg) );

      //Option B (Hardcoded the function add_waveform)
      // CHG->emplace_back(std::move(CLG->at(idx_clg)));
      // std::cout << "  Got A \n\n\n\n";
      // CHG->insert_channel2index(CLG->at(idx_clg).get_ChannelNum(), CHG->size()-1);
      // std::cout << "  Got B \n\n\n\n";
      //
      // CHG->insert_index2channel(CHG->size()-1, CLG->at(idx_clg).get_ChannelNum());
    }
      else if (is_used[idx_clg] ==true ){
        count_lg_skipped++;
      }
  }

  // std::cout << count_saturated << "     This many saturated HG \n\n";
  // std::cout << count_paired << "     There are this many HG waveforms paired with friends! :)\n";
  // std::cout << count_sat_no_friends << "     There are this many HG waveforms saturated, but without friends! :(\n";
  // std::cout << count_good_hg << "     There are this many HG waveforms not looking for friends!! :D\n";
  // std::cout << count_lg_unused << "     There are this many LG waveforms that were added because they weren't matched.\n";
  // std::cout << count_lg_skipped << "     There are this many LG waveforms that were skipped because they were used\n";
  // std::cout << count_fixed  << "     This many waveforms adjusted \n\n";



  // std::cout << CHG->size() << "    Is the total number of waveforms returned\n";



  return CHG;
}

OpWaveformCollection* saturation_merger::beam_merger(OpWaveformCollection* BHG, OpWaveformCollection* BLG, short saturation_threshold) {
  OpWaveformCollection* merged_beam;
  if ((BHG->size() != BLG->size() ) && (BHG->size()>0)) {
    std::cout << "Beam High Gain Collection and Beam Low Gain Collection do not have the same number of entries. Returning Empy merge\n";
    return merged_beam;
  }


  int n_channels = BHG->size();
  bool is_saturated;
  int count_bin_sat=0;

  int idx_ch_hg ;
  int idx_ch_lg ;

  //Loop through each waveform
  //(generally one per channel so 32 or 36 waveforms for each gain of beam)
  for(int i =0; i<n_channels; i++){

    //These calls get the index of the wfm that occurs at the channel i
    //for each gain, in case the two Opwaveformcollections aren't ordered the
    //same. The at(0) is because get_channel2index returns a vector of wfms
    //occurring at channel i but for beam we expect just one wfm per channel

    idx_ch_hg = BHG->get_channel2index(i).at(0);
    idx_ch_lg = BLG->get_channel2index(i).at(0);


    is_saturated = false;
    count_bin_sat=0;
    //Now loop through HG wfm to see if saturated (3+ ticks at value  >4050)
    for (int bin =0; bin<BHG->at(idx_ch_hg).size(); bin++){
      if (BHG->at(idx_ch_hg).at(bin) > saturation_threshold) {
        count_bin_sat++ ;
        if(count_bin_sat >= 3){
          //Consider it saturated
          is_saturated = true ;
          break;
        }
      }
    }
    if(is_saturated) {
          //If high gain waveform is saturated, replace the saturated sections with part of the low gain wfm
          std::vector<std::pair<short,short> > tickVec = findSaturationTick(&BHG->at(idx_ch_hg), saturation_threshold);
          BHG->at(idx_ch_hg) = replaceSaturatedBin( (BHG->at(idx_ch_hg)), (BLG->at(idx_ch_lg)), tickVec);

        }
  }

  return BHG;
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
      result.push_back(tempPair);
    }
  }
  return result;
}

OpWaveform wcopreco::saturation_merger::replaceSaturatedBin(OpWaveform &high, OpWaveform &low, std::vector<std::pair<short,short>> saturation_ranges){

  for(int i=0; i<(int)saturation_ranges.size(); i++){
    for(short j=saturation_ranges.at(i).first; j<saturation_ranges.at(i).second; j++){
      high.at(j) = low.at(j);
    }
  }
  return high;
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
