#include "kernel_fourier.h"
#include <vector>


namespace wcopreco {

 wcopreco::kernel_fourier::kernel_fourier(std::string nm, bool mult_flag)
  {
    name = nm;
    std::cout <<"Kernel Name is set to:   || " <<  name << " ||" << std::endl;

    mult_div = mult_flag;
    std::string optioned;
    if (mult_div) {optioned = "|| Multiply || this kernel.";}
    else if (not mult_div) {optioned = "|| Divide || this kernel.";}
    else {optioned = " Bool not true or false...";}
    std::cout << "Flag is set to:  " << mult_div  << "   This means "<< optioned << std::endl;



  }

  void wcopreco::kernel_fourier::Get_pow_spec(int nbins, float tick_width_ns, std::vector<double>* mag_v, std::vector<double>* phase_v)

    {
      mag_v->resize(nbins);
      phase_v->resize(nbins);

      //Get the input to the fourier transform ready
      std::vector<double> power_spec_d(nbins,0);
      power_spec_d = Get_wfm(nbins,tick_width_ns);
      double *in = power_spec_d.data();

      //Start the fourier transform (real to complex)
      TVirtualFFT *fftr2c = TVirtualFFT::FFT(1, &nbins, "R2C");
      fftr2c->SetPoints(in);
      fftr2c->Transform();
      double *re = new double[nbins]; //Real -> Magnitude
      double *im = new double[nbins]; //Imaginary -> Phase

      fftr2c->GetPointsComplex(re, im); //Put the values in the arrays

      // int index =3;
      // std::cout << power_spec_d[index] << "    POWER SPEC[" << index << "]" <<std::endl;
      // std::cout << re[index] << "    RE[" << index << "]" << std::endl;
      // std::cout << *(re+500) << "   Accessed *(re+500)" << std::endl;

      //Copy those array values into vectors passed in by reference.
      //This is inefficient, but makes for an easier user interface.
      double im_i =0;
      double re_i = 0;
      for (int i =0; i<nbins; i++){
        //Calculate the phase_v
        im_i = im[i];
        re_i = re[i];
        double ph = 0;
        // fft->GetPointComplex(ind, re, im);
        if (TMath::Abs(re_i) > 1e-13){
           ph = TMath::ATan(im_i/re_i);


           //find the correct quadrant
           if (re_i<0 && im_i<0)
              ph -= TMath::Pi();
           if (re_i<0 && im_i>=0)
              ph += TMath::Pi();
        } else {
           if (TMath::Abs(im_i) < 1e-13)
              ph = 0;
           else if (im_i>0)
              ph = TMath::Pi()*0.5;
           else
              ph = -TMath::Pi()*0.5;
        }
        phase_v->at(i) = ph;
        //End of phase_v calc

        //Calculate the mag_v
        double magnitude = TMath::Sqrt(re[i]*re[i]+im[i]*im[i]);
        mag_v->at(i) = magnitude;
        //if (i%50 == 0) std::cout<<"Magnitude is " << mag_raw[i] <<std::endl;
        //End of mag_v calc
      }

      //Test loop to output every 50 entries
      for (int index =0; index <phase_v->size(); index +=50) {
        // std::cout << phase_v->at(index) << "    Phase[" << index << "]" << std::endl <<std::endl;
        // std::cout << im[index] << "    IM[" << index << "]" << std::endl;
      }


      // Deletion test confirms that you can delete re after you delecte fftr2c, so fftr2c doesn't own re or im! Good.
      /*
      std::cout<< "Before delete    " << std::endl << std::endl << std::endl << std::endl;
      delete fftr2c;
      std::cout<< "After first  delete    " << std::endl << std::endl << std::endl << std::endl;
      delete [] re;
      std::cout<< "After Second!!! delete    " << std::endl << std::endl << std::endl << std::endl;
      */





      std::cout << nbins << " bins POWER  " << tick_width_ns << "  tick width POWER" << std::endl;
      std::cout << nbins*tick_width_ns << " Is total width of wfm" << std::endl <<std::endl;
      return ;
    }

  }
