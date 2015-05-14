#ifndef HO_COSMIC_DIGI_H
#define HO_COSMIC_DIGI_H

#include "HcalDigi.h"
#include "HOCosmicSample.h"

class HOCosmicDigi : public HcalDigi {

 public:
  HOCosmicDigi();
  HOCosmicDigi(Collection& c, unsigned short i, short j = 0);
  
  float energy() ;
  float recHitTime  () ;
  int   ieta  () ;
  int   iphi  () ;
  float eta  () ;
  float phi  () ;
  int   depth () ;
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

  HOCosmicSample operator[] ( int i ){
    return HOCosmicSample( *m_collection, m_raw_index, i );
  }
  
};

#endif 
