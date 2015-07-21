#ifndef HBHE_COSMIC_DIGI_H
#define HBHE_COSMIC_DIGI_H

#include "HcalDigi.h"
#include "HBHECosmicSample.h"

class HBHECosmicDigi : public HcalDigi {

 public:
  HBHECosmicDigi();
  HBHECosmicDigi(Collection& c, unsigned short i, short j = 0);
  
  float energy() ;
  float recHitTime  () ;
  int   ieta  () ;
  int   iphi  () ;
  int   subdet() ;
  float eta  () ;
  float phi  () ;
  int   depth () ;
  int   size  () ;
  int   presamples() ;
  float fc (int i);
  int adc(int i);
  int dv (int i);
  int er (int i);
  int capid (int i);

  int   electronicsId();
  int   rawId();
  int getRawIndex () { return m_raw_index; }

  HBHECosmicSample operator[] ( int i ){
    return HBHECosmicSample( *m_collection, m_raw_index, i );
  }
  
};

#endif 
