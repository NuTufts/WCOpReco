#ifndef DECONVOLVER_H
#define DECONVOLVER_H

//deconv functions
#include "kernel_fourier.h"
#include "kernel_fourier_container.h"
#include "noise_remover.h"
#include "noise_container.h"
#include "UB_spe.h"
#include "UB_rc.h"
#include "WCOpReco/LassoModel.h"
#include "WCOpReco/ElasticNetModel.h"
#include "WCOpReco/LinearModel.h"
#include "WCOpReco/Opflash.h"
#include "WCOpReco/COphit.h"

//data
#include "WCOpReco/DataReader.h"

//c++ includes
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <Eigen/Dense>

//root
#include "TCanvas.h"

namespace wcopreco{


  class deconvolver {
  public:
    deconvolver() {
      std::cout<< "object" <<std::endl;
    }; //OpWaveform op_wfm, kernel_fourier_shape kernel_fourier, noise_remover noise, std::vector<short???> LL_shape
    ~deconvolver() {};

    void deconv_test();
    double HighFreqFilter(double frequency);
    double BandPassFilter(double frequency2);
    void Remove_Baseline_Leading_Edge(OpWaveform *wfm);
    void Remove_Baseline_Secondary(OpWaveform *wfm);
    std::vector<double> Deconvolve(OpWaveform wfm);
    void Perform_L1(std::vector<double> inverse_res1, std::vector<double> decon_v[32], std::vector<double> *totPE_v, std::vector<double> *mult_v, std::vector<double> *l1_totPE_v, std::vector<double> *l1_mult_v, int ch);
    std::pair<double,double> cal_mean_rms(std::vector<double> wfm, int nbin);
    void testPlot(std::string Title, std::vector<double> input);
    double KS_maxdiff(int n, double *array1, double *array2);
    /*
    The KS_maxdiff function takes two array PDFs of n elements, and transforms
    them into CDFs then it finds the maximum difference between the CDFs and
    returns it.
    */

  protected:
    std::vector<float>  op_gain;
  };

}
#endif
