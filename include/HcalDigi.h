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
  virtual float fc    (int i) = 0;
  virtual int   adc   (int i) = 0;
  
  double time();
  bool   isSignal();

  double & Pt() { return m_null_value; } // Code will crash!
  double & Eta(){ return m_null_value; } // Code will crash!
  double & Phi(){ return m_null_value; } // Code will crash!
  
  bool PassUserID (ID, bool) { return false; }

 protected:
  double m_null_value;

};

#endif
