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
  const char* file = "../../../celltreeDATA_bnb.root";
  //testing ToyLightReco

  int size = 1;

  // //make root file of outputs to test

  TFile* output = new TFile("WCOutput.root", "RECREATE");
  //create TTree
  TTree *OpReco = new TTree("OpReco", "A tree to hold outputs from OpReco");
  double totPE;
  double time;
  int type;
  OpReco->Branch("totPE",&totPE);
  OpReco->Branch("time",&time);
  OpReco->Branch("type",&type);
  //TClonesArray *Tmerged_beam = new TClonesArray;
  //OpReco->Branch("merged_beam", "TClonesArray", &Tmerged_beam);
  //OpReco->Branch("totPE", "TH1D", &TtotPE);
  //OpReco->Branch("l1_totPE", "TH1D", &Tl1_totPE);
  //OpReco->Branch("mult", "TH1D", &Tmult);
  //OpReco->Branch("l1_mult", "TH1D", &Tl1_mult);
  TH1F* TtotPE;
  TH1F* Tl1_totPE;
  TH1F* Tmult;
  TH1F* Tl1_mult;
  TH1F* hdeconv[32];

  // need branches
  // OpReco->Branch("Branch Name", "Class name", &data)
  // merged_cosmic
  // merged_beam after decon
  // std::vector< std::vector<double> > decon_vv;
  // flashes_beam
  // flashes_cosmic
  // flashes

  for (int i;i<size;i++)
    {
      // std::cout << "You have chosen to read out event number: " << i << " out of " << size << std::endl << std::endl;

      WireCell2dToy::ToyLightReco flashreco(file,false);
      flashreco.load_event_raw(i);

      //saves for root file
      output->cd();
      WireCell::OpflashSelection flashes = flashreco.get_flashes();
      TtotPE = (TH1F*)flashreco.get_totPE();
      Tl1_totPE = (TH1F*)flashreco.get_l1_totPE();
      Tmult = (TH1F*)flashreco.get_mult();
      Tl1_mult = (TH1F*)flashreco.get_l1_mult();
      for(int j=0; j<32; j++){
	hdeconv[j] = (TH1F*)flashreco.get_decon_hist(j);
	hdeconv[j]->Write(Form("hdeconv_%d",j));
      }

      for(unsigned int i=0; i<flashes.size(); i++){
      //cout << flashes.at(i)->get_total_PE() << endl; 
	totPE = flashes.at(i)->get_total_PE();
	time = flashes.at(i)->get_time();
	type = flashes.at(i)->get_type();
	OpReco->Fill();
      }
      OpReco->Write();
      TtotPE->Write("totPE");
      Tl1_totPE->Write("l1_totPE");
      Tmult->Write("mult");
      Tl1_mult->Write("l1_mult");
    }

  t = clock() - t;

  //OpReco->Fill();
  //output->Write();
  output->Close();
  // t = clock() - t;
	// std::cout << "time: " << t*1.0/CLOCKS_PER_SEC << " seconds" << std::endl;
  return 0;
};
