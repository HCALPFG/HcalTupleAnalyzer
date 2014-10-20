#ifndef analysisClass_h
#define analysisClass_h

#include "baseClass.h"

class analysisClass : public baseClass {
 
 public:
  analysisClass (std::string inputList, std::string treeList, std::string out_file): 
  baseClass(inputList, treeList, out_file) {}
  void loop();
  
};

#endif

