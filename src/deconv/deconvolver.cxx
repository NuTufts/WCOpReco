#include "deconvolver.h"

namespace wcopreco {

void wcopreco::deconvolver::deconv_test()

  {

    float bin_width = (1.0/(64e6) );

    //load raw data
    std::string file = "src/data/celltree.root";
    wcopreco::DataReader reader(file);
    std::cout << "\n\n\nFilepath is set to:   " << file << std::endl;
    int EVENT_NUM = 4;
    int TYPE_OF_COLLECTION =0;
    int WFM_INDEX =2;
    int SIGNAL_INDEX =1;
    wcopreco::UBEventWaveform _UB_Ev_wfm;
    //Still can't use enum
    // UBOpWaveformForm_t blarg;
    // blarg = UBOpWaveformForm_t.kbeam_hg;

    _UB_Ev_wfm = reader.Reader(EVENT_NUM);
    std::cout << std::endl  <<(  ( _UB_Ev_wfm ).get__wfm_v() ) .size()      <<  "   How many Collections in the Event (4)?" <<std::endl ;
    std::cout << (  ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] ).size()      <<  "  How many waveforms in the collection (depends)? " <<TYPE_OF_COLLECTION <<std::endl;
    std::cout << (  ( ( _UB_Ev_wfm ).get__wfm_v() ) [1] ).size()      <<  "  How many waveforms in the collection (depends)? " << 1 <<std::endl;
    std::cout << (  ( ( _UB_Ev_wfm ).get__wfm_v() ) [2] ).size()      <<  "  How many waveforms in the collection (depends)? " << 2 <<std::endl;
    std::cout << (  ( ( _UB_Ev_wfm ).get__wfm_v() ) [3] ).size()      <<  "  How many waveforms in the collection (depends)? " << 3 <<std::endl;

