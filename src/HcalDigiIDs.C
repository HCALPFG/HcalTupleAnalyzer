#include "HcalDigi.h"

bool HcalDigi::PassUserID (ID id, bool verbose){
  if      ( id == DIGI_HAS_NDV       ) return PassUserID_DigiHasNDV       ( verbose );
  else if ( id == DIGI_HAS_ER        ) return PassUserID_DigiHasER        ( verbose );
  else if ( id == DIGI_HAS_CAPID_ERR ) return PassUserID_DigiHasCapIDErr  ( verbose );
  else if ( id == DIGI_HAS_BAD_SIZE  ) return PassUserID_DigiHasBadSize   ( verbose );
  else if ( id == DIGI_IS_SIGNAL     ) return PassUserID_DigiIsSignal     ( verbose );
  else return false;
}

bool HcalDigi::PassUserID_DigiIsSignal( bool verbose ){ 
  return (fcTotal() > 30.);
}

bool HcalDigi::PassUserID_DigiHasBadSize( bool verbose ){ 
  return ( size() != 10 );
}

bool HcalDigi::PassUserID_DigiHasNDV( bool verbose ){ 
  bool retval = true;
  for (int i = 0; i < size(); ++i)
    retval &= (dv(i) == 1);
  return !retval;
}

bool HcalDigi::PassUserID_DigiHasER( bool verbose ){ 
  bool retval = true;
  for (int i = 0; i < size(); ++i)
    retval &= (er(i) == 0);
  return !retval;
}

bool HcalDigi::PassUserID_DigiHasCapIDErr( bool verbose ){ 
  int last_capid = 0;
  int this_capid = 0;
  bool retval = false;
  for (int i = 0; i < size(); ++i){
    this_capid = capid(i);
    if ( i != 0 && this_capid != (last_capid+1)%4) retval = true;
    last_capid = this_capid;
  }
  
  if ( retval ) { 
    std::cout << ieta() << ", " << iphi() << ", " << depth() << ": ";
    for (int i = 0; i < size(); ++i){
      std::cout << capid(i) << " ";
    }
    std::cout << std::endl;
  }

  return retval;
}


