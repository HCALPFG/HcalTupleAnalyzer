#ifndef HLT_FILTER_OBJECT_COLLECTION_HELPER
#define HLT_FILTER_OBJECT_COLLECTION_HELPER

#include "HcalTupleTree.h"
#include "Collection.h"

class HLTFilterObjectCollectionHelper{

 public:
  HLTFilterObjectCollectionHelper( HcalTupleTree & d );
  short FindHLTFilterIndex ( const char * filter_name );
  CollectionPtr GetHLTFilterObjects ( const char * filter_name );
  void PrintFilterNames();
  
 private:
  HcalTupleTree * m_data;

};

#endif 