    std::cout << (  ( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] ).at(SIGNAL_INDEX))     <<  "   Attempt at Reading a Waveform Signal Value  " <<SIGNAL_INDEX << std::endl;
    std::cout << (  ( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] ).at(( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] ).size()-1))     <<  "   Attempt at Reading a Waveform Signal Value  " <<( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] ).size()-1 << std::endl << std::endl;



    OpWaveform wfm =( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] );
    op_gain = _UB_Ev_wfm.get_op_gain();
    std::cout <<_UB_Ev_wfm.get_op_gain().size() << "               SIZE HERE BLARG\n";

    // //Diagnosis Code:
    // OpWaveform wfm2 =( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [1] )  [WFM_INDEX] );
    // OpWaveform wfm3 =( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [2] )  [WFM_INDEX] );
    // OpWaveform wfm4 =( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [3] )  [WFM_INDEX] );
    //
    // std::cout << wfm.get_type() << "Type of waveform 1\n";
    // std::cout << wfm2.get_type() << "Type of waveform 2\n";
    // // std::cout << wfm3.get_type() << "Type of waveform 3\n";
    // // std::cout << wfm4.get_type() << "Type of waveform 4\n";
    // double value = 0;
    // int i=0;
    //
    // while (value<2070){
    //   std::cout << wfm.at(i) <<"\n";
    //   std::cout << wfm2.at(i)<<"\n\n";
    //   value = wfm.at(i);
    //   i++;
    //   // std::cout << wfm3.at(i) <<"\n";
    //   // std::cout << wfm4.at(i)<<"\n\n";
    //
    // }
    // //End Diagnosis Code


    //Process the Beam:
    //Note that the following code is supposed to only deal with beam waveforms, 32 channels and 1500 bin wfms.
    //Create array of vectors to process the waveforms
    TYPE_OF_COLLECTION = 0;
    int nbins;
    std::vector<double> inverse_res1[32];
    std::vector<double> decon_v[32];
    double beam_dt[32];
    OpflashSelection beam_flashes;

    std::vector<double> totPE_v(250,0);
    std::vector<double> mult_v(250,0);
    std::vector<double> l1_totPE_v(250,0);
    std::vector<double> l1_mult_v(250,0);
    for (int ch=0; ch<32; ch++){
      wfm = ( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [ch] );
      nbins = wfm.size();
      //remove baselines (baseline here are determined by the start of the waveform)
      Remove_Baseline_Leading_Edge(&wfm);
      Remove_Baseline_Secondary(&wfm);
      inverse_res1[ch] = Deconvolve(wfm);
      beam_dt[ch] = wfm.get_time_from_trigger();

      //totPE mult, and their l1 versions are additive (each element is always +=). Each iteration of ch will add to these values.
      Perform_L1( inverse_res1[ch],
                  decon_v,
                  &totPE_v,
                  &mult_v,
                  &l1_totPE_v,
                  &l1_mult_v,
                  ch);
      //std::cout << totPE_v.at(249) << " Total PE in spot 249 after " << ch << " channels\n";
    }//End of 32 Channel Forloop

    //BEGIN FLASH CODE
    // Now working on the flashes ...
      // [-2,78)

      std::vector<int> flash_time;
      flash_time.reserve(250);
      std::vector<double> flash_pe;


      double prev_pe_a[32];
      double curr_pe_a[32];

      for (int i=0;i!=250;i++){
        double pe = totPE_v.at(i);
        double mult = mult_v.at(i);
        // careteria: multiplicity needs to be higher than 3, PE needs to be higher than 6
        //std::cout << pe << " " << mult << std::endl;
        if (pe >= 6 && mult >= 3){
          bool flag_save = false;
          if (flash_time.size()==0){
    	       flag_save = true;
    	       for (int j=0;j!=32;j++){
    	          prev_pe_a[j] = decon_v[j].at(i);
    	       }
          }
          else{
    	       for (int j=0;j!=32;j++){
                curr_pe_a[j] = decon_v[j].at(i);
    	       }
    	       if (i - flash_time.back() >= 78){
    	          flag_save = true;
    	  // start one, and open a window of 8 us, if anything above it, not the next 2 bin
    	  // if find one is bigger than this, save a flash ... start a new flash?
             }
             else if (i-flash_time.back() > 4 && pe > flash_pe.back()){
    	          if (i-flash_time.back()>15){
    	             flag_save = true;
    	          }
                else{
                   if (KS_maxdiff(32,prev_pe_a,curr_pe_a) > 0.1){
    	               flag_save = true;
    	             }


    	          }
    	       }

             for (int j=0;j!=32;j++){
                prev_pe_a[j] = decon_v[j].at(i);
    	       }
          }

          if (flag_save){
            	flash_time.push_back(i);
            	flash_pe.push_back(pe);
          }
          else{
    	       if (i - flash_time.back()<=6 && pe > flash_pe.back())
               {
               flash_pe.back()=pe;
             }
          }
        }
      }

       // std::cout << flash_time.size() << " " << flash_pe.size() << std::endl;
       // for a flash, examine the L1 one to decide if add in more time ...?

      for (size_t i=0; i!=flash_time.size(); i++){
        //std::cout << flash_time.at(i) << " " << flash_pe.at(i) << std::endl;
        int start_bin = flash_time.at(i)-2;
        if (start_bin <0) start_bin = 0;

        int end_bin = start_bin + 78; // default
        if (end_bin > 250) end_bin = 250;
        if (i+1<flash_time.size()){
          if (end_bin > flash_time.at(i+1)-2) {
            end_bin = flash_time.at(i+1)-2;
          }
        }
        //  std::cout << start_bin << " " << end_bin << std::endl;
        //check with the next bin content ...

        Opflash *flash = new Opflash(decon_v, beam_dt[0], start_bin, end_bin);
        flash->Add_l1info(&l1_totPE_v, &l1_mult_v, beam_dt[0], start_bin, end_bin);
        // std::cout << flash->get_time() << " " <<flash->get_total_PE() << " " << flash->get_num_fired() << std::endl;
        beam_flashes.push_back(flash);



        // //Start COSMICS flash section - to do this, I think we need the hitfinder first
        // // -see how cosmic_flashes is defined in ToyLightReco (K)

        // Opflash *prev_cflash = 0;
        //
        // for (size_t i=0; i!=cosmic_flashes.size();i++){
        //   Opflash *cflash = cosmic_flashes.at(i);
        //   //std::cout << cflash->get_time() << std::endl;
        //   bool save = true;
        //   for (size_t j=0; j!=beam_flashes.size();j++){
        //     Opflash *bflash = beam_flashes.at(j);
        //     if (cflash->get_time() >= bflash->get_low_time() && cflash->get_time() <= bflash->get_high_time())
        //       {
        //       save = false;
        //       break;
        //     }
        //   }
        //   if (save){
        //     flashes.push_back(cflash);
        //     if (prev_cflash==0 ){
        //       if (cflash->get_time()<0)
        //         {
        //         prev_cflash = cflash;
        //       }
        //     }
        //     else{
        //       if (cflash->get_time() < 0 && cflash->get_time() > prev_cflash->get_time())
        //         {
        //         prev_cflash = cflash;
        //       }
        //     }
        //   }
        // }
        // for (size_t j=0; j!=beam_flashes.size();j++){
        //   Opflash *bflash = beam_flashes.at(j);
        //   if (prev_cflash!=0){
        //
        //     //std::cout << prev_cflash->get_time() << std::endl;
        //     if (bflash->get_time() - prev_cflash->get_time() < 2.4 && // veto for 3 us
        //               bflash->get_total_PE() < 0.7 * prev_cflash->get_total_PE())
        //               {continue;}
        //     // std::cout << bflash->get_time() << " " << prev_cflash->get_time() << " " << bflash->get_total_PE() << " " << prev_cflash->get_total_PE() << std::endl;
        //   }
        //   flashes.push_back(bflash);
        // }
        // // std::cout << cosmic_flashes.size() << " " << beam_flashes.size() << " " << flashes.size() << std::endl;
        // //END COSMIC FLASH SECTION




      }


    //END FLASH CODE


    testPlot("Deconv_ours", inverse_res1[0]);
    testPlot("mult_v", mult_v);
    testPlot("l1_mult_v", l1_mult_v);
    testPlot("totPE_v", totPE_v);
    testPlot("l1_totPE_v", l1_totPE_v);

  }//End of Deconv_test

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

   void deconvolver::Perform_L1(std::vector<double> inverse_res1,
                                std::vector<double> decon_v[32],
                                std::vector<double> *totPE_v,
                                std::vector<double> *mult_v,
                                std::vector<double> *l1_totPE_v,
                                std::vector<double> *l1_mult_v,
                                int ch
                                )
   {

     // prepare L1 fit ...
     std::vector<float> rebin_v;
     rebin_v.resize(250);
     // TH1F *rrebin = new TH1F("hrebin","hrebin",250,0,250);

     for (int i=0;i!=250;i++){
       // hrebin->SetBinContent(i+1,
 			//        fb->GetBinContent(6*i+1) +
 			//        fb->GetBinContent(6*i+2) +
 			//        fb->GetBinContent(6*i+3) +
 			//        fb->GetBinContent(6*i+4) +
 			//        fb->GetBinContent(6*i+5) +
 			//        fb->GetBinContent(6*i+6) );

       rebin_v[i] = inverse_res1.at(6*i) +
                   inverse_res1.at(6*i+1) +
                   inverse_res1.at(6*i+2) +
                   inverse_res1.at(6*i+3) +
                   inverse_res1.at(6*i+4) +
                   inverse_res1.at(6*i+5) ;
     }
     // std::vector<double> decon_v;
     decon_v[ch].resize(250);
     for (int i=0;i!=250;i++){
       // hdecon[j]->SetBinContent(i+1,hrebin->GetBinContent(i+1));
       decon_v[ch].at(i) = rebin_v[i];
     }


     // work on the L1 ...
     std::vector<double> vals_y;
     std::vector<double> vals_x;
     std::vector<int> vals_bin;

     for (int i=0;i!=250;i++){
       double content = rebin_v[i];
       if (content>0.3){
       	vals_y.push_back(content);
       	vals_x.push_back(i+0.5);
       	vals_bin.push_back(i);

       	// global_vals_y.push_back(content);
       	// global_vals_x.push_back(hrebin->GetBinCenter(i+1));
       	// global_vals_bin.push_back(i);
       	// global_vals_pmtid.push_back(j);
       }
     }

     int nbin_fit = vals_x.size();
     Eigen::VectorXd W = Eigen::VectorXd::Zero(nbin_fit);
     Eigen::MatrixXd G = Eigen::MatrixXd::Zero(nbin_fit,nbin_fit);
     for (int i=0;i!=nbin_fit;i++){
         W(i) = vals_y.at(i) / sqrt(vals_y.at(i));
         double t1 = vals_x.at(i); // measured time
         for (int k=0;k!=nbin_fit;k++){
           	double t2 = vals_x.at(k); // real time
           	if (t1>t2) {
             	  G(i,k) = (0.75 * (exp(-((t1-t2)*6*15.625/1000.-3*15.625/1000.)/1.5)-exp(-((t1-t2)*6*15.625/1000.+3*15.625/1000.)/1.5))) / sqrt(vals_y.at(i));
           	}
             else if (t1==t2){
             	  G(i,k) = (0.25 + 0.75 *(1-exp(-3*15.625/1000./1.5))) / sqrt(vals_y.at(i));
           	}
             else{
             	  continue;
           	}
         }
     }

     double lambda = 5;//1/2.;
     wcopreco::LassoModel m2(lambda, 100000, 0.05);
     m2.SetData(G, W);
     m2.Fit();
     Eigen::VectorXd beta = m2.Getbeta();
     //Make vector to hold L1 fit values
     std::vector<double> l1_v;
     l1_v.resize(250);
     for (int i=0;i!=nbin_fit;i++){
         // hl1[j]->SetBinContent(vals_bin.at(i)+1,beta(i));
         l1_v[vals_bin.at(i)] = beta(i);
     }

     // testPlot("L1test", l1_v);

     for (int j=0;j!=250;j++){
       double content = decon_v[ch].at(j);
       if (content >0.2) {
           // h_totPE->SetBinContent(j+1,h_totPE->GetBinContent(j+1) + content);
           totPE_v->at(j)= totPE_v->at(j) + content;
         }
       if (content > 1.5) {// ~2 PE threshold ...
           mult_v->at(j)= mult_v->at(j) + 1 ;
           // h_mult->SetBinContent(j+1,h_mult->GetBinContent(j+1)+1);
         }

       // content = hl1[i]->GetBinContent(j+1);
       content = l1_v.at(j);
       // h_l1_totPE->SetBinContent(j+1,h_l1_totPE->GetBinContent(j+1)+content);
       l1_totPE_v->at(j) = l1_totPE_v->at(j) + content;
       if (content > 1) {// 1 PE threshold
           // h_l1_mult->SetBinContent(j+1,h_l1_mult->GetBinContent(j+1)+1);
             l1_mult_v->at(j) = l1_mult_v->at(j) +1;
         }
       }

   }

   void deconvolver::testPlot(std::string Title, std::vector<double> input){
     //makes a hsitogram in root to test output and saves as png
     TCanvas *c1 = new TCanvas(Title.c_str(), Title.c_str(), 600, 400);
     int nbins = input.size();
     TH1D * hist = new TH1D(Title.c_str() ,Title.c_str(), nbins, 0., (double) nbins);
     for (int i=0; i<nbins; i++) {
       hist->SetBinContent(i,input.at(i));
       //std::cout << mag_raw.at(i) << " :Value of wfm_pow" << std::endl;
     }
     hist->Draw();
     c1->SaveAs((Title + ".png").c_str());
     delete hist;
     delete c1;
     return;
   }

   double deconvolver::KS_maxdiff(int n, double *array1, double *array2){

     for (int index =1; index<n; index++){
       array1[index] += array1[index-1];
       array2[index] += array2[index-1];
     }
     double maxdiff=0;
     double thisdiff=0;
     for (int index=0; index<n; index++){
       array1[index] = array1[index]/array1[n-1];
       array2[index] = array2[index]/array2[n-1];
       thisdiff =fabs(array1[index]-array2[index]);
       if (thisdiff > maxdiff) {maxdiff = thisdiff;}
       // std::cout << prev_pe_a[index] << " Prev PE " << index << "    " << curr_pe_a[index]<< " Curr PE\n";
     }
     return maxdiff;
   }

   std::vector<double> deconvolver::Deconvolve(OpWaveform wfm) {
     //BEGIN DECONVOLUTION MARKER
     std::vector<double> wfm_doubles(wfm.begin(), wfm.end());
     float bin_width = (1.0/(64e6) );
     int nbins = wfm.size();

     // testPlot("raw_data", wfm_doubles);

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

       }
       phase_raw.at(i) = ph;
       //End of phase_raw calc

       //Calculate the mag_v
       double magnitude = TMath::Sqrt(re[i]*re[i]+im[i]*im[i]);
       mag_raw[i] = magnitude;
       //if (i%50 == 0) std::cout<<"Magnitude is " << mag_raw[i] <<std::endl;
       //End of mag_v calc
     }



     delete fftr2c;
     double max_freq_MHz = 64*1500*2*TMath::Pi();

     // testPlot("wfm_mag", mag_raw);
     // testPlot("wfm_phase", phase_raw);



     std::string word = "SPE_wfm" ;
  


     // std::cout << op_gain->at(wfm.get_ChannelNum()) << " Is gain of the channel!";
     UB_spe spe(word, true, op_gain.at(wfm.get_ChannelNum()));
     // spe.gain = 1;

     std::vector<double> mag_spe;
     std::vector<double> phase_spe;

     spe.Get_pow_spec(nbins,bin_width,&mag_spe,&phase_spe);

     std::string word2 = "RC_Wfm";
     UB_rc rc(word2,true);

     std::vector<double> vec_rc = rc.Get_wfm(nbins,bin_width);


     std::vector<double> mag_rc;
     std::vector<double> phase_rc;

     rc.Get_pow_spec(nbins,bin_width,&mag_rc,&phase_rc);


     double value_re[nbins];
     double value_im[nbins];
     double value_re1[nbins];
     double value_im1[nbins];

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
     };
     delete ifft;

     // calcumate rms and mean ...
     std::pair<double,double> results = cal_mean_rms(inverse_res, nbins);
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
     // std::vector<short> shortvec(inverse_res1.begin(), inverse_res1.end());
     // OpWaveform output(wfm.get_type(), wfm.get_time_from_trigger(), wfm.get_type(), shortvec);

     //END OF DECONVOLUTION
     return inverse_res1;
   }

}
