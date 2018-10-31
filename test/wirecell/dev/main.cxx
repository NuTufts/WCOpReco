#include <iostream>
#include <sstream>
#include <string>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

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
  clock_t t;
  t = clock();
  std::cout << "Hello world" << std::endl;
  const char* file = "../celltree.root";
  //testing ToyLightReco

  bool do_loop = true;
  int i = 16;
  int size = i+1;
  if (do_loop)
  {
    i =0;
    size =52;
  }

  for (i;i<size;i++)
    {
      // std::cout << "You have chosen to read out event number: " << i << " out of " << size << std::endl << std::endl;

      WireCell2dToy::ToyLightReco flash(file,false);
      flash.load_event_raw(i);

      TH1F* hist_raw = flash.get_raw_hist(0);

      TCanvas *c1 = new TCanvas("raw_wc", "raw_wc", 600, 400);
      hist_raw->Draw();
      c1->SaveAs("raw_wc.png");
      delete c1;
      // delete hist_raw;

      TH1F* hist_decon = flash.get_decon_hist(0);

      TCanvas *c2 = new TCanvas("deconv_wc", "deconv_wc", 600, 400);
      hist_decon->Draw();
      c2->SaveAs("deconv_wc.png");

      delete c2;
      // delete hist_decon;

  }
  t = clock() - t;
	std::cout << "time: " << t*1.0/CLOCKS_PER_SEC << " seconds" << std::endl;
  return 0;
};
