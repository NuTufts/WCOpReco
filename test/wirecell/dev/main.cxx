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
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"

#include "../ToyLightReco.h"

using namespace WireCell;
using namespace std;


int main(){
  std::cout << "Hello world" << std::endl;
  const char* file = "../celltree.root";
  //testing ToyLightReco
  WireCell2dToy::ToyLightReco flash(file,false);
  flash.load_event_raw(4);
  TH1F* hist_raw = flash.get_raw_hist(0);

  TCanvas *c1 = new TCanvas("raw_wc", "raw_wc", 600, 400);
  hist_raw->Draw();
  c1->SaveAs("raw_wc.png");
  delete c1;
  delete hist_raw;

  TH1F* hist_decon = flash.get_decon_hist(0);

  TCanvas *c2 = new TCanvas("deconv_wc", "deconv_wc", 600, 400);
  hist_decon->Draw();
  c1->SaveAs("deconv_wc.png");
  delete c2;
  delete hist_decon;



};
