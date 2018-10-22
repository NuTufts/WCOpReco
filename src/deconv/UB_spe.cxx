#include "UB_spe.h"




namespace wcopreco {

wcopreco::UB_spe::UB_spe(std::string nm, bool mult_flag, float op_gain)
: kernel_fourier (nm,mult_flag)
 {
   gain = op_gain;
 }

std::vector<double> wcopreco::UB_spe::Get_wfm(int nbins, float tick_width_ns)

  {
    std::vector<double> wfm(nbins,0);
    double value=0;
    int size = wfm.size();
    double parameter_1 = 8.18450e-01;
    double X;


    for (int i=0; i<size; i++) {
      X = (double(i)+0.5);
      // std::cout << gain << std::endl;

      value = 1./19.6348*pow(X/parameter_1,4)*exp(-X/parameter_1)*gain;

      // if (i%100 ==0) {std::cout << value << " Is value of the analytical function at X: " << X << "   and i value: "<< i << std::endl;}
      // if (i%100 ==0) {std::cout << gain << " GAIN " << X << std::endl;}
      wfm[i] = value;
    }



    // std::cout << nbins << " bins WFM  " << tick_width_ns << "  tick width WFM" << std::endl;
    // std::cout << nbins*tick_width_ns << "ns Is time width of this waveform." <<std::endl << std::endl;;
    return wfm;
  }


// This function is now generalized to the base class.
// void wcopreco::UB_spe::Get_pow_spec(int nbins, float tick_width_ns, std::vector<double>* mag, std::vector<double>* phase)
//
//   {
//     mag->resize(nbins);
//     phase->resize(nbins);
//
//     //Get the input to the fourier transform ready
//     std::vector<double> power_spec_d(nbins,0);
//     power_spec_d = Get_wfm(nbins,tick_width_ns);
//     double *in = power_spec_d.data();
//
//     //Start the fourier transform (real to complex)
//     TVirtualFFT *fftr2c = TVirtualFFT::FFT(1, &nbins, "R2C");
//     fftr2c->SetPoints(in);
//     fftr2c->Transform();
//     double *re = new double[nbins]; //Real -> Magnitude
//     double *im = new double[nbins]; //Imaginary -> Phase
//
//     fftr2c->GetPointsComplex(re, im); //Put the values in the arrays
//
//     int index =3;
//     std::cout << power_spec_d[index] << "    POWER SPEC[" << index << "]" <<std::endl;
//     std::cout << re[index] << "    RE[" << index << "]" << std::endl;
//     // std::cout << *(re+500) << "   Accessed *(re+500)" << std::endl;
//
//     //Copy those array values into vectors passed in by reference.
//     //This is inefficient, but makes for an easier user interface.
//     memcpy(mag->data(), re, sizeof(double)*nbins);
//     memcpy(phase->data(), im, sizeof(double)*nbins);
//
//     std::cout << mag->at(index) << "    MAG[" << index << "]" << std::endl <<std::endl;
//     std::cout << im[index] << "    IM[" << index << "]" << std::endl;
//
//
//
//     // Deletion test confirms that you can delete re after you delecte fftr2c, so fftr2c doesn't own re or im! Good.
//     /*
//     std::cout<< "Before delete    " << std::endl << std::endl << std::endl << std::endl;
//     delete fftr2c;
//     std::cout<< "After first  delete    " << std::endl << std::endl << std::endl << std::endl;
//     delete [] re;
//     std::cout<< "After Second!!! delete    " << std::endl << std::endl << std::endl << std::endl;
//     */
//
//
//
//
//
//     std::cout << nbins << " bins POWER  " << tick_width_ns << "  tick width POWER" << std::endl;
//     return ;
//   }

}
