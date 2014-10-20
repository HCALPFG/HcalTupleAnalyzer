#ifndef cell_h
#define cell_h

#include <cstdlib>

class cell {
 public:
 
  cell(int subdet, int ieta, int iphi, int depth);
  
  friend bool operator<(const cell & cell1, const cell & cell2){
    return ( cell1.m_value < cell2.m_value );
  }

  friend bool operator==(const cell & cell1, const cell & cell2){
    return ( cell1.m_value == cell2.m_value );
  }
  
  int m_subdet, m_ieta, m_iphi, m_depth;
  int m_value;
};

#endif
