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
  int nEventToDisplay = 1000;
  std::string dt_trigger_name("HLT_L1SingleMuOpen_v6");
  std::map< std::string , std::vector<TH2F*>> HistosPerEvent;

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


  //--------------------------------------------------------------------------------
  // Make array of histos  
  //--------------------------------------------------------------------------------
  HistosPerEvent["RecHitTiming"].reserve(nEventToDisplay);
  HistosPerEvent["RecHitEnergy"].reserve(nEventToDisplay);

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  // Display only predefined number of events
  for (int i=0; i < nEventToDisplay; ++i){ 

    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 100 == 0 ) 
      std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

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
    // Define histograms per event
    //-----------------------------------------------------------------
    HistosPerEvent["RecHitTiming"][i] = makeTH2F(("ieta_iphi_rechitTiming_"+std::to_string(i)).c_str(),81, -40.5, 40.5, 72, 0.5, 72.5);
    HistosPerEvent["RecHitTiming"][i]->SetTitle("; i#eta ; i#phi ");
    HistosPerEvent["RecHitEnergy"][i] = makeTH2F(("ieta_iphi_Energy_"+std::to_string(i)).c_str(),81, -40.5, 40.5, 72, 0.5, 72.5);
    HistosPerEvent["RecHitEnergy"][i]->SetTitle("; i#eta ; i#phi ");


    //-----------------------------------------------------------------
    // Read HBHEDigi
    //-----------------------------------------------------------------

    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHECosmicDigiIEta -> size()));
    int nHBHE = hbheDigis -> GetSize();

    for (int iHBHE = 0; iHBHE < nHBHE; ++iHBHE){
      HBHECosmicDigi hbheDigi = hbheDigis -> GetConstituent<HBHECosmicDigi>(iHBHE);
       HistosPerEvent["RecHitTiming"][i] ->Fill( hbheDigi.ieta(),hbheDigi.iphi(),hbheDigi.recHitTime()  );
       HistosPerEvent["RecHitEnergy"][i] ->Fill(hbheDigi.ieta(),hbheDigi.iphi(),hbheDigi.energy());
    };
    

  };

};
