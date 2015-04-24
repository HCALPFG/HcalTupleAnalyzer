
#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HLTFilterObjectCollectionHelper.h"

#include "HLTFilterObject.h"
#include "HBHECosmicDigi.h"
#include "HOCosmicDigi.h"
#include "CosmicMuon.h"

void analysisClass::loop(){
  //--------------------------------------------------------------------------------
  // Configurables
  //--------------------------------------------------------------------------------
  std::string dt_trigger_name("HLT_L1SingleMuOpen_v6");
  // std::map< UInt_t ,std::map< std::string , TH2F* > > HistosTH2;
  std::map< int ,std::map< std::string , TH2F* > > HistosTH2;

  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------
  
  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();

  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*"                                , kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerNames"     , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerDecisions" , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerPrescales" , kTRUE );
  
  tuple_tree -> fChain -> SetBranchStatus("HLTFilterName"                    , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HLTFilterObjId"                   , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HLTFilterObjPt"                   , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HLTFilterObjEta"                  , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HLTFilterObjPhi"                  , kTRUE );
  							                     	     
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiIEta"               , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiIPhi"               , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiEta"               , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiPhi"               , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiDepth"              , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiRecEnergy"          , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiRecTime"            , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiFC"                 , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiSize"               , kTRUE );
							                     	     
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiIEta"                 , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiIPhi"                 , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiEta"                 , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiPhi"                 , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiDepth"                , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiRecEnergy"            , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiRecTime"              , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiFC"                   , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiSize"                 , kTRUE );
  /*
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta"                     , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi"                     , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDepth"                    , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy"                , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecTime"                  , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC"                       , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize"                     , kTRUE );
							                           	     
  tuple_tree -> fChain -> SetBranchStatus("HODigiIEta"                       , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiIPhi"                       , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiDepth"                      , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiRecEnergy"                  , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiRecTime"                    , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiFC"                         , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiSize"                       , kTRUE );
  */
  tuple_tree -> fChain -> SetBranchStatus("CosmicMuonPt"                     , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("CosmicMuonEta"                    , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("CosmicMuonPhi"                    , kTRUE );

  tuple_tree -> fChain -> SetBranchStatus("run"				     , kTRUE );

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  for (int i=0; i < n_events; ++i){ 
    // if (i > 10000) continue;
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 100 == 0 ){ 
      std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;
    };

    //-----------------------------------------------------------------
    // Define histograms for each run
    //-----------------------------------------------------------------
    // Get Run Number
    // UInt_t RunNumber = tuple_tree -> run ;
    int RunNumber = tuple_tree -> run ;
    if (HistosTH2.find(RunNumber) == HistosTH2.end()){
      std::map < std::string, TH2F* > HistosForEachRun;
      HistosForEachRun["HBHE_RecHitTimingVsIphi_plusPhi"] = makeTH2F(("HBHE_RecHitTimingVsIphi_plusPhi_"+std::to_string(RunNumber)).c_str(), 200,-100,100,72, 0.5, 72.5  );
      HistosForEachRun["HBHE_RecHitTimingVsIphi_plusPhi"] -> SetTitle( ("#phi > 0, Run Number "+std::to_string(RunNumber)+" ; RecHit Timing  ; i#phi ").c_str() ); 
      
      HistosForEachRun["HBHE_RecHitTimingVsIphi_minusPhi"] = makeTH2F(("HBHE_RecHitTimingVsIphi_minusPhi_"+std::to_string(RunNumber)).c_str(), 200,-100,100,72, 0.5, 72.5   );
      HistosForEachRun["HBHE_RecHitTimingVsIphi_minusPhi"] -> SetTitle( ("#phi < 0, Run Number "+std::to_string(RunNumber)+" ; RecHit Timing  ; i#phi ").c_str() ); 
      
      HistosTH2.insert( std::pair< int, std::map< std::string ,TH2F* > > ( RunNumber, HistosForEachRun) );
    };

    //-----------------------------------------------------------------
    // Check if DT Trigger has been fired 
    //-----------------------------------------------------------------

    getTriggers ( tuple_tree -> HLTKey, 
		  tuple_tree -> HLTInsideDatasetTriggerNames, 
		  tuple_tree -> HLTInsideDatasetTriggerDecisions,  
		  tuple_tree -> HLTInsideDatasetTriggerPrescales ) ; 

    bool dt_trigger_fired = triggerFired ( dt_trigger_name.c_str() );

    if (not dt_trigger_fired) continue;

    //-----------------------------------------------------------------
    // Read HBHEDigi
    //-----------------------------------------------------------------

    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHECosmicDigiIEta -> size()));
    int nHBHE = hbheDigis -> GetSize();

    for (int iHBHE = 0; iHBHE < nHBHE; ++iHBHE){
       HBHECosmicDigi hbheDigi = hbheDigis -> GetConstituent<HBHECosmicDigi>(iHBHE);
       if (hbheDigi.phi() > 0.){
         HistosTH2[RunNumber]["HBHE_RecHitTimingVsIphi_plusPhi"] -> Fill( hbheDigi.recHitTime(),hbheDigi.iphi()  );
       };
       if (hbheDigi.phi() < 0.){
         HistosTH2[RunNumber]["HBHE_RecHitTimingVsIphi_minusPhi"] -> Fill( hbheDigi.recHitTime(),hbheDigi.iphi()  );
       };
    };
    

  };

};
