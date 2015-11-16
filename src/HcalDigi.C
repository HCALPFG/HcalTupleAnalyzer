#include "HcalDigi.h"

HcalDigi::HcalDigi():
  Object(){}

HcalDigi::HcalDigi(Collection& c, unsigned short i, short j):
  Object(c,i,"HcalDigi"){}

double HcalDigi::time(){
  int n = size();
  int MaxI=-100; 
  double Time=0,SumT=0,MaxT=-10;
  
  for(int j=0;j<n;++j) if(MaxT<fc(j)){ MaxT=fc(j); MaxI=j; }

  if (MaxI>=0)
    {
      Time=MaxI*fc(MaxI);
      SumT=fc(MaxI);
      if(MaxI>0){ Time+=(MaxI-1)*fc(MaxI-1); SumT+=fc(MaxI-1); }
      if(MaxI<(n-1)){ Time+=(MaxI+1)*fc(MaxI+1); SumT+=fc(MaxI+1); }
      Time=Time/SumT;
    }
  return Time;
}

double HcalDigi::time12()  { return ( (1. * fc(1)) + (2. * fc(2)) ) / charge12(); }
double HcalDigi::time34()  { return ( (3. * fc(3)) + (4. * fc(4)) ) / charge34(); }
double HcalDigi::charge12(){ return ( fc(1) + fc(2) ); }
double HcalDigi::charge34(){ return ( fc(3) + fc(4) ); }

bool HcalDigi::isSignal(){
  int n = size();
  int Imax=-1; double max=-100;
  for(int i=0;i<n;i++) if(fc(i)>max){max=fc(i); Imax=i;}
  if(Imax==0 && Imax==(n-1)) return false;
  float sum=fc(Imax-1)+fc(Imax+1);
  if(fc(Imax)>5.5 && sum>(fc(Imax)*0.20)) return true;
  return false;
}

float HcalDigi::fcTotal() {
  float retval = 0.;
  for (int i = 0; i < size(); ++i){
    retval += fc(i);
  }
  return retval;
}

int HcalDigi::adcTotal() {
  int retval = 0.;
  for (int i = 0; i < size(); ++i){
    retval += adc(i);
  }
  return retval;
}

int HcalDigi::maxADC(){
  int max = -999;
  for (int i = 0; i < size(); ++i)
    if ( adc(i) > max ) max = adc(i);
  return max;
}
