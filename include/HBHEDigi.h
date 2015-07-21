#ifndef HBHE_DIGI_H
#define HBHE_DIGI_H

#include "HcalDigi.h"
#include "HBHESample.h"

class HBHEDigi : public HcalDigi {

 public:
  HBHEDigi();
  HBHEDigi(Collection& c, unsigned short i, short j = 0);
  
  float energy() ;
  float recHitTime  () ;
  int   ieta  () ;
  int   iphi  () ;
  float eta  () ;
  float phi  () ;
  int   depth () ;
  int   subdet () ;
  int   size  () ;
  int   presamples() ;
  int   electronicsId();
  int   rawId();
  float fc (int i);
  int adc(int i);
  int dv (int i);
  int er (int i);
  int capid (int i);
  
  int getRawIndex () { return m_raw_index; }

  HBHESample operator[] ( int i ){
    return HBHESample( *m_collection, m_raw_index, i );
  }
  
};

#endif 
