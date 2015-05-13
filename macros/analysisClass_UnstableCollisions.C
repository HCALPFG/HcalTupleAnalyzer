#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"
#include "HFDigi.h"
#include "HODigi.h"
#include "RBXMap.h"
#include <fstream>


void analysisClass::loop(){
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();
  std::cout << "n events = " << n_events << std::endl;

  //--------------------------------------------------------------------------------
  // RBX map
  //--------------------------------------------------------------------------------
  
  RBXMap map;
  map.LoadFile ( "data/emaps/HCALmapHBEF_E.txt" );
  map.LoadFile ( "data/emaps/HCALmapHO_G.txt" );
  
  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);

  
  tuple_tree -> fChain -> SetBranchStatus("HLTKey", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerNames", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerDecisions", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerPrescales", kTRUE);


  tuple_tree -> fChain -> SetBranchStatus("run", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("bcn", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSubdet", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRawID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPresamples", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize", kTRUE);

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------

  std::map<int, TH1F*> m_hbhe_id_to_timing;
  std::map<std::string, TH1F*> m_rbx_to_timing;

  TH1F * h_ls = makeTH1F("lumiSection", 600, 0, 150);
  TH1F * h_energy = makeTH1F( "energy", 1000, 0, 50);
  TH1F * h_time = makeTH1F( "time", 200, -100, 100);
  TH1F * h_time_HBHEa = makeTH1F( "time_HBHEa", 200, -100, 100);
  TH1F * h_time_HBHEb = makeTH1F( "time_HBHEb", 200, -100, 100);
  TH1F * h_time_HBHEc = makeTH1F( "time_HBHEc", 200, -100, 100);
  TH1F * h_bcn = makeTH1F("bcn", 300, 0.5, 300.5);
  std::vector<TH2F*> h_occupancy (5);

  char hist_name[100];
  for (int i = 1; i <=4; ++i){
    sprintf(hist_name,"occupancy_depth%d", i);
    h_occupancy[i] = makeTH2F(hist_name, 85, -42.5, 42.5, 72, 0.5, 72.5 );
  }
  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 100 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    h_ls -> Fill ( tuple_tree -> ls );
    h_bcn -> Fill ( tuple_tree -> bcn );

    
    //-----------------------------------------------------------------
    // Did the trigger fire?
    //-----------------------------------------------------------------

    getTriggers ( tuple_tree -> HLTKey, 			
                  tuple_tree -> HLTInsideDatasetTriggerNames, 	
                  tuple_tree -> HLTInsideDatasetTriggerDecisions,  
                  tuple_tree -> HLTInsideDatasetTriggerPrescales ) ;
    
    //-----------------------------------------------------------------
    // Collections of HBHE, HF, HO digis
    //-----------------------------------------------------------------

    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    
    int nHBHEDigis = hbheDigis -> GetSize();
    std::map<int, TH1F*>::iterator it;
    std::map<std::string, TH1F*>::iterator it_rbx;
    std::string rbx_name;
    
    
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);
      if ( hbheDigi.energy() < 5.0 ) continue;
      
      rbx_name = map.getRBXString ( hbheDigi.subdet(), hbheDigi.ieta() / abs(hbheDigi.ieta()), abs(hbheDigi.ieta()), hbheDigi.iphi(), hbheDigi.depth() );

      it_rbx = m_rbx_to_timing.find ( rbx_name );
      if ( it_rbx == m_rbx_to_timing.end() ){
	m_rbx_to_timing[rbx_name] = makeTH1F(rbx_name.c_str(), 200, -100, 100);
      }
      m_rbx_to_timing[rbx_name] -> Fill ( hbheDigi.recHitTime());

      if      ( hbheDigi.iphi() >= 3  && hbheDigi.iphi() <= 26 ) h_time_HBHEa -> Fill ( hbheDigi.recHitTime() );
      else if ( hbheDigi.iphi() >= 27 && hbheDigi.iphi() <= 50 ) h_time_HBHEb -> Fill ( hbheDigi.recHitTime() );
      else                                                       h_time_HBHEc -> Fill ( hbheDigi.recHitTime() );

      h_occupancy[hbheDigi.depth()] -> Fill(hbheDigi.ieta(), hbheDigi.iphi());
      
      h_energy -> Fill ( hbheDigi.energy() );
      h_time   -> Fill ( hbheDigi.recHitTime());
    }
  }
}
