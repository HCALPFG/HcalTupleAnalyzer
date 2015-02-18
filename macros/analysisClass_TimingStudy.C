#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HLTFilterObjectCollectionHelper.h"

#include "HLTFilterObject.h"
#include "HBHECosmicDigi.h"
#include "HOCosmicDigi.h"
#include "CosmicMuon.h"

void analysisClass::loop(){
  
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
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiDepth"              , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiRecEnergy"          , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiRecTime"            , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiFC"                 , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HBHECosmicDigiSize"               , kTRUE );
							                     	     
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiIEta"                 , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HOCosmicDigiIPhi"                 , kTRUE );
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
  // Make histograms
  //--------------------------------------------------------------------------------

  TH1F * ho_cosmic_timing_dtFired     = makeTH1F("ho_cosmic_timing_dtFired"    , 50,-10,40);
  TH1F * ho_cosmic_timing_hoFired     = makeTH1F("ho_cosmic_timing_hoFired"    , 50,-10,40);
  TH1F * ho_cosmic_timing_hodtFired   = makeTH1F("ho_cosmic_timing_hodtFired"  , 50,-10,40);

  TH1F * hbhe_cosmic_timing_dtFired   = makeTH1F("hbhe_cosmic_timing_dtFired"  , 50,-10,40);
  TH1F * hbhe_cosmic_timing_hoFired   = makeTH1F("hbhe_cosmic_timing_hoFired"  , 50,-10,40);
  TH1F * hbhe_cosmic_timing_hodtFired = makeTH1F("hbhe_cosmic_timing_hodtFired", 50,-10,40);

  TH1F * ho_cosmic_energy_dtFired     = makeTH1F("ho_cosmic_energy_dtFired"    , 100, 0, 10);
  TH1F * ho_cosmic_energy_hoFired     = makeTH1F("ho_cosmic_energy_hoFired"    , 100, 0, 10);
  TH1F * ho_cosmic_energy_hodtFired   = makeTH1F("ho_cosmic_energy_hodtFired"  , 100, 0, 10);

  TH1F * hbhe_cosmic_energy_dtFired   = makeTH1F("hbhe_cosmic_energy_dtFired"  , 100, 0, 10);
  TH1F * hbhe_cosmic_energy_hoFired   = makeTH1F("hbhe_cosmic_energy_hoFired"  , 100, 0, 10);
  TH1F * hbhe_cosmic_energy_hodtFired = makeTH1F("hbhe_cosmic_energy_hodtFired", 100, 0, 10);

  TH2F * hbhe_cosmic_energy_vs_timing_dtFired   = makeTH2F("hbhe_cosmic_energy_vs_timing_dtFired"  , 100, 0, 10, 50,-10,40 );
  TH2F * hbhe_cosmic_energy_vs_timing_hoFired   = makeTH2F("hbhe_cosmic_energy_vs_timing_hoFired"  , 100, 0, 10, 50,-10,40 );
  TH2F * hbhe_cosmic_energy_vs_timing_hodtFired = makeTH2F("hbhe_cosmic_energy_vs_timing_hodtFired", 100, 0, 10, 50,-10,40 );

  TH2F * ho_cosmic_energy_vs_timing_dtFired   = makeTH2F("ho_cosmic_energy_vs_timing_dtFired"  , 100, 0, 10, 50,-10,40 );
  TH2F * ho_cosmic_energy_vs_timing_hoFired   = makeTH2F("ho_cosmic_energy_vs_timing_hoFired"  , 100, 0, 10, 50,-10,40 );
  TH2F * ho_cosmic_energy_vs_timing_hodtFired = makeTH2F("ho_cosmic_energy_vs_timing_hodtFired", 100, 0, 10, 50,-10,40 );

  TH2F * hbhe_cosmic_occupancy_depth1_dtFired   = makeTH2F("hbhe_cosmic_occupancy_depth1_dtFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth1_hoFired   = makeTH2F("hbhe_cosmic_occupancy_depth1_hoFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth1_hodtFired = makeTH2F("hbhe_cosmic_occupancy_depth1_hodtFired", 59, -29.5, 29.5, 72, 0.5, 72.5 );

  TH2F * hbhe_cosmic_occupancy_depth2_dtFired   = makeTH2F("hbhe_cosmic_occupancy_depth2_dtFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth2_hoFired   = makeTH2F("hbhe_cosmic_occupancy_depth2_hoFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth2_hodtFired = makeTH2F("hbhe_cosmic_occupancy_depth2_hodtFired", 59, -29.5, 29.5, 72, 0.5, 72.5 );

  TH2F * hbhe_cosmic_occupancy_depth3_dtFired   = makeTH2F("hbhe_cosmic_occupancy_depth3_dtFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth3_hoFired   = makeTH2F("hbhe_cosmic_occupancy_depth3_hoFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth3_hodtFired = makeTH2F("hbhe_cosmic_occupancy_depth3_hodtFired", 59, -29.5, 29.5, 72, 0.5, 72.5 );

  TH2F * ho_cosmic_occupancy_dtFired     = makeTH2F("ho_cosmic_occupancy_dtFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_hoFired     = makeTH2F("ho_cosmic_occupancy_hoFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_hodtFired   = makeTH2F("ho_cosmic_occupancy_hodtFired"  , 31, -15.5, 15.5, 72, 0.5, 72.5 );

  TH1F * ho_cosmic_recHitTiming_dtFired  = makeTH1F("ho_cosmic_recHitTiming_dtFired"    , 200, -100, 100);
  TH1F * ho_cosmic_recHitTiming_hoFired  = makeTH1F("ho_cosmic_recHitTiming_hoFired"    , 200, -100, 100);
  TH1F * ho_cosmic_recHitTiming_hodtFired  = makeTH1F("ho_cosmic_recHitTiming_hodtFired"    , 200, -100, 100);

  TH1F * hbhe_cosmic_recHitTiming_dtFired  = makeTH1F("hbhe_cosmic_recHitTiming_dtFired"    , 200, -100, 100);
  TH1F * hbhe_cosmic_recHitTiming_hoFired  = makeTH1F("hbhe_cosmic_recHitTiming_hoFired"    , 200, -100, 100);
  TH1F * hbhe_cosmic_recHitTiming_hodtFired  = makeTH1F("hbhe_cosmic_recHitTiming_hodtFired"    , 200, -100, 100);
  
  //--------------------------------------------------------------------------------
  // Trigger names
  //--------------------------------------------------------------------------------

  std::string dt_trigger_name("HLT_L1SingleMuOpen_v6");
  std::string ho_trigger_name("HLT_L1Tech_HBHEHO_totalOR_v5");

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 100 == 0 ) 
      std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    //--------------------------------------------------------------------------------
    // Get helper
    //--------------------------------------------------------------------------------
    
    HLTFilterObjectCollectionHelper helper (*tuple_tree);

    //-----------------------------------------------------------------
    // Did the trigger fire?
    //-----------------------------------------------------------------

    getTriggers ( tuple_tree -> HLTKey, 
		  tuple_tree -> HLTInsideDatasetTriggerNames, 
		  tuple_tree -> HLTInsideDatasetTriggerDecisions,  
		  tuple_tree -> HLTInsideDatasetTriggerPrescales ) ; 
    
    bool dt_trigger_fired = triggerFired ( dt_trigger_name.c_str() );
    bool ho_trigger_fired = triggerFired ( ho_trigger_name.c_str() );
    
    if ( (!ho_trigger_fired) && (!dt_trigger_fired)) continue;

    //-----------------------------------------------------------------
    // If the trigger fired, find the muon that fired it
    //-----------------------------------------------------------------

    CollectionPtr cosmicMuons ( new Collection(*tuple_tree, tuple_tree -> CosmicMuonPt -> size()));

    if ( dt_trigger_fired ){
      CollectionPtr hltMuons = helper.GetHLTFilterObjects("hltL1MuOpenL1Filtered0");
      // hltMuons -> examine<HLTFilterObject>("HLT muons");
      // cosmicMuons -> examine<CosmicMuon>("Cosmic muons");
    }

    //-----------------------------------------------------------------
    // Fill HBHE histograms
    //-----------------------------------------------------------------
      
    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHECosmicDigiIEta -> size()));

    int nHBHE = hbheDigis -> GetSize();

    for (int iHBHE = 0; iHBHE < nHBHE; ++iHBHE){
      HBHECosmicDigi hbheDigi = hbheDigis -> GetConstituent<HBHECosmicDigi>(iHBHE);
      
      if ( ho_trigger_fired && !dt_trigger_fired ) {
	hbhe_cosmic_energy_hoFired   -> Fill ( hbheDigi.energy() );
	hbhe_cosmic_timing_hoFired   -> Fill ( hbheDigi.time()   );
	hbhe_cosmic_energy_vs_timing_hoFired -> Fill ( hbheDigi.energy(), hbheDigi.time() );
  hbhe_cosmic_recHitTiming_hoFired->Fill(hbheDigi.recHitTime());
	if (hbheDigi.depth() == 1 ) hbhe_cosmic_occupancy_depth1_hoFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 2 ) hbhe_cosmic_occupancy_depth2_hoFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 3 ) hbhe_cosmic_occupancy_depth3_hoFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
      }

      if ( dt_trigger_fired && !ho_trigger_fired ) {
	hbhe_cosmic_energy_dtFired   -> Fill ( hbheDigi.energy() );
	hbhe_cosmic_timing_dtFired   -> Fill ( hbheDigi.time()   );
	hbhe_cosmic_energy_vs_timing_dtFired -> Fill ( hbheDigi.energy(), hbheDigi.time() );
  hbhe_cosmic_recHitTiming_dtFired->Fill(hbheDigi.recHitTime());
	if (hbheDigi.depth() == 1 ) hbhe_cosmic_occupancy_depth1_dtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 2 ) hbhe_cosmic_occupancy_depth2_dtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 3 ) hbhe_cosmic_occupancy_depth3_dtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
      }
      
      if ( dt_trigger_fired &&  ho_trigger_fired ) {
	hbhe_cosmic_energy_hodtFired -> Fill ( hbheDigi.energy() );
	hbhe_cosmic_timing_hodtFired -> Fill ( hbheDigi.time()   );
	hbhe_cosmic_energy_vs_timing_hodtFired -> Fill ( hbheDigi.energy(), hbheDigi.time() );
  hbhe_cosmic_recHitTiming_hodtFired->Fill(hbheDigi.recHitTime());
	if (hbheDigi.depth() == 1 ) hbhe_cosmic_occupancy_depth1_hodtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 2 ) hbhe_cosmic_occupancy_depth2_hodtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 3 ) hbhe_cosmic_occupancy_depth3_hodtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
      }
    }

    //-----------------------------------------------------------------
    // Fill HO histograms
    //-----------------------------------------------------------------

    CollectionPtr hoDigis (new Collection(*tuple_tree, tuple_tree -> HOCosmicDigiIEta -> size()));

    int nHO = hoDigis -> GetSize();

    for (int iHO = 0; iHO < nHO; ++iHO){
      HOCosmicDigi hoDigi = hoDigis -> GetConstituent<HOCosmicDigi>(iHO);
      
      if ( ho_trigger_fired && !dt_trigger_fired ) {
	ho_cosmic_energy_hoFired   -> Fill ( hoDigi.energy() );
	ho_cosmic_timing_hoFired   -> Fill ( hoDigi.time()   );
	ho_cosmic_energy_vs_timing_hoFired -> Fill ( hoDigi.energy(), hoDigi.time() );
	ho_cosmic_occupancy_hoFired -> Fill ( hoDigi.ieta(), hoDigi.iphi());
  ho_cosmic_recHitTiming_hoFired->Fill(hoDigi.recHitTime());
      }

      if ( dt_trigger_fired && !ho_trigger_fired ) {
	ho_cosmic_energy_dtFired   -> Fill ( hoDigi.energy() );
	ho_cosmic_timing_dtFired   -> Fill ( hoDigi.time()   );
	ho_cosmic_energy_vs_timing_dtFired -> Fill ( hoDigi.energy(), hoDigi.time() );
	ho_cosmic_occupancy_dtFired -> Fill ( hoDigi.ieta(), hoDigi.iphi());
  ho_cosmic_recHitTiming_dtFired->Fill(hoDigi.recHitTime());
      }
      
      if ( dt_trigger_fired &&  ho_trigger_fired ) {
	ho_cosmic_energy_hodtFired -> Fill ( hoDigi.energy() );
	ho_cosmic_timing_hodtFired -> Fill ( hoDigi.time()   );
	ho_cosmic_energy_vs_timing_hodtFired -> Fill ( hoDigi.energy(), hoDigi.time() );
	ho_cosmic_occupancy_hodtFired -> Fill ( hoDigi.ieta(), hoDigi.iphi());
  ho_cosmic_recHitTiming_hodtFired->Fill(hoDigi.recHitTime());
      }
      
    }
  }
}
