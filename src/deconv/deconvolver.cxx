#include "deconvolver.h"

namespace wcopreco {

void wcopreco::deconvolver::deconv_test()

  {
    int nbins = 1500;
    float bin_width = (1.0/(64e6) );

    //load raw data
    std::string file = "src/data/celltree.root";
    wcopreco::DataReader reader(file);
    std::cout << "Filepath is set to:   " << file << std::endl;
    int EVENT_NUM = 3;
    int TYPE_OF_COLLECTION =0;
    int WFM_INDEX =0;
    int SIGNAL_INDEX =2;
    wcopreco::UBEventWaveform _UB_Ev_wfm;

    _UB_Ev_wfm = reader.Reader(EVENT_NUM);
    OpWaveform wfm = ( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] );

    //remove baseline (baseline here means leading edge)
    std::cout << *std::max_element(wfm.begin(),wfm.end()) << " Is max in element before any baseline removed" <<std::endl;

    Remove_Baseline_Leading_Edge(&wfm);
    std::cout << *std::max_element(wfm.begin(),wfm.end()) << " Is max in element after 1st baseline removed" <<std::endl;
    Remove_Baseline_Secondary(&wfm);
    std::cout << *std::max_element(wfm.begin(),wfm.end()) << " Is max in element after 2nd baseline removed" <<std::endl;


    std::vector<double> wfm_doubles(wfm.begin(), wfm.end());
    //plot wfm_doubles
    TCanvas *c1 = new TCanvas("Title", "canvas", 600, 400);
    TH1D * wfm_data = new TH1D("Datawfm" ,"name", 1499, 0., 1499.);
    for (int i=0; i<(wfm_doubles.size()-1); i++) {
      wfm_data->Fill(i,wfm_doubles[i]);
      // if (wfm_doubles[i] >5 )std::cout << wfm_doubles[i] << " :Value of wfm_data" << std::endl;
    }
    wfm_data->Draw();
    c1->SaveAs("wfm_data.png");
    delete c1;

    //get power spectrum of data
    //Create Mag and Phase vectors
    std::vector<double> mag_raw;
    std::vector<double> phase_raw;
    mag_raw.resize(nbins);
    phase_raw.resize(nbins);

    //Get the input to the fourier transform ready
    std::vector<double> power_spec_d(nbins,0);
    power_spec_d = wfm_doubles;
    double *in = power_spec_d.data();

    //Start the fourier transform (real to complex)
    TVirtualFFT *fftr2c = TVirtualFFT::FFT(1, &nbins, "R2C");
    fftr2c->SetPoints(in);
    fftr2c->Transform();
    double *re = new double[nbins]; //Real -> Magnitude
    double *im = new double[nbins]; //Imaginary -> Phase

    fftr2c->GetPointsComplex(re, im); //Put the values in the arrays

    //Copy those array values into vectors passed in by reference.
    //This is inefficient, but makes for an easier user interface.
    memcpy(mag_raw.data(), re, sizeof(double)*nbins);
    memcpy(phase_raw.data(), im, sizeof(double)*nbins);

    delete fftr2c;

    //plot wfm_power
    TCanvas *c2 = new TCanvas("wfmPow", "wfmPow", 600, 400);
    TH1D * wfm_pow = new TH1D("WaveformPowerSpectrum" ,"wmfPowerSpec", 1500, 0., 755.);
    //std::cout << "size of mag_raw " << mag_raw.size() <<std::endl;
    for (int i=0; i<(mag_raw.size()-1); i++) {
      wfm_pow->Fill(i,mag_raw.at(i));
      //std::cout << mag_raw.at(i) << " :Value of wfm_pow" << std::endl;
    }
    wfm_pow->Draw();
    c2->SaveAs("wfm_pow.png");
    delete c2;

    //Cout Block for Testing RE and IM

    // int index =3;
    // std::cout << power_spec_d[index] << "    POWER SPEC[" << index << "]" <<std::endl;
    // std::cout << re[index] << "    RE[" << index << "]" << std::endl;
    // std::cout << *(re+500) << "   Accessed *(re+500)" << std::endl;
    // std::cout << mag_raw.at(index) << "    MAG[" << index << "]" << std::endl;
    // std::cout << im[index] << "    IM[" << index << "]" << std::endl;

    // std::cout << nbins << " bins POWER  " << bin_width << "  tick width POWER" << std::endl;
    // std::cout << nbins*bin_width << " Is total width of wfm" << std::endl;

    std::string word = "SPE_wfm" ;

    UB_spe spe(word, true);
    // spe.gain = 1;

    std::vector<double> vec_spe = spe.Get_wfm(nbins,bin_width);
    //Cout Block for testing SPE wfm
    // std::cout << vec_spe.size() << "    Is size of vector." << std::endl;
    // std::cout << vec_spe.at(1) << "    Is first element." << std::endl;
    // std::cout << vec_spe.at(500) << "    Is 500 element." << std::endl;
    // std::cout << *std::max_element(vec_spe.begin(),vec_spe.end()) << "    Is MAX element." << std::endl;

    std::vector<double> mag_spe;
    std::vector<double> phase_spe;

