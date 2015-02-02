#include "RBXMap.h"

#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

RBXMap::RBXMap():
  m_hash_map_rbxstring ( 1600000, std::string("") ),
  m_hash_map_rbxnumber ( 1600000, -1 ),
  m_hash_map_fednumber ( 1600000, -1 ),
  m_hash_map_rbxside   ( 1600000, -1 ),
  m_hash_map_hoIndex   ( 1600000, -1 ),
  m_hash_map_hbIndex   ( 1600000, -1 ),
  m_hash_map_heIndex   ( 1600000, -1 ),
  m_hash_map_hfIndex   ( 1600000, -1 ),
  m_hoIndex_to_hash    ( 1600000, -1 ),
  m_hbIndex_to_hash    ( 1600000, -1 ),
  m_heIndex_to_hash    ( 1600000, -1 ),
  m_hfIndex_to_hash    ( 1600000, -1 )
{}

RBXMap::~RBXMap(){}

void RBXMap::PrintAllRBXs(){
  
  PrintRBXs( 1 );
  PrintRBXs( 2 );
  PrintRBXs( 3 );
  PrintRBXs( 4 );

  // Ignore HOX
  // PrintRBXs( 5 );
  
}

void RBXMap::PrintRBXs( int det_int ) { 
  
  std::string name;
  std::vector<std::string> * rbxs;
  
  if      ( det_int == 1 ) {
    name = std::string("HB");
    rbxs = & m_hb_rbx_names;
  } 

  else if ( det_int == 2 ) {
    name = std::string("HE");
    rbxs = & m_he_rbx_names;
  } 

  else if ( det_int == 3 ) {
    name = std::string("HO");
    rbxs = & m_ho_rbx_names;
  } 

  else if ( det_int == 4 ) {
    name = std::string("HF");
    rbxs = & m_hf_rbx_names;
  } 

  else if ( det_int == 5 ) {
    name = std::string("HOX");
    rbxs = & m_hox_rbx_names;
  } 

  int n_rbx = rbxs -> size();
  
  std::cout << "Loaded these "<< n_rbx << " " << name << " RBXs:" << std::endl;
  for (int i = 0; i < n_rbx; ++i) {
    std::cout << rbxs -> at(i) << "\t";
    if ( (i+1) % 6 == 0 ) std::cout << std::endl;
  }
  std::cout << std::endl;

}

long RBXMap::getHash ( int det_int, int side, int ieta, int iphi, int depth ){
  
  // side [1 digit], subdet [1 digit], eta [2 digits], phi [2 digits], depth [1 digit]
  // Total of 7 digits: > 1 million addresses.
  
  if (side == -1) side = 0;

  long hash = 0;
  hash += (side    * 1000000);
  hash += (det_int * 100000 );
  hash += (ieta    * 1000   );
  hash += (iphi    * 10     );
  hash += (depth   * 1      );
  
  return hash;
}

int RBXMap::getDetInt ( const std::string & det ){
  int det_int = -1;
  if      ( det.compare("HB" ) == 0 ) det_int = 1;
  else if ( det.compare("HE" ) == 0 ) det_int = 2;
  else if ( det.compare("HO" ) == 0 ) det_int = 3;
  else if ( det.compare("HF" ) == 0 ) det_int = 4;
  else if ( det.compare("HOX") == 0 ) det_int = 5;
  else {
    std::cout << "Don't understand this detector: " << det << std::endl;
    return -1;
  }

  return det_int;
}

long RBXMap::getHash ( const std::string & det, int side, int ieta, int iphi, int depth ){
  int det_int = getDetInt ( det ) ;
  return getHash( det_int , side, ieta, iphi, depth );
}

std::string RBXMap::getRBXString( const std::string & det, int side, int ieta, int iphi, int depth ){
  int hash = getHash ( det, side, ieta, iphi, depth );
  return m_hash_map_rbxstring[hash];
}

