#ifndef HCAL_DIGI_H
#define HCAL_DIGI_H

#include "Object.h"
#include "HcalSample.h"

class HcalDigi : public Object { 
  
 public:
  HcalDigi();
  HcalDigi(Collection& c, unsigned short i, short j = 0);
  
  virtual float energy() = 0;
  virtual float recHitTime () = 0;
  virtual int   ieta  () = 0;
  virtual int   iphi  () = 0;
  virtual int   depth () = 0;
  virtual int   size  () = 0;
  virtual int   presamples() = 0;
  virtual int   electronicsId() = 0;
  virtual int   rawId() = 0;
  virtual float fc    (int i) = 0;
  virtual int   adc   (int i) = 0;
  virtual int   dv    (int i) = 0;
  virtual int   er    (int i) = 0;
  virtual int   capid (int i) = 0;
  
  float  fcTotal();
  int    adcTotal();
  double time();
  double time12();
  double time34();
  double charge12();
  double charge34();
  bool   isSignal();
  int    maxADC();

  double & Pt() { return m_null_value; } // Code will crash!
  double & Eta(){ return m_null_value; } // Code will crash!
  double & Phi(){ return m_null_value; } // Code will crash!
  
  bool PassUserID (ID id, bool verbose = false);
  
  bool PassUserID_DigiHasNDV     ( bool verbose );
  bool PassUserID_DigiHasER      ( bool verbose );
  bool PassUserID_DigiHasCapIDErr( bool verbose );
  bool PassUserID_DigiHasBadSize ( bool verbose );
  bool PassUserID_DigiIsSignal   ( bool verbose );

 protected:
  double m_null_value;

};

#endif
