/*
This file contains the namespace for WireCell2dToy
I think we will want to rename this, but keep it in some form.
Most of the objects seem useful.
We'll want to define this namespace such that we can use it will all our functions.
*/

namespace WireCell2dToy{

  struct pmtDisc{
    short channel;
    double timestamp;
    std::vector<short> wfm;
    bool saturated;
    bool isolated;
    bool highGain;
  };
  typedef std::map<short,pmtDisc> pmtMap;
  struct timeOrder_pmtDisc{
    bool operator()(const pmtDisc& a, const pmtDisc& b) const
    {return a.timestamp < b.timestamp;}
  };
  typedef std::set<pmtDisc,timeOrder_pmtDisc> pmtSet;
  typedef std::map<short,pmtSet> pmtMapSet;
  typedef std::pair<pmtDisc,pmtDisc> pmtPair;
  struct timeOrder_pmtPair{
    bool operator()(const pmtPair& a, const pmtPair& b) const
    {return a.first.timestamp < b.first.timestamp;}
  };
  typedef std::set<pmtPair,timeOrder_pmtPair> pmtSetPair;
  typedef std::map<short,pmtPair> pmtMapPair;
  typedef std::map<short,pmtSetPair> pmtMapSetPair;
  typedef std::vector<std::pair<short,short> > saturationTick;
