#include "WCOpReco/OpWaveform.h"
#include "WCOpReco/OpWaveformCollection.h"
#include "WCOpReco/EventOpWaveforms.h"
#include "WCOpReco/UBEventWaveform.h"
#include "WCOpReco/DataReader.h"
#include "WCOpReco/deconvolver.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"
#include "TFile.h"

#include <iostream>
#include <sstream>

int main(){

  std::cout << "Hello world" << std::endl;



  // This tests the reader:
  // std::string file = "src/data/celltree.root";
  // wcopreco::DataReader reader(file);
  // std::cout << "Filepath is set to:   " << file << std::endl;
  // int event_num = 3;
  // reader.Reader(event_num);

  //This tests the deconvolver:
  wcopreco::deconvolver tester;
  std::cout << "Deconvolver declared!" << std::endl;
  tester.deconv_test();




};
