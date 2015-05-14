#ifndef RBXMAP_H
#define RBXMAP_H

#include <string>
#include <vector>

class RBXMap {
  
 public:

  // Constructor & destructor
  RBXMap();
  ~RBXMap();

  // Load input
  void LoadFile(const char* file_name);

  // Get output (string)
  std::string getRBXString ( const std::string & det, int side, int ieta, int iphi, int depth );
  std::string getRBXString ( int det_int            , int side, int ieta, int iphi, int depth );

  // Get output (RBX number)
  int getRBXNumber         ( const std::string & det, int side, int ieta, int iphi, int depth );
  int getRBXNumber         ( int det_int            , int side, int ieta, int iphi, int depth );
  
  // Get index of channel
  int getIndex             ( const std::string & det, int side, int ieta, int iphi, int depth );
  int getIndex             ( int det_int            , int side, int ieta, int iphi, int depth );

  // Get coordinates from index
  void getCoordinates      (int index, int det_int, int & side, int & ieta, int &iphi, int & depth );
  
  // Get output (RBX side)
  int getRBXSide           ( const std::string & det, int side, int ieta, int iphi, int depth );
  int getRBXSide           ( int det_int            , int side, int ieta, int iphi, int depth );
  
  // Get output (FED number)
  int getFEDNumber         ( const std::string & det, int side, int ieta, int iphi, int depth );
  int getFEDNumber         ( int det_int            , int side, int ieta, int iphi, int depth );

  // Say what you loaded
  void PrintAllRBXs();
  void PrintRBXs   ( int det_int );

  std::vector<std::string> getHBRBXNames() { return m_hb_rbx_names; }
  std::vector<std::string> getHERBXNames() { return m_he_rbx_names; }
  std::vector<std::string> getHORBXNames() { return m_ho_rbx_names; }
  std::vector<std::string> getHFRBXNames() { return m_hf_rbx_names; }
  
 private:

  long getHash  (int det_int            , int side, int ieta, int iphi, int depth );
  long getHash  (const std::string & det, int side, int ieta, int iphi, int depth );
  int getDetInt (const std::string & det);
  
  std::vector<std::string> m_hb_rbx_names;
  std::vector<std::string> m_he_rbx_names;
  std::vector<std::string> m_ho_rbx_names;
  std::vector<std::string> m_hf_rbx_names;
  std::vector<std::string> m_hox_rbx_names;

  std::vector<std::string> m_hash_map_rbxstring;
  std::vector<int>         m_hash_map_rbxnumber;
  std::vector<int>         m_hash_map_fednumber;
  std::vector<int>         m_hash_map_rbxside;
  std::vector<int>         m_hash_map_hoIndex;
  std::vector<int>         m_hash_map_hfIndex;
  std::vector<int>         m_hash_map_hbIndex;
  std::vector<int>         m_hash_map_heIndex;
  std::vector<int>         m_hoIndex_to_hash;
  std::vector<int>         m_hfIndex_to_hash;
  std::vector<int>         m_hbIndex_to_hash;
  std::vector<int>         m_heIndex_to_hash;
};

#endif
