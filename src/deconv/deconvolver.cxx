#include "deconvolver.h"

namespace wcopreco {

void wcopreco::deconvolver::deconv_test()

  {
    int nbins = 1500;
    float bin_width = (1.0/(64e6) );

    //load raw data -test for now

    std::string file = "src/data/celltree.root";
    wcopreco::DataReader reader(file);
    std::cout << "Filepath is set to:   " << file << std::endl;

    int EVENT_NUM = 3;
    int TYPE_OF_COLLECTION =0;
    int WFM_INDEX =0;
    int SIGNAL_INDEX =2;

    wcopreco::UBEventWaveform _UB_Ev_wfm;
    _UB_Ev_wfm = reader.Reader(EVENT_NUM);


    OpWaveform wfm = ( ( ( ( _UB_Ev_wfm ).get__wfm_v() ) [TYPE_OF_COLLECTION] )  [WFM_INDEX] );
    
    //remove baseline
    int size = wfm.size();
    //std::cout << size << std::endl;

    float baseline = wfm[0];

    for (int i=0; i<size; i++) {
      wfm[i] = wfm[i] - baseline;
    }

    std::vector<double> wfm_doubles(wfm.begin(), wfm.end());

    //get power spectrum of data
    std::vector<double> mag_raw;
    std::vector<double> phase_raw;

    mag_raw.resize(nbins);
    phase_raw.resize(nbins);

    //Get the input to the fourier transform ready
    std::vector<double> power_spec_d(nbins,0);
    power_spec_d = wfm_doubles;
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
    memcpy(mag_raw.data(), re, sizeof(double)*nbins);
    memcpy(phase_raw.data(), im, sizeof(double)*nbins);

    // std::cout << mag_raw.at(index) << "    MAG[" << index << "]" << std::endl <<std::endl;
    // std::cout << im[index] << "    IM[" << index << "]" << std::endl;

    // Deletion test confirms that you can delete re after you delecte fftr2c, so fftr2c doesn't own re or im! Good.
    // std::cout<< "Before delete    " << std::endl << std::endl << std::endl << std::endl;
    // delete fftr2c;
    // std::cout<< "After first  delete    " << std::endl << std::endl << std::endl << std::endl;
    // delete [] re;
    // std::cout<< "After Second!!! delete    " << std::endl << std::endl << std::endl << std::endl;
    //
    // std::cout << nbins << " bins POWER  " << bin_width << "  tick width POWER" << std::endl;
    // std::cout << nbins*bin_width << " Is total width of wfm" << std::endl;

    // std::string word = "Josh" ;
    //
    // UB_spe spe(word, true);
    // // spe.gain = 1;
    //
    // std::vector<double> vec_spe = spe.Get_wfm(nbins,bin_width);
    // std::cout << vec_spe.size() << "    Is size of vector." << std::endl;
    // std::cout << vec_spe.at(1) << "    Is first element." << std::endl;
    // std::cout << vec_spe.at(500) << "    Is 500 element." << std::endl;
    // std::cout << *std::max_element(vec_spe.begin(),vec_spe.end()) << "    Is MAX element." << std::endl;
    //
    // std::vector<double> mag_spe;
    // std::vector<double> phase_spe;
    //
    // spe.Get_pow_spec(nbins,bin_width,&mag_spe,&phase_spe);
    // std::cout << mag_spe.size() << "    Is size of vector." << std::endl;
    // std::cout << mag_spe.at(1) << "    Is first element." << std::endl;
    // std::cout << mag_spe.at(500) << "    Is 500 element." << std::endl;
    // std::cout << *std::max_element(mag_spe.begin(),mag_spe.end()) << "    Is MAX element." << std::endl;
    //
    // //testing UB_rc
    // UB_rc rc(word,true);
    //
    // std::vector<double> vec_rc = rc.Get_wfm(nbins,bin_width);
    // std::cout << vec_rc.size() << "    Is size of vector(rc)." << std::endl;
    // std::cout << vec_rc.at(1) << "    Is first element(rc)." << std::endl;
    // std::cout << vec_rc.at(500) << "    Is 500 element(rc)." << std::endl;
    // std::cout << *std::max_element(vec_rc.begin(),vec_rc.end()) << "    Is MAX element(rc)." << std::endl;
    //
    // std::vector<double> mag_rc;
    // std::vector<double> phase_rc;
    //
    // rc.Get_pow_spec(nbins,bin_width,&mag_rc,&phase_rc);
    // std::cout << mag_rc.size() << "    Is size of vector(rc)." << std::endl;
    // std::cout << mag_rc.at(1) << "    Is first element(rc)." << std::endl;
    // std::cout << mag_rc.at(500) << "    Is 500 element(rc)." << std::endl;
    // std::cout << *std::max_element(mag_rc.begin(),mag_rc.end()) << "    Is MAX element(rc)." << std::endl;

    //for (int i=0; i<nbins; i++) {
      //X = (tick_width_ns)*(double(i)+0.5);
      //std::cout << X << std::endl;

      //hm and hp are the FFT of the raw opWaveForm minus the baseline - should be another object?
      //double rho = hm->GetBinContent(i+1)/ mag_rc.at(i) / mag.at(i)  ;
      //double phi = hp->GetBinContent(i+1) - phase_rc.at(i) - hp_spe.at(i);
    //}

  }


}
