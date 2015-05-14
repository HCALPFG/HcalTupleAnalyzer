#ifndef HCAL_ID_TYPES_H
#define HCAL_ID_TYPES_H

enum ID { 
  NULL_ID      = 999,
  DIGI_HAS_NDV = 1,
  DIGI_HAS_ER  = 2,
  DIGI_HAS_CAPID_ERR = 3,
  DIGI_HAS_BAD_SIZE = 4,
  DIGI_IS_SIGNAL = 5
};

#endif