    spe.Get_pow_spec(nbins,bin_width,&mag_spe,&phase_spe);
    //Cout Block for testing SPE power spectrum
    // std::cout << mag_spe.size() << "    Is size of vector." << std::endl;
    // std::cout << mag_spe.at(1) << "    Is first element." << std::endl;
    // std::cout << mag_spe.at(500) << "    Is 500 element." << std::endl;
    // std::cout << *std::max_element(mag_spe.begin(),mag_spe.end()) << "    Is MAX element." << std::endl;

    std::string word2 = "RC_Wfm";
    UB_rc rc(word2,true);

    std::vector<double> vec_rc = rc.Get_wfm(nbins,bin_width);
    //Cout Block for testing RC wfm
    // std::cout << vec_rc.size() << "    Is size of vector(rc)." << std::endl;
    // std::cout << vec_rc.at(1) << "    Is first element(rc)." << std::endl;
    // std::cout << vec_rc.at(500) << "    Is 500 element(rc)." << std::endl;
    // std::cout << *std::max_element(vec_rc.begin(),vec_rc.end()) << "    Is MAX element(rc)." << std::endl;

    std::vector<double> mag_rc;
    std::vector<double> phase_rc;

    rc.Get_pow_spec(nbins,bin_width,&mag_rc,&phase_rc);
    //Cout Block for testing RC power spectrum
    // std::cout << mag_rc.size() << "    Is size of vector(rc)." << std::endl;
    // std::cout << mag_rc.at(1) << "    Is first element(rc)." << std::endl;
    // std::cout << mag_rc.at(500) << "    Is 500 element(rc)." << std::endl;
    // std::cout << *std::max_element(mag_rc.begin(),mag_rc.end()) << "    Is MAX element(rc)." << std::endl;

    double value_re[nbins], value_im[nbins];
    double value_re1[nbins], value_im1[nbins];

    for (int i=0;i<nbins;i++){
        double freq;
        if (i<=750){
    	     freq = i/nbins*2.;
        }
        else{
    	     freq = (nbins-i)/nbins*2;
        }
        double rho = mag_raw.at(i)/ mag_rc.at(i) / mag_spe.at(i);
        double phi = phase_raw.at(i) - phase_rc.at(i) - phase_spe.at(i);
        if (i==0) rho = 0;

        value_re[i] = rho * BandPassFilter(freq)* cos(phi)/nbins;
        value_im[i] = rho * BandPassFilter(freq)* sin(phi)/nbins;

        //test band pass filter
        // if (i%100 == 0) std::cout << value_re[i] << " Is value of value_re at: " << i << std::endl;
        // if (i%100 == 0) std::cout << value_im[i] << " Is value of value_im at: " << i << std::endl;

        value_re1[i] = rho * cos(phi)/nbins * HighFreqFilter(freq);
        value_im1[i] = rho * sin(phi)/nbins * HighFreqFilter(freq);

        //test high freq filter
        // if (i%100 == 0) std::cout << value_re1[i] << " Is value of value_re1 at: " << i << std::endl;
        // if (i%100 == 0) std::cout << value_im1[i] << " Is value of value_im1 at: " << i << std::endl;

    }

  }

  //toy light reco f2
  double deconvolver::HighFreqFilter(double frequency)
  {
    double par_0 = 0.45;
    double par_1 = 3.07;
     //   TF1 f2("f2","exp(-pow(x/[0],[1]))",0,1); // high frequency filter
    double freq_filter = exp(-pow(frequency/par_0,par_1));
    return freq_filter;
  }

  //toy light reco f3
  double deconvolver::BandPassFilter(double frequency)
  {
    //   TF1 f3("f3","(1-exp(-pow(x/[0],2)))*exp(-pow(x/[1],[2]))",0,1);

    double par_0 = 0.05;
    double par_1 = 0.45;
    double par_2 = 3.07;

    double bandpass_filter = (1-exp(-pow(frequency/par_0,2)))*exp(-pow(frequency/par_1,par_2));
    return bandpass_filter;
   }




   void deconvolver::Remove_Baseline_Leading_Edge(OpWaveform *wfm)
   {
     int size = wfm->size();
     double baseline = wfm->at(0);
     for (int i=0; i<size; i++) {
       wfm->at(i) = wfm->at(i) - baseline;
     }
     return;
   }

   void deconvolver::Remove_Baseline_Secondary(OpWaveform *wfm)
   {
      TH1F h1("h1","h1",200,-100,100);

      h1.Reset();
      for (int j=0;j!=20;j++){
          h1.Fill(wfm->at(j));
      }
      // double xq = 0.5;
      // double baseline;
      // h1.GetQuantiles(1,&baseline,&xq);
      double baseline = h1.GetMaximumBin()-100;
      if (fabs(baseline)>=8) {baseline = 0;}
      else {std::cout << "Baseline adjusted by: " <<baseline << std::endl;}
      //std::cout << h1.GetMaximum() << " " << baseline << std::endl;
      for (int j=0;j!=1500;j++){
          wfm->at(j) = wfm->at(j) - baseline;
      }

      return;
   }
}
