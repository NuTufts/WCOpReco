#include "Flashes_beam.h"

namespace wcopreco {

  wcopreco::Flashes_beam::Flashes_beam(std::vector<double> totPE_v, std::vector<double> mult_v, std::vector<double> l1_totPE_v, std::vector<double> l1_mult_v, std::vector< std::vector<double> > decon_vv, double beam_start_time)
  {
    //Module for flash finding for beams

    //BEGIN FLASH CODE
    // Now working on the flashes ...
      // [-2,78)

    std::vector<int> flash_time;
    flash_time.reserve(250);
    std::vector<double> flash_pe;

    double prev_pe_a[32];
    double curr_pe_a[32];

    for (int i=0;i!=250;i++){
      double pe = totPE_v.at(i);
      double mult = mult_v.at(i);
      // if (i==0 || i ==249) {std::cout << pe << "    Tot PE Value in bin 1     " << mult << "     multiplicity value in bin 1\n"; }
      // careteria: multiplicity needs to be higher than 3, PE needs to be higher than 6
      //std::cout << pe << " " << mult << std::endl;

      if (pe >= 6 && mult >= 3){
        bool flag_save = false;
        if (flash_time.size()==0){
  	       flag_save = true;

  	       for (int j=0;j!=32;j++){


  	          prev_pe_a[j] = decon_vv.at(j).at(i);


  	       }
        }
        else{
  	       for (int j=0;j!=32;j++){

              curr_pe_a[j] = decon_vv[j].at(i);
  	       }

  	       if (i - flash_time.back() >= 78){
             std::cout << i << "   Flashtime added!\n";

  	          flag_save = true;
  	  // start one, and open a window of 8 us, if anything above it, not the next 2 bin
  	  // if find one is bigger than this, save a flash ... start a new flash?
           }

           else if (i-flash_time.back() > 4 && pe > flash_pe.back()){
  	          if (i-flash_time.back()>15){
                std::cout << i << "   Flashtime added!\n";

  	             flag_save = true;
  	          }
              else{
                 if (KS_maxdiff(32,prev_pe_a,curr_pe_a) > 0.1){
                   std::cout << i << "   Flashtime added!\n";

  	               flag_save = true;
  	             }


  	          }
  	       }

           for (int j=0;j!=32;j++){
              prev_pe_a[j] = decon_vv[j].at(i);
  	       }
        }

        if (flag_save){
          	flash_time.push_back(i);
          	flash_pe.push_back(pe);
        }

        else{
  	       if (i - flash_time.back()<=6 && pe > flash_pe.back())
             {
             flash_pe.back()=pe;
           }
        }
      }
    }


     // std::cout << flash_time.size() << " " << flash_pe.size() << std::endl;
     // for a flash, examine the L1 one to decide if add in more time ...?

    for (size_t i=0; i!=flash_time.size(); i++){
      //std::cout << flash_time.at(i) << " " << flash_pe.at(i) << std::endl;
      int start_bin = flash_time.at(i)-2;
      if (start_bin <0) start_bin = 0;

      int end_bin = start_bin + 78; // default
      if (end_bin > 250) end_bin = 250;
      if (i+1<flash_time.size()){
        if (end_bin > flash_time.at(i+1)-2) {
          end_bin = flash_time.at(i+1)-2;
        }
      }
      //  std::cout << start_bin << " " << end_bin << std::endl;
      //check with the next bin content ...

      Opflash *flash = new Opflash(decon_vv, beam_start_time, start_bin, end_bin);
      flash->Add_l1info(&l1_totPE_v, &l1_mult_v, beam_start_time, start_bin, end_bin);
      // std::cout << flash->get_time() << " " <<flash->get_total_PE() << " " << flash->get_num_fired() << std::endl;
      beam_flashes.push_back(flash);
      }
    // std::cout << beam_flashes.size() << " Size of beam flashes\n";
    }


  double wcopreco::Flashes_beam::KS_maxdiff(int n, double *array1, double *array2){

       for (int index =1; index<n; index++){
         array1[index] += array1[index-1];
         array2[index] += array2[index-1];
       }
       double maxdiff=0;
       double thisdiff=0;
       for (int index=0; index<n; index++){
         array1[index] = array1[index]/array1[n-1];
         array2[index] = array2[index]/array2[n-1];
         thisdiff =fabs(array1[index]-array2[index]);
         if (thisdiff > maxdiff) {maxdiff = thisdiff;}
       }
       return maxdiff;
     }

}
