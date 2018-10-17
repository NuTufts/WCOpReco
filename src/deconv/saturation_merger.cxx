#include "saturation_merger.h"


namespace wcopreco {

saturation_merger::saturation_merger(UBEventWaveform UB_Ev) {
  std::cout << "\nYou've crafted a class, soft clap. Now get to work!\n\n" ;

  OpWaveformCollection BHG_WFs;
  OpWaveformCollection BLG_WFs;
  OpWaveformCollection CHG_WFs;
  OpWaveformCollection CLG_WFs;

  BHG_WFs = (UB_Ev.get__wfm_v() [0]);
  BLG_WFs = (UB_Ev.get__wfm_v() [1]);
  CHG_WFs = (UB_Ev.get__wfm_v() [2]);
  CLG_WFs = (UB_Ev.get__wfm_v() [3]);

  std::cout << "BeamLowGainWf 1 BEFORE Scaling: " << UB_Ev.get__wfm_v().at(1).at(18).at(750) << "\n";
  scale_lowgains(&BLG_WFs,&CLG_WFs);
  std::cout << "Beam_Original 1 AFTER  Scaling: " << UB_Ev.get__wfm_v().at(1).at(18).at(750) << "\n";
  std::cout << "BeamLGWF_COPY 1 AFTER  Scaling: " << BLG_WFs.at(18).at(750) << "\n";






}

// void wcopreco::saturation_merger::deconv_test()
//
//   {}


void saturation_merger::scale_lowgains(OpWaveformCollection *BLG_WFs, OpWaveformCollection *CLG_WFs){
    std::cout << "Little Work here and there \n";

    std::cout << "BeamLowGainWf 1 IN FN BEFORE  Scaling: " << BLG_WFs->at(18).at(750) << "\n";

    //First lets do the Beam Low Gain Waveform Rescaling
    double baseline = 2050;
    double temp_baseline;
    int nbins;
    //Start with a loop through the beam lg waveforms
    for (int n=0; n < BLG_WFs->size() ; n++){
      nbins = BLG_WFs->at(n).size();
      temp_baseline = findBaselineLg(&BLG_WFs->at(n), nbins);
      if (fabs(temp_baseline-baseline) <= 8 ) {
        baseline = temp_baseline;
      }

    }


    BLG_WFs->at(18).at(750) = 9999;
    std::cout << "BeamLowGainWf 1 IN FN AFTER  Scaling: " << BLG_WFs->at(18).at(750) << "\n";


}

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
  std::cout << "    Error in saturation_merger::findScaling, you you input channel bigger than 31:  " << channel << std::endl;
  return 0;
}

}