int RBXMap::getIndex ( const std::string & det, int side, int ieta, int iphi, int depth ){
  int hash = getHash ( det, side, ieta, iphi, depth );
  if ( det.compare("HB") == 0 ) return m_hash_map_hbIndex[hash];
  if ( det.compare("HE") == 0 ) return m_hash_map_heIndex[hash];
  if ( det.compare("HO") == 0 ) return m_hash_map_hoIndex[hash];
  if ( det.compare("HF") == 0 ) return m_hash_map_hfIndex[hash];
  return -1;
}

int RBXMap::getIndex ( int det_int, int side, int ieta, int iphi, int depth ){
  int hash = getHash ( det_int, side, ieta, iphi, depth );
  if ( det_int == 1 ) return m_hash_map_hbIndex[hash];
  if ( det_int == 2 ) return m_hash_map_heIndex[hash];
  if ( det_int == 3 ) return m_hash_map_hoIndex[hash];
  if ( det_int == 4 ) return m_hash_map_hfIndex[hash];
  return -1;
}

void RBXMap::getCoordinates(int index, int det_int, int & side, int & ieta, int &iphi, int & depth ){
  long hash;  
  if ( det_int == 1 ) hash = m_hbIndex_to_hash[index];
  if ( det_int == 2 ) hash = m_heIndex_to_hash[index];
  if ( det_int == 3 ) hash = m_hoIndex_to_hash[index];
  if ( det_int == 4 ) hash = m_hfIndex_to_hash[index];
  depth = hash % 10;
  iphi  = (hash / 10) % 100;
  ieta  = (hash / 1000) % 100;
  side  = (hash / 1000000);
  if ( side == 0 ) side = -1;
}

int RBXMap::getRBXNumber( const std::string & det, int side, int ieta, int iphi, int depth ){
  int hash = getHash ( det, side, ieta, iphi, depth );
  return m_hash_map_rbxnumber[hash];
}

int RBXMap::getRBXSide( const std::string & det, int side, int ieta, int iphi, int depth ){
  int hash = getHash ( det, side, ieta, iphi, depth );
  return m_hash_map_rbxside[hash];
}

std::string RBXMap::getRBXString( int det_int, int side, int ieta, int iphi, int depth ){
  int hash = getHash ( det_int, side, ieta, iphi, depth );
  return m_hash_map_rbxstring[hash];
}

int RBXMap::getRBXNumber( int det_int, int side, int ieta, int iphi, int depth ){
  int hash = getHash ( det_int, side, ieta, iphi, depth );
  return m_hash_map_rbxnumber[hash];
}

int RBXMap::getRBXSide( int det_int, int side, int ieta, int iphi, int depth ){
  int hash = getHash ( det_int, side, ieta, iphi, depth );
  return m_hash_map_rbxside[hash];
}

int RBXMap::getFEDNumber( const std::string & det, int side, int ieta, int iphi, int depth ){
  int hash = getHash ( det, side, ieta, iphi, depth );
  return m_hash_map_fednumber[hash];
}

int RBXMap::getFEDNumber( int det_int, int side, int ieta, int iphi, int depth ){
  int hash = getHash ( det_int, side, ieta, iphi, depth );
  return m_hash_map_fednumber[hash];
}

