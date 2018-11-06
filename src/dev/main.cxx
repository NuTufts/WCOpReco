#include "WCOpReco/OpWaveform.h"
#include "WCOpReco/OpWaveformCollection.h"
#include "WCOpReco/EventOpWaveforms.h"
#include "WCOpReco/UBEventWaveform.h"
#include "WCOpReco/DataReader.h"
#include "WCOpReco/Deconvolver.h"
#include "WCOpReco/saturation_merger.h"
#include "WCOpReco/HitFinder_cosmic.h"
#include "WCOpReco/Flashes_cosmic.h"
#include "WCOpReco/Flashes_beam.h"
#include "WCOpReco/HitFinder_beam.h"
#include "WCOpReco/FlashFiltering.h"

#include "WCOpReco/Run.h"

//root includes
#include "TH1S.h"
#include "TF1.h"
#include "TVirtualFFT.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"

#include <iostream>
#include <sstream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

int main(){
  wcopreco::Run opreco;
  wcopreco::OpflashSelection flashes = opreco.get_flashes();
  std::cout << flashes.size() << " :Number of flashes\n";
  wcopreco::OpflashSelection flashes_cosmic = opreco.get_flashes_cosmic();
  std::cout << flashes_cosmic.size() << " :Number of cosmic flashes\n";
  wcopreco::OpflashSelection flashes_beam = opreco.get_flashes_beam();
  std::cout << flashes_beam.size() << " :Number of beam flashes\n";
//   clock_t t;
//   clock_t dataread;
//   clock_t satmerger;
//   clock_t hitsbeam;
//   clock_t flashbeam;
//   clock_t hitscosmic;
//   clock_t flashcosmic;
//   clock_t flashfilter;
//   t=clock();
//
//   std::cout << "Hello world" << std::endl;
//
//   //Set the filepath
//   std::string file = "src/data/celltree.root";
//   std::cout << "\n\nFilepath is set to:   " << file << std::endl;
//
//   //Open the reader, choose event number, create the UBEventWaveform _UB_Ev_wfm
//   wcopreco::DataReader reader(file);
//   wcopreco::UBEventWaveform _UB_Ev_wfm;
//   bool do_loop = true;
//   int EVENT_NUM =22;
//   int size = EVENT_NUM+1;
//
//   if (do_loop){
//     EVENT_NUM=0;
//     size = 52;
//   }
//
//   // //make root file of outputs to test
//   // TFile output("OurOutput.root", "RECREATE");
//   // //create TTree
//   // TTree *OpReco = new TTree("OpReco", "A tree to hold outputs from OpReco");
//   // TClonesArray *Tmerged_beam = new TClonesArray;
//   //
//   // OpReco->Branch("merged_beam", "TClonesArray", &Tmerged_beam);
//   // TH1D * TtotPE = new TH1D("totPE" ,"totPE", 249, 0., (double) 250);
//   // OpReco->Branch("totPE", "TH1D", &TtotPE);
//   // TH1D * Tl1_totPE = new TH1D("l1_totPE" ,"l1_totPE", 249, 0., (double) 250);
//   // OpReco->Branch("l1_totPE", "TH1D", &Tl1_totPE);
//   // TH1D * Tmult = new TH1D("mult" ,"mult", 249, 0., (double) 250);
//   // OpReco->Branch("mult", "TH1D", &Tmult);
//   // TH1D * Tl1_mult = new TH1D("l1_mult" ,"l1_mult", 249, 0., (double) 250);
//   // OpReco->Branch("l1_mult", "TH1D", &Tl1_mult);
//
//   //need branches
//   //OpReco->Branch("Branch Name", "Class name", &data)
//   //merged_cosmic
//   //merged_beam after decon
//   //std::vector< std::vector<double> > decon_vv;
//   //flashes_beam
//   //flashes_cosmic
//   //flashes
//
//   for (EVENT_NUM;EVENT_NUM<size;EVENT_NUM++){
//     _UB_Ev_wfm = reader.Reader(EVENT_NUM);
//     std::vector<float> op_gain = _UB_Ev_wfm.get_op_gain();
//     std::vector<float> op_gainerror = _UB_Ev_wfm.get_op_gainerror();
//     dataread = clock();
//     // std::cout << "\n";
//     // std::cout << _UB_Ev_wfm.get__wfm_v().at(2).size() << " Number of Waveform in Cosmic HG\n";
//     // std::cout << _UB_Ev_wfm.get__wfm_v().at(3).size() << " Number of Waveform in Cosmic LG\n";
//
//
//
//     //create the merger and then get a Merged UBEventWaveform UB_Ev_Merged
//     wcopreco::saturation_merger merger(_UB_Ev_wfm);
//     wcopreco::OpWaveformCollection merged_beam = merger.get_merged_beam(); //This is inside UB_Ev_Merged
//     wcopreco::OpWaveformCollection merged_cosmic = merger.get_merged_cosmic(); //This is inside UB_Ev_Merged
//     wcopreco::UBEventWaveform UB_Ev_Merged = merger.get_merged_UB_Ev();
//     satmerger = clock();
//     //std::cout << UB_Ev_Merged.get__wfm_v().at(5).size() << " Number of Waveform in Cosmic LG\n";
//     //std::cout << UB_Ev_Merged.get__wfm_v().at(5).size() << " Number of Waveform in Cosmic LG\n";
//     // std::cout << UB_Ev_Merged.get__wfm_v().at(5).size() << " Number of Waveform in Cosmic Merged\n";
//     // std::cout << merged_cosmic.size() << " Number of Waveform in Cosmic Merged (CONFIRMED)\n\n";
//
//
//     //add to root output file
//     // for (int j; j<merged_beam.size(); j++){
//     //   int n = merged_beam.at(j).size();
//     //   TH1D * hist = new TH1D("hist" ,"hist", n-1, 0., (double) n);
//     //   for (int k=0; k<n; k++) {
//     //     hist->SetBinContent(k,merged_beam.at(j).at(k));
//     //   }
//     //   //TH1S *h = (TH1S*)wf->At(i)
//     //   //new(Tmerged_beam[j]) TH1D * hist;
//     //   Tmerged_beam->AddAt(hist,j);
//     //   delete hist;
//     // }
//
//
//     //Diagnosis Code -J
//     // for (int i=0; i< 2; i++){
//     //   for (int j=0; j<merged_beam.at(i).size(); j++){
//     //
//     //     if (j%1==0) {std::cout << merged_beam.at(i).at(j) << "   Is value in " << i << " wfm in " << j << " bin\n";}
//     //   }
//     //   std::cout << "\n\n";
//     // }
//
//
//     // Create the Deconvolver (This should just deconvolves the BEAM)
//     // wcopreco::Deconvolver tester(&merged_beam, true, true);
//     // // std::cout << "Deconvolver declared!" << std::endl;
//     // std::vector<wcopreco::kernel_fourier_container> kernel_container_v = tester.get_kernel_container_v();
//     //
//     // wcopreco::OpWaveform wfm = merged_beam.at(0);
//     // std::cout << kernel_container_v.size() << " Size of kernel container_v \n\n\n\n";
//     //
//     //
//     //
//     //
//     // //do beam hitfinding
//     //wcopreco::OpWaveformCollection deconvolved_wfm = tester.Deconvolve_Collection(& merged_beam);
//     wcopreco::HitFinder_beam hits_found_beam(merged_beam);
//     std::vector<double> totPE_v = hits_found_beam.get_totPE_v();
//     std::vector<double> mult_v =hits_found_beam.get_mult_v();
//     std::vector<double> l1_totPE_v =hits_found_beam.get_l1_totPE_v();
//     std::vector<double> l1_mult_v = hits_found_beam.get_l1_mult_v();
//     std::vector< std::vector<double> > decon_vv = hits_found_beam.get_decon_vv();
//     hitsbeam = clock();
//
//     // //root saves
//     // for (int i=0; i<250; i++) {
//     //   TtotPE->SetBinContent(i,totPE_v.at(i));
//     //   Tl1_totPE->SetBinContent(i,l1_totPE_v.at(i));
//     //   Tmult->SetBinContent(i,mult_v.at(i));
//     //   Tl1_mult->SetBinContent(i,l1_mult_v.at(i));
//     // }
//
//     double beam_start_time =merged_beam.at(0).get_time_from_trigger();
//
//
//     wcopreco::Flashes_beam flashfinder_beam( totPE_v, mult_v, l1_totPE_v, l1_mult_v, decon_vv, beam_start_time );
//     wcopreco::OpflashSelection flashes_beam = flashfinder_beam.get_beam_flashes();
//     // std::cout << "\n\n" << flashes_beam.size() << " Beam Flashes in Event\n";
//     flashbeam = clock();
//
//     // //Create the Hitfinder for COSMICS (Currently this also does the flashes for cosmics)
//     wcopreco::HitFinder_cosmic hits_found(&merged_cosmic, &op_gain, &op_gainerror);
//     std::vector<wcopreco::COphitSelection> hits = hits_found.get_ophits_group();
//     hitscosmic = clock();
//
//     wcopreco::Flashes_cosmic flashfinder_cosmic(hits);
//     wcopreco::OpflashSelection flashes_cosmic = flashfinder_cosmic.get_cosmic_flashes();
//     // std::cout << flashes_cosmic.size() << " Cosmic Flashes in Event\n";
//     flashcosmic=clock();
//
//     // std::cout << flashes.size() << " flashes were found in the cosmic selection\n";
//
//     //flash matching
//     wcopreco::FlashFiltering flashesfiltered(flashes_cosmic, flashes_beam);
//     wcopreco::OpflashSelection flashes = flashesfiltered.get_flashes();
//     flashfilter =clock();
//     // std::cout << flashes.size() << " Matched Flashes in Event\n\n";
//     // wcopreco::UB_rc here(true,false);
//     // std::vector<double> magy;
//     // std::vector<double> phasey;
//     // here.Get_pow_spec(1500, (1.0/(64e6) ), &magy, &phasey);
//     // for (int p=0;p<1500;p++){
//     //   std::cout << magy.at(p) << "\n";
//     // }
//     // std::cout << "\n\n-------------------------------------------\n";
//     for (int i =0 ; i<flashes.size(); i++) {
//         if (flashes.at(i)->get_type() ==2) std::cout << flashes.at(i)->get_total_PE() << "\n";
//     }
//
//
//     // Code to test plotting lines on a waveform
//     // wcopreco::Opflash *bflash = flashes_beam.at(0);
//
//     // wcopreco::Deconvolver testplotter(&merged_cosmic, true,true);
//     // std::string  str = "Ev16_Beamflash";
//     // testplotter.testPlot(str , merged_beam, bflash);
//
//       // std::cout << merged_beam.at(i).get_time_from_trigger() << "\n";
//
//
//
//
//     // testplotter.testPlot("Plot With Flash" +(std::string)i,merged_beam.at(i));
//     // if (plottedwfm.get_ChannelNum() ==0) std::cout << "Channel num is 0!\n";
//     // if (do_loop) std::cout << (clock() - t)*1.0/CLOCKS_PER_SEC<<"\n";// << " Time through loop " <<  EVENT_NUM<< "\n";
//   }
// // OpReco->Fill();
// // output.Write();
// // output.Close();
//
//
//
//
//
//
//
//
//   // // // // // // Here is deconvolver test code // // // // // // //
//   // std::cout << "\n";
//   // // Create the Deconvolver (This should just deconvolves the BEAM)
//   // wcopreco::Deconvolver Does_Nothing(&merged_beam, false, false);
//   // // wcopreco::OpWaveformCollection DN = Does_Nothing.Deconvolve_Collection(& merged_beam);
//   //
//   // std::cout << "\n";
//   // // Create the Deconvolver (This should just deconvolves the BEAM)
//   // wcopreco::Deconvolver All_At_Once(&merged_beam, true, true);
//   // wcopreco::OpWaveformCollection AAO = All_At_Once.Deconvolve_Collection(& merged_beam);
//   // std::cout << "\n";
//   //
//   // // create the deconvolver in 2 steps
//   // wcopreco::Deconvolver Step_One(&merged_beam, true, false);
//   // wcopreco::OpWaveformCollection S1 = Step_One.Deconvolve_Collection(& merged_beam);
//   // std::cout << "\n";
//   //
//   // wcopreco::Deconvolver Step_Two(&S1, false, true);
//   // wcopreco::OpWaveformCollection S2 = Step_Two.Deconvolve_Collection(& S1);
//   // std::cout << "\n";
//   //
//   //Remove Baselines from Original
//   // wcopreco::OpWaveform orig = merged_beam.at(0);
//   // All_At_Once.Remove_Baseline_Leading_Edge(&orig);
//   // All_At_Once.Remove_Baseline_Secondary(&orig);
//
//   // Do Nothing Deconvolver
//   // std::vector<wcopreco::kernel_fourier_container> kernel_container_v_dn = Does_Nothing.get_kernel_container_v();
//   // wcopreco::OpWaveform dn = Does_Nothing.Deconvolve_One_Wfm(orig, kernel_container_v_dn.at(orig.get_ChannelNum()));
//
//
//
//
//   // wcopreco::OpWaveform aao = AAO.at(0);
//   // wcopreco::OpWaveform s2 = S2.at(0);
//
//   // All_At_Once.Remove_Baseline_Leading_Edge(&aao);
//   // All_At_Once.Remove_Baseline_Secondary(&aao);
//
//   // All_At_Once.testPlot("Original", orig);
//   // All_At_Once.testPlot("Do Nothing Dec", dn);
//   // All_At_Once.testPlot("All at Once from Collection", aao);
//   // Step_Two.testPlot("Two Step Deconv", s2);
//   //
//   // double difference;
//   // // std::cout << "=================================================\n";
//   // for (int i=0; i<1500;i++){
//   //   // if (i%100 ==0) {
//   //     difference = s2.at(i) - aao.at(i);
//   //     // std::cout << orig.at(i) - dn.at(i) << "\n";
//   //     // std::cout << orig.at(i) << " Original Waveform\n";
//   //     // std::cout << dn.at(i) << " 'Does Nothing' Waveform\n";
//   //     if (difference > 0.05){
//   //       std::cout << difference/aao.at(i)*100.0 << "   Percent difference relative to all at once\n";
//   //       std::cout << aao.at(i) << " All at once method\n";
//   //       std::cout << s2.at(i) << " Two Step\n";
//   //       std::cout << difference << "   Difference\n\n";
//   //     }
//   //   // }
//   // }
//   flashfilter = flashfilter - flashcosmic;
//   flashcosmic = flashcosmic - hitscosmic;
//   hitscosmic  = hitscosmic  - flashbeam;
//   flashbeam   = flashbeam   - hitsbeam;
//   hitsbeam    = hitsbeam    - satmerger;
//   satmerger   = satmerger   - dataread;
//   dataread    = dataread    - t;
//   t = clock() - t;
//
// 	// std::cout << "Total time:           " << t*1.0/CLOCKS_PER_SEC << " seconds" << std::endl << std::endl;
//   // std::cout << "DataRead Time:        " << dataread*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "DataRead Fraction:           " << (double)dataread/t  <<  std::endl << std::endl;
//   // std::cout << "SatMerger Time:       " << satmerger*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "SatMerger Fraction:          " << (double)satmerger/t  <<  std::endl << std::endl;
//   // std::cout << "HitsBeam Time:        " << hitsbeam*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "HitsBeam Fraction:           " << (double)hitsbeam/t  <<  std::endl << std::endl;
//   // std::cout << "Flashbeam Time:       " << flashbeam*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "FlashBeam Fraction:          " << (double)flashbeam/t  <<  std::endl << std::endl;
//   // std::cout << "HitsCosmic Time:      " << hitscosmic*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "HitsCosmic Fraction:         " << (double)hitscosmic/t  <<  std::endl << std::endl;
//   // std::cout << "Flashcosmic Time:     " << flashcosmic*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "Flashcosmic Fraction:        " << (double)flashcosmic/t  <<  std::endl << std::endl;
//   // std::cout << "FlashFilter Time:     " << flashfilter*1.0/CLOCKS_PER_SEC << " seconds" <<  std::endl << std::endl;
//   // std::cout << "FlashFilter Fraction:        " << (double)flashfilter/t  <<  std::endl << std::endl;
//   // std::cout << "Percentage Check :    " << (double)flashfilter/t+(double)flashcosmic/t+(double)hitscosmic/t+(double)flashbeam/t+(double)hitsbeam/t+(double)satmerger/t+(double)dataread/t << std::endl;
//

return 0;
};
