#include "HitFinder_beam.h"

namespace wcopreco {

  wcopreco::HitFinder_beam::HitFinder_beam(OpWaveformCollection deconvolved_beam){
    //Module for hit finding for beam
    // loop through all 32 channels of collection, fft with filters, ifft, and perform L1 fit

    //need to call deconvolver with no kernels (should aready have been taken into account in deconvolution step)
    //include HighFreqFilter and LateLight filter for UB, but can add in different or additional functions if desired.
    wcopreco::Deconvolver filtered_wfm(&deconvolved_beam, true, true);
    OpWaveformCollection filtered_collection = filtered_wfm.Deconvolve_Collection(&deconvolved_beam);

    totPE_v.resize(250);
    mult_v.resize(250);
    l1_totPE_v.resize(250);
    l1_mult_v.resize(250);
    decon_vv.resize(32);

    for (int ch=0; ch<32; ch++){
      //totPE mult, and their l1 versions are additive (each element is always +=). Each iteration of ch will add to these values.
      decon_vv.at(ch).reserve(300);
      channel =ch;
      // std::cout << ch << "  ";
      Perform_L1( filtered_collection.at(ch),
                  decon_vv,
                  &totPE_v,
                  &mult_v,
                  &l1_totPE_v,
                  &l1_mult_v,
                  ch);


      //std::cout << totPE_v.at(249) << " Total PE in spot 249 after " << ch << " channels\n";
    }


  }

  void HitFinder_beam::Perform_L1(std::vector<double> inverse_res1,
                               std::vector< std::vector<double> > &decon_vv,
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
    // if (ch==1){
    //   for (int p=0;p<1500;p++){
    //     std::cout << inverse_res1.at(p) << "\n";
    //   }
    // }

    for (int i=0;i!=250;i++){
      rebin_v[i] = inverse_res1.at(6*i) +
                  inverse_res1.at(6*i+1) +
                  inverse_res1.at(6*i+2) +
                  inverse_res1.at(6*i+3) +
                  inverse_res1.at(6*i+4) +
                  inverse_res1.at(6*i+5) ;
                  // if (i == 0||i==1 ||i==3) {
                  //   std::cout << ch << "\n";
                  //
                  //   // std::cout << inverse_res1.at(6*i) << " PrePooled 0" <<  "\n";
                  //   for (int num=0;num<6;num++){
                  //     std::cout << inverse_res1.at(6*i+num) << " PrePooled "<<num+i*6 <<  "\n";
                  //   }
                  //
                  //
                  //   std::cout <<"\n"<< rebin_v[i] << " Is total in bin "<<i<<"\n";
                  // }
                  // if (rebin_v[i] > 0.1) {std::cout << rebin_v[i] << " Value in bin "<<i<< " for channel " << ch << "\n";}

    }

    decon_vv[ch].resize(250);
    for (int i=0;i!=250;i++){
      decon_vv[ch].at(i) = rebin_v[i];
    }


    // work on the L1 ...
    std::vector<double> vals_y;
    std::vector<double> vals_x;
    std::vector<int> vals_bin;

    for (int i=0;i!=250;i++){
      double content = rebin_v[i];
      // if (ch==1 && (i==166 || i==168 || i==173 || i==193 || i==196 || i==224 ||i==231 ||i==239 ))
      //   {std::cout << i << " " << content << " \n";}
      if (content>0.3){
        // if (ch < 6) std::cout << ch << " " << i << " \n";

       vals_y.push_back(content);
       vals_x.push_back(i+0.5);
       vals_bin.push_back(i);
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

    double lambda = 5;
    wcopreco::LassoModel m2(lambda, 100000, 0.05);
    m2.SetData(G, W);
    m2.Fit();
    Eigen::VectorXd beta = m2.Getbeta();

    //Make vector to hold L1 fit values
    std::vector<double> l1_v;
    l1_v.resize(250);
    for (int i=0;i!=nbin_fit;i++){
        l1_v[vals_bin.at(i)] = beta(i);
    }


    for (int j=0;j!=250;j++){
      double content = decon_vv[ch].at(j);

      if (content >0.2) {;
          totPE_v->at(j)= totPE_v->at(j) + content;
        }
      if (content > 1.5) {// ~2 PE threshold ...
          mult_v->at(j)= mult_v->at(j) + 1 ;
        }

      content = l1_v.at(j);
      // if (j ==41) std::cout << content << " content\n";
      // if (j ==41) std::cout << content<< "\n" ;

      l1_totPE_v->at(j) = l1_totPE_v->at(j) + content;
      if (content > 1) {// 1 PE threshold
          l1_mult_v->at(j) = l1_mult_v->at(j) + 1;
        }
      }
  }

}