void RBXMap::LoadFile(const char* file_name){

  std::fstream file(file_name, std::ios_base::in);  
  std::string line;

  int iHB = 0;
  int iHE = 0;
  int iHO = 0;
  int iHF = 0;
  
  while ( std::getline(file, line)){

    if (strncmp(&line[0],"#",1) == 0) continue;

    std::istringstream iss(line);

    std::vector<std::string> entries;
    std::copy(std::istream_iterator<std::string>(iss),
	      std::istream_iterator<std::string>(),
	      std::back_inserter<std::vector<std::string> >(entries));

    int side        = std::stoi( entries[1] );
    int ieta        = std::stoi( entries[2] );
    int iphi        = std::stoi( entries[3] );
    int depth       = std::stoi( entries[5] );
    std::string det = entries[6];
    std::string rbx_name = entries[7];
    int rbx_number  = std::stoi( entries[7].substr(entries[7].size() - 2));
    int fed_number  = std::stoi( entries[entries.size() - 1] );
    int rbx_side;

    std::string rbx_side_string;
    rbx_side_string = rbx_name.substr(2, rbx_name.size());
    rbx_side_string = rbx_side_string.substr(0, rbx_side_string.size() - 2);

    if      ( rbx_side_string.compare("2M") == 0 ) rbx_side = -2;
    else if ( rbx_side_string.compare("1M") == 0 ) rbx_side = -1;
    else if ( rbx_side_string.compare("0" ) == 0 ) rbx_side =  0;
    else if ( rbx_side_string.compare("1P") == 0 ) rbx_side =  1;
    else if ( rbx_side_string.compare("2P") == 0 ) rbx_side =  2;
    else if ( rbx_side_string.compare("M")  == 0 ) rbx_side = -1;
    else if ( rbx_side_string.compare("P")  == 0 ) rbx_side =  1;
    
    int det_int = getDetInt ( det );
    
    if      ( det_int == 1 && std::find(m_hb_rbx_names .begin(), m_hb_rbx_names .end(), rbx_name )==m_hb_rbx_names .end() ) m_hb_rbx_names .push_back ( rbx_name );
    else if ( det_int == 2 && std::find(m_he_rbx_names .begin(), m_he_rbx_names .end(), rbx_name )==m_he_rbx_names .end() ) m_he_rbx_names .push_back ( rbx_name );
    else if ( det_int == 3 && std::find(m_ho_rbx_names .begin(), m_ho_rbx_names .end(), rbx_name )==m_ho_rbx_names .end() ) m_ho_rbx_names .push_back ( rbx_name );
    else if ( det_int == 4 && std::find(m_hf_rbx_names .begin(), m_hf_rbx_names .end(), rbx_name )==m_hf_rbx_names .end() ) m_hf_rbx_names .push_back ( rbx_name );
    else if ( det_int == 5 && std::find(m_hox_rbx_names.begin(), m_hox_rbx_names.end(), rbx_name )==m_hox_rbx_names.end() ) m_hox_rbx_names.push_back ( rbx_name );

    int hash = getHash (det, side, ieta, iphi, depth);
    m_hash_map_rbxstring[hash] = rbx_name;
    m_hash_map_rbxnumber[hash] = rbx_number;
    m_hash_map_fednumber[hash] = fed_number;
    m_hash_map_rbxside  [hash] = rbx_side;

    
    if      ( det.compare("HB") == 0 ){
      m_hash_map_hbIndex[hash] = iHB;
      m_hbIndex_to_hash[iHB] = hash;
      iHB++;
    }

    else if ( det.compare("HE") == 0 ){
      m_hash_map_heIndex[hash] = iHE;
      m_heIndex_to_hash[iHE] = hash;
      iHE++;
    }

    else if ( det.compare("HO") == 0 ){
      m_hash_map_hoIndex[hash] = iHO;
      m_hoIndex_to_hash[iHO] = hash;
      iHO++;
    }

    else if ( det.compare("HF") == 0 ){
      m_hash_map_hfIndex[hash] = iHF;
      m_hfIndex_to_hash[iHF] = hash;
      iHF++;
    }

  }

  std::sort ( m_hb_rbx_names .begin(), m_hb_rbx_names .end());
  std::sort ( m_he_rbx_names .begin(), m_he_rbx_names .end());
  std::sort ( m_ho_rbx_names .begin(), m_ho_rbx_names .end());
  std::sort ( m_hf_rbx_names .begin(), m_hf_rbx_names .end());
  std::sort ( m_hox_rbx_names.begin(), m_hox_rbx_names.end());

}

