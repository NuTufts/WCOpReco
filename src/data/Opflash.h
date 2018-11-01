#ifndef Opflash_h
#define Opflash_h

#include "COphit.h"
#include <math.h>
#include <set>

namespace wcopreco{
  class Opflash{
  public:
    Opflash(COphitSelection &ophits);
    Opflash(const std::vector<std::vector<double>> &vec_v, double start_time, int start_bin, int end_bin, float bin_width=6*15.625/1000.); //bin width should be derived from detector constants when in larlite/larsoft
    ~Opflash();

    void Add_l1info(std::vector<double>* vec1, std::vector<double> *vec2, double start_time , int start_bin, int end_bin, float bin_width=6*15.625/1000.);

    void set_flash_id(int value){flash_id = value;};
    int get_flash_id(){return flash_id;};

    double get_time(){return time;};
    double get_total_PE(){return total_PE;};
    double get_PE(int ch){return PE[ch];};
    double get_PE_err(int ch){return PE_err[ch];};
    bool get_fired(int ch);
    int get_num_fired(){return fired_channels.size();};

    int get_type(){return type;}
    double get_low_time(){return low_time;};
    double get_high_time(){return high_time;};

    std::vector<double>& get_l1_fired_time(){return l1_fired_time;};
    std::vector<double>& get_l1_fired_pe(){return l1_fired_pe;};

    void swap_channels();

  protected:

    int type;
    int flash_id;
    double low_time;
    double high_time;

    double time;
    double total_PE;
    std::vector<int> fired_channels;
    double PE[32];
    double PE_err[32];

    std::vector<double> l1_fired_time;
    std::vector<double> l1_fired_pe;
  };

  struct OpFlashCompare{
    bool operator() (Opflash *a, Opflash *b) const{
      if (a->get_time() < b->get_time()){
	return true;
      }else{
	return false;
      }
    }
  };

  typedef std::vector<Opflash*> OpflashSelection;
  typedef std::set<Opflash*, OpFlashCompare> OpFlashSet;

}

#endif
