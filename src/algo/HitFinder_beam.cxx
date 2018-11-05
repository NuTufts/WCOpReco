#include "HitFinder_beam.h"

namespace wcopreco {

  wcopreco::HitFinder_beam::HitFinder_beam(OpWaveformCollection deconvolved_beam, std::vector<kernel_fourier_container> &kernel_container_v){
    //main function for beam hit finder

    //perform deconvolution with kernals add and with filters (true,true)
    wcopreco::Deconvolver filtered_wfm(&deconvolved_beam, true, kernel_container_v);
    OpWaveformCollection filtered_collection = filtered_wfm.Deconvolve_Collection(&deconvolved_beam);

    totPE_v.resize(250);
    mult_v.resize(250);
    l1_totPE_v.resize(250);
    l1_mult_v.resize(250);
    decon_vv.resize(32);

    //loop through each channel and perform the l1 fit
    for (int ch=0; ch<32; ch++){
      //totPE mult, and their l1 versions are additive (each element is always +=). Each iteration of ch will add to these values.
      decon_vv.at(ch).reserve(300);
      Perform_L1( filtered_collection.at(ch),
                  decon_vv,
                  totPE_v,
                  mult_v,
                  l1_totPE_v,
                  l1_mult_v,
                  ch);

    }

  }

  void HitFinder_beam::Perform_L1(std::vector<double> inverse_res1,
                               std::vector< std::vector<double> > &decon_vv,
                               std::vector<double> &totPE_v,
                               std::vector<double> &mult_v,
                               std::vector<double> &l1_totPE_v,
                               std::vector<double> &l1_mult_v,
                               int ch
                               )
  {
    //function to perform L1

    // prepare L1 fit ...
    std::vector<float> rebin_v;
    rebin_v.resize(250);

    for (int i=0;i!=250;i++){
      rebin_v[i] = inverse_res1.at(6*i) +
                  inverse_res1.at(6*i+1) +
                  inverse_res1.at(6*i+2) +
                  inverse_res1.at(6*i+3) +
                  inverse_res1.at(6*i+4) +
                  inverse_res1.at(6*i+5) ;
    }

    decon_vv[ch].resize(250);
    for (int i=0;i!=250;i++){
      decon_vv[ch].at(i) = rebin_v[i];
    }

    // work on the L1 ...
    std::vector<double> vals_y;
    std::vector<double> vals_x;
    std::vector<int> vals_bin;

    //save bin content if > threshold of .3
    for (int i=0;i!=250;i++){
      double content = rebin_v[i];
      if (content>0.3){
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
          totPE_v.at(j)= totPE_v.at(j) + content;
        }
      if (content > 1.5) {// ~2 PE threshold ...
          mult_v.at(j)= mult_v.at(j) + 1 ;
        }

      content = l1_v.at(j);

      l1_totPE_v.at(j) = l1_totPE_v.at(j) + content;
      if (content > 1) {// 1 PE threshold
          l1_mult_v.at(j) = l1_mult_v.at(j) + 1;
        }
      }
  }

}
