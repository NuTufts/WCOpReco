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
    // std::cout << *std::max_element(wfm.begin(),wfm.end()) << " Is max in element before any baseline removed" <<std::endl;

    Remove_Baseline_Leading_Edge(&wfm);
    // std::cout << *std::max_element(wfm.begin(),wfm.end()) << " Is max in element after 1st baseline removed" <<std::endl;
    Remove_Baseline_Secondary(&wfm);
    // std::cout << *std::max_element(wfm.begin(),wfm.end()) << " Is max in element after 2nd baseline removed" <<std::endl;


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

    for (int index =nbins-1; index>nbins/2; index--){
      re[index] = re[(nbins-1) - index];
      im[index] = im[(nbins-1) - index];

    }
    // std::cout << re[1499] << "     " << re[0] << std::endl;
    // std::cout << im[1499] << "     " << im[0] << std::endl;

    //Copy those array values into vectors passed in by reference.
    // This is inefficient, but makes for an easier user interface.
    double im_i =0;
    double re_i = 0;
    for (int i =0; i<nbins; i++){
      //Calculate the phase_raw
      im_i = im[i];
      re_i = re[i];
      double ph = 0;
      // fft->GetPointComplex(ind, re, im);
      if (TMath::Abs(re_i) > 1e-13){
         //ph = TMath::ATan(im_i/re_i);
         ph = atan2(im_i , re_i);


         //find the correct quadrant
      //    if (re_i<0 && im_i<0)
      //       ph -= TMath::Pi();
      //    if (re_i<0 && im_i>=0)
      //       ph += TMath::Pi();
      // } else {
      //    if (TMath::Abs(im_i) < 1e-13)
      //       ph = 0;
      //    else if (im_i>0)
      //       ph = TMath::Pi()*0.5;
      //    else
      //       ph = -TMath::Pi()*0.5;
      }
      phase_raw.at(i) = ph;
      //End of phase_raw calc

      //Calculate the mag_v
      double magnitude = TMath::Sqrt(re[i]*re[i]+im[i]*im[i]);
      mag_raw[i] = magnitude;
      //if (i%50 == 0) std::cout<<"Magnitude is " << mag_raw[i] <<std::endl;
      //End of mag_v calc
    }

    // memcpy(mag_raw.data(), re, sizeof(double)*nbins);
    // memcpy(phase_raw.data(), im, sizeof(double)*nbins);

    delete fftr2c;
    double max_freq_MHz = 64*1500*2*TMath::Pi();
    //plot wfm_power
    TCanvas *c2 = new TCanvas("wfmPow", "wfmPow", 600, 400);
    TH1D * wfm_pow = new TH1D("WaveformPowerSpectrum" ,"wmfPowerSpec", 1500, 0., max_freq_MHz);
    // std::cout << " Mag 780::    " << mag_raw.at(780) <<std::endl;
    for (int i=0; i<(mag_raw.size()-1); i++) {
      wfm_pow->SetBinContent(i,mag_raw.at(i));
      //std::cout << mag_raw.at(i) << " :Value of wfm_pow" << std::endl;
    }
    // std::cout << mag_raw.at(1499) <<std::endl;
    // std::cout << wfm_pow->GetBinContent(0) << " Content at 0    " << wfm_pow->GetBinContent(1499) << " Content at end \n" ;
    wfm_pow->Draw();
    c2->SaveAs("wfm_pow.png");
    delete c2;

    TCanvas *c3 = new TCanvas("wfmPhase", "wfmPhase", 600, 400);
    TH1D * wfm_phase = new TH1D("WaveformPhaseSpectrum" ,"wmfPhaseSpec", 1500, 0., max_freq_MHz);
    // std::cout << " Phase 780::    " << phase_raw.at(780) <<std::endl;
    for (int i=0; i<(phase_raw.size()-1); i++) {
      wfm_phase->SetBinContent(i,phase_raw.at(i));
      //std::cout << mag_raw.at(i) << " :Value of wfm_pow" << std::endl;
    }
    wfm_phase->Draw();
    c3->SaveAs("wfm_phase.png");
    delete c3;

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
  	     freq = ((double)i/(double)nbins*2.)*1.0;
      }
      else{
  	     freq = (((double)nbins-(double)i)/(double)nbins*2.)*1.0;
      }
      double rho = mag_raw.at(i)/ mag_rc.at(i) / mag_spe.at(i);
      double phi = phase_raw.at(i) - phase_rc.at(i) - phase_spe.at(i);

      //double rho = mag_raw.at(i);
      //double phi = phase_raw.at(i);

      if (i==0) rho = 0;

      value_re[i] = rho * BandPassFilter(freq)* (cos(phi)/nbins)*2;
      value_im[i] = rho * BandPassFilter(freq)* (sin(phi)/nbins)*2;

      value_re1[i] = rho * (cos(phi)/nbins)*2 * HighFreqFilter(freq);
      value_im1[i] = rho * (sin(phi)/nbins)*2 * HighFreqFilter(freq);

      // if(i%50 == 0){
      //   std::cout << "val_re of " << i <<  " is: " << value_re[i] << std::endl;
      //   std::cout << "val_im of " << i <<  " is: " << value_im[i] << std::endl;
      //   std::cout << "val_re1 of " << i <<  " is: " << value_re1[i] << std::endl;
      //   std::cout << "val_im1 of " << i <<  " is: " << value_im1[i] << std::endl << std::endl;
      // }
    }

    // ROI finding
    TVirtualFFT *ifft = TVirtualFFT::FFT(1,&nbins,"C2R");
    ifft->SetPointsComplex(value_re,value_im);
    //ifft->SetPointsComplex(re,im);
    ifft->Transform();

    double *re_inv = new double[nbins]; //Real -> Magnitude
    double *im_inv = new double[nbins]; //Imaginary -> Phase

    ifft->GetPointsComplex(re_inv, im_inv);

    std::vector<double> inverse_res;
    inverse_res.resize(nbins);
    for (int i = 0; i < nbins ; i++){
      double value = re_inv[i];
      inverse_res.at(i) = value;
      //if (i%50 == 0) std::cout<< "ifft value: " <<value <<std::endl;
    };
    delete ifft;

    // calcumate rms and mean ...
    std::pair<double,double> results = cal_mean_rms(inverse_res, nbins);
    std::cout <<"mean: " << results.first << " rms: " << results.second << std::endl;
    std::vector<double> hflag;
    hflag.resize(nbins);
    // TH1F *hflag = new TH1F("hflag","hflag",1500,0,1500);
    for (int i=0;i<nbins;i++){
      double content = inverse_res.at(i);
      if (fabs(content-results.first)>5*results.second){
	       for (int j=-20;j!=20;j++){
	        //hflag->SetBinContent(i+j+1,1);
          double flag =1.0;
          if((i+j) >= 0 && (i+j) < 1500) hflag.at(i+j) = flag;
	       }
       }
    }

    // solve for baseline
    TVirtualFFT *ifft1 = TVirtualFFT::FFT(1,&nbins,"C2R");
    ifft1->SetPointsComplex(value_re1,value_im1);
    ifft1->Transform();

    double *re_inv1 = new double[nbins]; //Real -> Magnitude
    double *im_inv1 = new double[nbins]; //Imaginary -> Phase

    ifft1->GetPointsComplex(re_inv1, im_inv1);

    std::vector<double> inverse_res1;
    inverse_res1.resize(nbins);
    for (int i = 0; i < nbins ; i++){
      double value = re_inv1[i];
      inverse_res1.at(i) = value;
      if (i%50 == 0) std::cout<< "ifft value: " <<value <<std::endl;
    };
    double A11 = 0, A12 = 0, A21=0, A22=0;
    double B1 = 0, B2 = 0;
    double a=0, b=0;
    for (int i=0;i!=1500;i++){
      double bincenter = i+.5;
      if (hflag.at(i)==0){
      	B2 += inverse_res1.at(i);
      	B1 += inverse_res1.at(i) * bincenter;
      	A11 += pow(bincenter,2);
      	A12 += bincenter;
      	A21 += bincenter;
      	A22 += 1;
      }
    }

    if (A22>0){
      a = (B1*A22-B2*A12)/(A11*A22-A21*A12);
      b = (B1*A21-B2*A11)/(A22*A11-A12*A21);
    }
    // std::cout << a << " " << b << std::endl;
    for (int i=0;i!=1500;i++){
      //fb->SetBinContent(i+1,fb->GetBinContent(i+1) - a * fb->GetBinCenter(i+1) -b);
      double bincenter = i+.5;
      inverse_res1.at(i) = inverse_res1.at(i) - a * bincenter -b;
    }
    results = cal_mean_rms(inverse_res1, nbins);
    for (int i=0;i!=1500;i++){
      if (i<1500-4){
	       //fb->SetBinContent(i+1,fb->GetBinContent(i+1)-results.first+0.01);
         inverse_res1.at(i) = inverse_res1.at(i) -results.first+0.01;
      }else{
	       inverse_res1.at(i) = 0;
      }
    }

  //   // prepare L1 fit ... 
  //   TH1F *hrebin = new TH1F("hrebin","hrebin",250,0,250);
  //
  //   for (int i=0;i!=250;i++){
  //     hrebin->SetBinContent(i+1,
	// 		       fb->GetBinContent(6*i+1) +
	// 		       fb->GetBinContent(6*i+2) +
	// 		       fb->GetBinContent(6*i+3) +
	// 		       fb->GetBinContent(6*i+4) +
	// 		       fb->GetBinContent(6*i+5) +
	// 		       fb->GetBinContent(6*i+6) );
  //   }
  //   for (int i=0;i!=250;i++){
  //     hdecon[j]->SetBinContent(i+1,hrebin->GetBinContent(i+1));
  //   }
  //
  //
  //   // work on the L1 ...
  //   std::vector<double> vals_y;
  //   std::vector<double> vals_x;
  //   std::vector<int> vals_bin;
  //
  //   for (int i=0;i!=250;i++){
  //     double content = hrebin->GetBinContent(i+1);
  //     if (content>0.3){
	// vals_y.push_back(content);
	// vals_x.push_back(hrebin->GetBinCenter(i+1));
	// vals_bin.push_back(i);
  //
	// // global_vals_y.push_back(content);
	// // global_vals_x.push_back(hrebin->GetBinCenter(i+1));
	// // global_vals_bin.push_back(i);
	// // global_vals_pmtid.push_back(j);
  //     }
  //   }
  //
  //   int nbin_fit = vals_x.size();
  //   VectorXd W = VectorXd::Zero(nbin_fit);
  //   MatrixXd G = MatrixXd::Zero(nbin_fit,nbin_fit);
  //   for (int i=0;i!=nbin_fit;i++){
  //     W(i) = vals_y.at(i) / sqrt(vals_y.at(i));
  //     double t1 = vals_x.at(i); // measured time
  //     for (int k=0;k!=nbin_fit;k++){
	// double t2 = vals_x.at(k); // real time
	// if (t1>t2) {
	//   G(i,k) = (0.75 * (exp(-((t1-t2)*6*15.625/1000.-3*15.625/1000.)/1.5)-exp(-((t1-t2)*6*15.625/1000.+3*15.625/1000.)/1.5))) / sqrt(vals_y.at(i));
	// }else if (t1==t2){
	//   G(i,k) = (0.25 + 0.75 *(1-exp(-3*15.625/1000./1.5))) / sqrt(vals_y.at(i));
	// }else{
	//   continue;
	// }
  //     }
  //   }
  //
  //   double lambda = 5;//1/2.;
  //   WireCell::LassoModel m2(lambda, 100000, 0.05);
  //   m2.SetData(G, W);
  //   m2.Fit();
  //   VectorXd beta = m2.Getbeta();
  //   for (int i=0;i!=nbin_fit;i++){
  //     //global_sols.push_back(beta(i));
  //     hl1[j]->SetBinContent(vals_bin.at(i)+1,beta(i));
  //   }
  //
  //
  //   delete hrebin;
  //   delete hflag;
  //   delete fb;
  //   delete ifft;
  //   delete hm;
  //   delete hp;
  //   delete hm_rc;
  //   delete hp_rc;
  //   delete hm_spe;
  //   delete hp_spe;
  // }

    TCanvas *c8 = new TCanvas("fb", "fb", 600, 400);
    TH1D * ifft1_plot = new TH1D("ifft1" ,"ifft1", 1480, 10., 1490.);
    for (int i=10; i<(inverse_res1.size()-10); i++) {
      ifft1_plot->SetBinContent(i,inverse_res1.at(i));
      //std::cout << mag_raw.at(i) << " :Value of wfm_pow" << std::endl;
    }
    ifft1_plot->Draw();
    c8->SaveAs("ifft1.png");
    delete c8;

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
  double deconvolver::BandPassFilter(double frequency2)
  {
    //   TF1 f3("f3","(1-exp(-pow(x/[0],2)))*exp(-pow(x/[1],[2]))",0,1);

    double par_0 = 0.05;
    double par_1 = 0.45;
    double par_2 = 3.07;

    double bandpass_filter = (1-exp(-pow(frequency2/par_0,2)))*exp(-pow(frequency2/par_1,par_2));
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
      // else {std::cout << "Baseline adjusted by: " <<baseline << std::endl;}
      //std::cout << h1.GetMaximum() << " " << baseline << std::endl;
      for (int j=0;j!=1500;j++){
          wfm->at(j) = wfm->at(j) - baseline;
      }

      return;
   }

   std::pair<double,double> deconvolver::cal_mean_rms(std::vector<double> wfm, int nbin)
   {
      //calculate the mean and rms values
      TH1F *h4 = new TH1F("h4","h4",2000,-10,10);
      double mean, rms;
      for (int i=0;i!=nbin;i++){
        double content = wfm.at(i);
        if (fabs(content)<10)
        h4->Fill(content);
      }
      mean = h4->GetBinCenter(h4->GetMaximumBin()+1);

      double xq = 0.5;
      double par[3];
      h4->GetQuantiles(1,&par[1],&xq);
      xq = 0.5 - 0.34;
      h4->GetQuantiles(1,&par[0],&xq);
      xq = 0.5 + 0.34;
      h4->GetQuantiles(1,&par[2],&xq);

      rms = sqrt((pow(par[0]-par[1],2)+pow(par[2]-par[1],2))/2.);

      delete h4;
      return std::make_pair(mean,rms);
   }
}
