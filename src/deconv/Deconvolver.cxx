#include "Deconvolver.h"

namespace wcopreco {


  wcopreco::Deconvolver::Deconvolver(OpWaveformCollection *merged_beam, bool standard_run, bool with_filters){
    std::cout << "Starting the deconvolution of a waveform collection!\n";


    int type = merged_beam->at(0).get_type();
    op_gain = merged_beam->get_op_gain();
    kernel_container_v.resize(32);
    filter_status = with_filters;
    if (filter_status) {std::cout << "You filtered out latelight and High Frequencies\n";}
    else {std::cout << "You performed the deconvolution without filters\n";}


    //Default way to construct the deconvolver is with spe and rc
    if (standard_run){
      //Construct the vector of kernel containers (one container per channel)
      UB_rc *rc = new UB_rc(true);
      for (int i =0 ; i<32; i++){
        UB_spe *spe = new UB_spe(true, op_gain.at(i)); //Place UB_spe on heap, so object not deleted
        kernel_container_v.at(i).add_kernel(spe);
        kernel_container_v.at(i).add_kernel(rc);
      }
    }

  }



  OpWaveformCollection wcopreco::Deconvolver::Deconvolve_Collection(OpWaveformCollection * merged_beam)

    {

      //Process the Beam:
      //Note that the following code is supposed to only deal with beam waveforms, 32 channels and 1500 bin wfms.
      OpWaveform wfm(0,0,0,0);

      for (int ch=0; ch<32; ch++){
        wfm = merged_beam->at(ch);
        nbins = wfm.size();

        //remove baselines (baseline here are determined by the start of the waveform)
        Remove_Baseline_Leading_Edge(&wfm);
        Remove_Baseline_Secondary(&wfm);

        //Do deconvolution (need to add a way to incorporate kernels)
        deconvolved_collection.add_waveform(Deconvolve_One_Wfm(wfm, kernel_container_v.at(wfm.get_ChannelNum())));

        }
    return deconvolved_collection;
    }//End of Deconvolve_Collection


    void Deconvolver::add_kernel_container_entry(kernel_fourier *kernel, int channel) {

      //If channel is ommitted from the function arguments then we add the kernel to all
      if (channel <0) {
        for (int i =0 ; i<32; i++){
          kernel_container_v.at(i).add_kernel(kernel);
        }
      }
      else if (channel < 32) {
        kernel_container_v.at(channel).add_kernel(kernel);
      }
      else
      {std::cout << "You're asking to add a kernel to a nonexistant channel. Options are 0-31 for individual beam channels or input channel < 0 to apply to all channels\n";}

    }

    //toy light reco f2
    double Deconvolver::HighFreqFilter(double frequency)
    {
      double par_0 = 0.45;
      double par_1 = 3.07;
       //   TF1 f2("f2","exp(-pow(x/[0],[1]))",0,1); // high frequency filter
      double freq_filter = exp(-pow(frequency/par_0,par_1));
      return freq_filter;
    }

    //toy light reco f3
    double Deconvolver::LateLightFilter(double frequency2)
    {
      //   TF1 f3("f3","(1-exp(-pow(x/[0],2)))*exp(-pow(x/[1],[2]))",0,1);

      double par_0 = 0.05;
      double par_1 = 0.45;
      double par_2 = 3.07;

      double latelight_filter = (1-exp(-pow(frequency2/par_0,2)))*exp(-pow(frequency2/par_1,par_2));
      return latelight_filter;
     }

     void Deconvolver::Remove_Baseline_Leading_Edge(OpWaveform *wfm)
     {
       int size = wfm->size();
       double baseline = wfm->at(0);
       for (int i=0; i<size; i++) {
         wfm->at(i) = wfm->at(i) - baseline;
       }
       return;
     }

     void Deconvolver::Remove_Baseline_Secondary(OpWaveform *wfm)
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

