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
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiZ", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSubdet", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRawID", kTRUE);

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------

  TH1F * h_ls = makeTH1F("lumiSection", 600, 0, 150);
  TH1F * h_energy = makeTH1F( "energy", 1000, 0, 50);
  TH1F * h_time = makeTH1F( "time", 200, -100, 100);
  TH1F * h_time_diff = makeTH1F( "time_diff", 200, -100, 100);
  TH2F * h_time_vs_eta = makeTH2F( "time_vs_eta", 100, -20, 20, 100, -5, 5);
  TH2F * h_time_vs_z = makeTH2F( "time_vs_z", 100, -20, 20, 100, -500, 500);
  TH2F * h_time_vs_energy = makeTH2F( "time_vs_energy", 100, -20, 20, 100, -5, 45);
  
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
    if ( (i + 1) % 1000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

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
    
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);
      if ( hbheDigi.energy() < 5.0 ) continue;
      if ( hbheDigi.iphi() == 2 && hbheDigi.ieta() < 0) continue;


      double t_expected_splash = 0.031 * hbheDigi.z() + 0.22;
      double t_observed = hbheDigi.recHitTime();
      double t_diff = t_observed - t_expected_splash;
      
      if ( fabs(t_diff) < 20. ) continue;

      h_occupancy[hbheDigi.depth()] -> Fill(hbheDigi.ieta(), hbheDigi.iphi());
      
      h_energy -> Fill ( hbheDigi.energy() );
      h_time   -> Fill ( hbheDigi.recHitTime());
      h_time_diff -> Fill ( t_diff ) ;
      h_time_vs_eta -> Fill ( hbheDigi.recHitTime(), hbheDigi.eta());
      h_time_vs_z -> Fill ( hbheDigi.recHitTime(), hbheDigi.z());
      h_time_vs_energy -> Fill ( hbheDigi.recHitTime(), hbheDigi.energy());
    }
  }
}
