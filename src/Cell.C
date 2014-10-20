#include "Cell.h"

cell::cell(int subdet, int ieta, int iphi, int depth):
  m_subdet(subdet), 
  m_ieta(ieta)    , 
  m_iphi(iphi)    , 
  m_depth(depth) {
  int absIeta = abs(m_ieta);
  int sign    = m_ieta / absIeta;
  m_value  = 0;
  m_value += 1      * m_depth  ;
  m_value += 10     * m_iphi   ;
  m_value += 1000   * absIeta  ;
  m_value += 100000 * m_subdet ;
  m_value *= sign;
  }