     std::pair<double,double> Deconvolver::cal_mean_rms(std::vector<double> wfm, int nbin)
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


     void Deconvolver::testPlot(std::string Title, std::vector<double> input){
       //makes a hsitogram in root to test output and saves as png
       TCanvas *c1 = new TCanvas(Title.c_str(), Title.c_str(), 600, 400);
       int nbins = input.size();
       TH1D * hist = new TH1D(Title.c_str() ,Title.c_str(), nbins, 0., (double) nbins-1);
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
     void Deconvolver::testPlot(std::string Title, OpWaveform input){
       //makes a hsitogram in root to test output and saves as png
       TCanvas *c1 = new TCanvas(Title.c_str(), Title.c_str(), 600, 400);
       int nbins = input.size();
       TH1D * hist = new TH1D(Title.c_str() ,Title.c_str(), nbins, 0., (double) nbins-1);
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

     double Deconvolver::KS_maxdiff(int n, double *array1, double *array2){

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

     OpWaveform Deconvolver::Deconvolve_One_Wfm(OpWaveform wfm, kernel_fourier_container kernel_container) {
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


       double value_re[nbins];
       double value_im[nbins];
       double value_re1[nbins];
       double value_im1[nbins];

       //Set up the kernels to be deconvolved out:


      int channel = wfm.get_ChannelNum();
      int num_kernels = kernel_container_v.at(channel).size();
      std::vector<std::vector<double>> mag_kernel;
      mag_kernel.resize(num_kernels);
      std::vector<std::vector<double>> phase_kernel;
      phase_kernel.resize(num_kernels);


      for (int n=0; n < num_kernels; n++ ) {
        kernel_container_v.at(channel).at(n) ->Get_pow_spec(nbins, bin_width, &mag_kernel.at(n), &phase_kernel.at(n));

      }


       for (int i=0;i<nbins;i++){
         double freq;
         if (i<=750){
     	     freq = ((double)i/(double)nbins*2.)*1.0;
         }
         else{
     	     freq = (((double)nbins-(double)i)/(double)nbins*2.)*1.0;
         }





         double rho = mag_raw.at(i);
         double phi = phase_raw.at(i);
         for (int n=0;n<num_kernels;n++){
           rho = rho / mag_kernel.at(n).at(i);
           phi = phi - phase_kernel.at(n).at(i);
         }

         // if (i%100 ==0) {
         //   std::cout << rho << "                rho                 \n" ;//<< rho2 << "            rho2                  \n";
         //   std::cout << phi << "                phi                 \n" ;//<< phi2 << "            phi2                  \n";
         //
         // }

         //double rho = mag_raw.at(i);
         //double phi = phase_raw.at(i);

         if (i==0) rho = 0;
         //Perform Decon with Filters
         if (filter_status){
           value_re[i] = rho * (cos(phi)/nbins)*2 * LateLightFilter(freq);
           value_im[i] = rho * (sin(phi)/nbins)*2 * LateLightFilter(freq);
           value_re1[i] = rho * (cos(phi)/nbins)*2 * HighFreqFilter(freq);
           value_im1[i] = rho * (sin(phi)/nbins)*2 * HighFreqFilter(freq);
         }
         //Perform Decon without Filters
         else{
           value_re[i] = rho * (cos(phi)/nbins)*2 ;
           value_im[i] = rho * (sin(phi)/nbins)*2 ;
           value_re1[i] = rho * (cos(phi)/nbins)*2 ;
           value_im1[i] = rho * (sin(phi)/nbins)*2 ;
         }

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

       OpWaveform inverse_res1(channel,wfm.get_time_from_trigger(), wfm.get_type(), nbins);
       // inverse_res1.resize(nbins);
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

     void Deconvolver::clear_kernels() {
       for (int i=0; i< kernel_container_v.size() ; i++) {
         kernel_container_v.at(i).clear_kernels_v();
       }
     }

}
