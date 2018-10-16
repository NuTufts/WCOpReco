#include <iostream>
#include <sstream>
#include <string>

#include "TApplication.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TFile.h"
#include "TGraph2D.h"
#include "TColor.h"
#include "TVectorD.h"
#include "TMatrixD.h"

#include "../ToyLightReco.h"

using namespace WireCell;
using namespace std;


int main(){
  std::cout << "Hello world" << std::endl;
  const char* file = "celltree.root";
  //testing ToyLightReco
  WireCell2dToy::ToyLightReco flash(file,1);
  flash.load_event_raw(4);
  TH1F* hist_raw = flash.get_raw_hist(0);
  TH1F* hist_decon = flash.get_decon_hist(0);

};
