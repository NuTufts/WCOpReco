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
  // clock_t t;
  // t = clock();
  std::cout << "Hello world" << std::endl;
  const char* file = "../celltree.root";
  //testing ToyLightReco

  bool do_loop = false;
<<<<<<< HEAD
  int i = 22;
=======
  int i = 16;
>>>>>>> d5e8eb39ba9dc0c42446dd5f882916cf2e3bfd6a
  int size = i+1;
  if (do_loop)
  {
    i =0;
    size =52;
  }

  // //make root file of outputs to test
  TFile output("WCOutput.root", "RECREATE");
  //create TTree
  TTree *OpReco = new TTree("OpReco", "A tree to hold outputs from OpReco");

  //TClonesArray *Tmerged_beam = new TClonesArray;
  //OpReco->Branch("merged_beam", "TClonesArray", &Tmerged_beam);
  TH1D * TtotPE = new TH1D("totPE" ,"totPE", 250, 0., (double) 250);
  OpReco->Branch("totPE", "TH1D", &TtotPE);
  TH1D * Tl1_totPE = new TH1D("l1_totPE" ,"l1_totPE", 250, 0., (double) 250);
  OpReco->Branch("l1_totPE", "TH1D", &Tl1_totPE);
  TH1D * Tmult = new TH1D("mult" ,"mult", 250, 0., (double) 250);
  OpReco->Branch("mult", "TH1D", &Tmult);
  TH1D * Tl1_mult = new TH1D("l1_mult" ,"l1_mult", 250, 0., (double) 250);
  OpReco->Branch("l1_mult", "TH1D", &Tl1_mult);

  // need branches
  // OpReco->Branch("Branch Name", "Class name", &data)
  // merged_cosmic
  // merged_beam after decon
  // std::vector< std::vector<double> > decon_vv;
  // flashes_beam
  // flashes_cosmic
  // flashes

  for (i;i<size;i++)
    {
      // std::cout << "You have chosen to read out event number: " << i << " out of " << size << std::endl << std::endl;

      WireCell2dToy::ToyLightReco flash(file,false);
      flash.load_event_raw(i);


      //saves for root file
      for (int j=0; j<250; j++){
        TtotPE->SetBinContent(j,flash.get_totPE()->GetBinContent(j));
        Tl1_totPE->SetBinContent(j,flash.get_l1_totPE()->GetBinContent(j));
        Tmult->SetBinContent(j,flash.get_mult()->GetBinContent(j));
        Tl1_mult->SetBinContent(j,flash.get_l1_mult()->GetBinContent(j));
      }

<<<<<<< HEAD
      delete c2;
      // delete hist_decon;
      // if (do_loop) std::cout << (clock() - t)*1.0/CLOCKS_PER_SEC<< "\n"; //<< " Time through loop " <<  i<< "\n";
=======
>>>>>>> d5e8eb39ba9dc0c42446dd5f882916cf2e3bfd6a

      // TH1F* hist_raw = flash.get_raw_hist(0);
      //
      // TCanvas *c1 = new TCanvas("raw_wc", "raw_wc", 600, 400);
      // hist_raw->Draw();
      // c1->SaveAs("raw_wc.png");
      // delete c1;
      // // delete hist_raw;
      //
      // TH1F* hist_decon = flash.get_decon_hist(0);
      //
      // TCanvas *c2 = new TCanvas("deconv_wc", "deconv_wc", 600, 400);
      // hist_decon->Draw();
      // c2->SaveAs("deconv_wc.png");
      //
      // delete c2;
      // // delete hist_decon;
      //OpReco->Fill();
  }
<<<<<<< HEAD
  t = clock() - t;
=======
  OpReco->Fill();
  output.Write();
  output.Close();
  // t = clock() - t;
>>>>>>> d5e8eb39ba9dc0c42446dd5f882916cf2e3bfd6a
	// std::cout << "time: " << t*1.0/CLOCKS_PER_SEC << " seconds" << std::endl;
  return 0;
};
