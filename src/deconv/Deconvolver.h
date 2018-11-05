#ifndef DECONVOLVER_H
#define DECONVOLVER_H

//deconv functions
#include "kernel_fourier.h"
#include "kernel_fourier_container.h"
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
#include "TLine.h"

namespace wcopreco{
  /*
  This class is microboone specific in its constructor. It allows for the deconvolution
  of a user controlled number of kernels, where kernel_container_v is a vector of
  kernel containers where each the indice of the vector gets applied to a corresponding channel.
  If standard_run ==true then the constructor builds a UB kernel_container_v with
  spe and RC kernels applied to each channel.
  */
  class Deconvolver {
  public:
    Deconvolver(OpWaveformCollection *merged_beam, bool standard_run, bool with_filters); //OpWaveform op_wfm, kernel_fourier_shape kernel_fourier, noise_remover noise, std::vector<short???> LL_shape
    ~Deconvolver() {};

    //Kernel manipulating functions
    std::vector<kernel_fourier_container> get_kernel_container_v() {return kernel_container_v;}
    kernel_fourier_container get_kernel_container_entry(int channel) {return kernel_container_v.at(channel);}
    void add_kernel_container_entry(kernel_fourier *kernel, int channel =-1);
    void clear_kernels();


    void set_filter_status(bool status) {filter_status = status;}
    OpWaveformCollection Deconvolve_Collection(OpWaveformCollection * merged_beam);
      /*
      This function takes a collection of beam waveforms and deconvolves them using the
      kernels loaded into kernel_container_v. It calls the remove baseline functions
      and the Deconvolve_One_Wfm on each waveform in merged_beam
      */
    double HighFreqFilter(double frequency);
    double LateLightFilter(double frequency2);
    void Remove_Baseline_Leading_Edge(OpWaveform *wfm);
    void Remove_Baseline_Secondary(OpWaveform *wfm);
    OpWaveform Deconvolve_One_Wfm(OpWaveform wfm, kernel_fourier_container kernel_container);
      //This does the actual deconvolution on an individual waveform
      //Called by Deconvolve_Collection
    std::pair<double,double> cal_mean_rms(std::vector<double> wfm, int nbin);
      //This function calculates the mean and rms values of a waveform for use in the deconvolution
    void testPlot(std::string Title, std::vector<double> input);
    void testPlot(std::string Title, OpWaveform input);
    void testPlot(std::string Title, OpWaveform input, std::vector<double> hits, double threshold);
    void testPlot(std::string Title, OpWaveformCollection inputcollection, Opflash *flash);



    double KS_maxdiff(int n, double *array1, double *array2);
      /*
      The KS_maxdiff function takes two array PDFs of n elements, and transforms
      them into CDFs then it finds the maximum difference between the CDFs and
      returns it.
      */
  protected:
    int nbins;

    bool filter_status;

    std::vector<float>  op_gain;
    std::vector<kernel_fourier_container> kernel_container_v;
    OpWaveformCollection deconvolved_collection;
  };

}
#endif
