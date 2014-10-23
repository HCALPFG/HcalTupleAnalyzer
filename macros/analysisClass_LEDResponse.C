#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HODigi.h"
#include "RBXMap.h"

const int n_ho_channels = 2160;
const int n_hbheho_rbx = 36;
const int n_hf_rbx     = 24;
const int n_fed        = 32;
const int min_fed      = 700;
const int max_fed      = 731;

const int n_iphi       = 72;
const int min_iphi     = 1;
const int max_iphi     = 72;

const int n_ieta       = 83;
const int min_ietaabs  = 1;
const int max_ietaabs  = 41;

std::string getHORBXNameFromIndex ( int index ) {
  int number;
  std::string side;
  int i = index + 1;

  if      ( i >= 1  && i <=  6 ) {
    number = 2 * i;
    side = std::string("2M");
  }
  else if ( i >= 7  && i <= 12 ) {
    number = 2 * (i - 6);
    side = std::string("1M");
  }
  else if ( i >= 13 && i <= 24 ) {
    number = i - 12;
      side = std::string("0");
  }
  else if ( i >= 25 && i <= 30 ) {
    number = 2 * (i - 24);
    side = std::string("1P");
  }
  else if ( i >= 31 && i <= 36 ) {
    number = 2 * (i - 30);
    side = std::string("2P");
  }
  char rbx_name[100];
  if ( number <  10 ) sprintf( rbx_name, "HO%s0%d", side.c_str() , number );
  if ( number >= 10 ) sprintf( rbx_name, "HO%s%d" , side.c_str() , number );
  
  return std::string(rbx_name);
}

int getHORBXIndex ( int rbx_side, int rbx_number ){
  int index;
  if      ( rbx_side == -2 ) index = 0  + (rbx_number/2);
  else if ( rbx_side == -1 ) index = 6  + (rbx_number/2);
  else if ( rbx_side ==  0 ) index = 12 + (rbx_number);
  else if ( rbx_side ==  1 ) index = 24 + (rbx_number/2);
  else if ( rbx_side ==  2 ) index = 30 + (rbx_number/2);
  return index - 1;
}

void analysisClass::loop(){
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();

  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiIEta"      , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiIPhi"      , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiDepth"     , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiRecEnergy" , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiRecTime"   , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiFC"        , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiSize"      , kTRUE );

  //--------------------------------------------------------------------------------
  // Declare and load RBX map
  //--------------------------------------------------------------------------------

  RBXMap map;
  map.LoadFile ( "data/emaps/HCALmapHBEF_E.txt" );
  map.LoadFile ( "data/emaps/HCALmapHO_E.txt" );

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------

  std::vector<TH1F*> h_ho_rbx_charge     (n_hbheho_rbx, 0);
  std::vector<TH1F*> h_ho_channel_charge (n_ho_channels, 0);
  
  char rbx_name[10];
  char hist_name[200];

  for (int i = 0; i < n_hbheho_rbx; ++i){
    std::string rbx_name = getHORBXNameFromIndex(i);
    sprintf(hist_name, "%s_energy", rbx_name.c_str());
    std::cout << i << "\t" << hist_name << std::endl;
    h_ho_rbx_charge[i] = makeTH1F ( hist_name, 1000, -100, 10000 );
  }

  for ( int i = 0; i < n_ho_channels; ++i){
    int side, ieta, iphi, depth;
    map.getCoordinates(i, 3, side, ieta, iphi, depth);
    sprintf(hist_name, "HO_Side%d_IEta%d_IPhi%d_Depth%d_energy", side, ieta, iphi, depth);
    h_ho_channel_charge[i] = makeTH1F(hist_name, 1000, -100, 10000 );
  }

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 100 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hoDigis (new Collection(*tuple_tree, tuple_tree -> HODigiIEta -> size()));

    int nHODigis = hoDigis -> GetSize();
    for (int iHODigi = 0; iHODigi < nHODigis; ++iHODigi){
      HODigi hoDigi = hoDigis -> GetConstituent<HODigi>(iHODigi);

      // Collect values
      float  energy = hoDigi.energy();
      float  charge = hoDigi.fcTotal();
      int    ieta   = hoDigi.ieta();
      int    iphi   = hoDigi.iphi();
      int    depth  = hoDigi.depth();
      int    det    = 3;
      int    side   = hoDigi.ieta() / abs(hoDigi.ieta());
      int    rbx_side = map.getRBXSide( det, side, abs(ieta), iphi, depth );
      int    rbx    = map.getRBXNumber( det, side, abs(ieta), iphi, depth );
      int    fed    = map.getFEDNumber( det, side, abs(ieta), iphi, depth );
      int    idet   = det - 1;
      int    iside  = rbx_side + 1;
      int    index  = map.getIndex    ( det, side, abs(ieta), iphi, depth );
      if ( det != 3 ) iside /= 2;
      
      int rbx_index;
      if      ( det <= 2 ) rbx_index = (iside * (n_hbheho_rbx / 2)) + rbx - 1;
      else if ( det == 3 ) rbx_index = getHORBXIndex ( rbx_side, rbx );
      else if ( det == 4 ) rbx_index = (iside * (n_hf_rbx     / 2)) + rbx - 1;

      h_ho_rbx_charge[rbx_index] -> Fill ( charge );
      h_ho_channel_charge[index] -> Fill ( charge );
      
    }
  }
}
