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
  // Make histograms
  //--------------------------------------------------------------------------------

//===============================
// ieta Plot
//===============================
  TH1F * hbhe_cosmic_ieta_dtFired = makeTH1F("hbhe_cosmic_ieta_dtFired",81,-40.5,40.5); 
  
  // Special Plot for validation	  
  TH1F * hbhe_cosmic_ieta_minusphi_TimingPlus20To5_dtFired = makeTH1F("hbhe_cosmic_ieta_minusphi_TimingPlus20To5_dtFired",81,-40.5,40.5);
  TH1F * hbhe_cosmic_ieta_minusphi_TimingMinus20To5_dtFired = makeTH1F("hbhe_cosmic_ieta_minusphi_TimingMinus20To5_dtFired",81,-40.5,40.5);
  TH1F * hbhe_cosmic_ieta_plusphi_TimingMinus25ToMinus15_dtFired = makeTH1F("hbhe_cosmic_ieta_plusphi_TimingMinus25ToMinus15_dtFired",81,-40.5,40.5);
  TH1F * hbhe_cosmic_ieta_plusphi_TimingMinus15To5_dtFired = makeTH1F("hbhe_cosmic_ieta_plusphi_TimingMinus15To5_dtFired",81,-40.5,40.5);
  TH1F * hbhe_cosmic_ieta_plusphi_TimingMinus40ToMinus25_dtFired = makeTH1F("hbhe_cosmic_ieta_plusphi_TimingMinus40ToMinus25_dtFired",81,-40.5,40.5);
  TH1F * hbhe_cosmic_ieta_plusphi_TimingMinus25To5_dtFired = makeTH1F("hbhe_cosmic_ieta_plusphi_TimingMinus25To5_dtFired",81,-40.5,40.5);


//===============================
// Timing Plot
//===============================


  TH1F * ho_cosmic_timing_dtFired     = makeTH1F("ho_cosmic_timing_dtFired"    , 100, 0, 10);
  TH1F * ho_cosmic_timing_hoFired     = makeTH1F("ho_cosmic_timing_hoFired"    , 100, 0, 10);
  TH1F * ho_cosmic_timing_hodtFired   = makeTH1F("ho_cosmic_timing_hodtFired"  , 100, 0, 10);

  TH1F * ho_cosmic_rhtiming_dtFired     = makeTH1F("ho_cosmic_rhtiming_dtFired"    , 200, -100, 100);
  TH1F * ho_cosmic_rhtiming_hoFired     = makeTH1F("ho_cosmic_rhtiming_hoFired"    , 200, -100, 100);
  TH1F * ho_cosmic_rhtiming_hodtFired   = makeTH1F("ho_cosmic_rhtiming_hodtFired"  , 200, -100, 100);

  TH1F * ho_top_cosmic_timing_dtFired     = makeTH1F("ho_top_cosmic_timing_dtFired"    , 100, 0, 10);
  TH1F * ho_top_cosmic_timing_hoFired     = makeTH1F("ho_top_cosmic_timing_hoFired"    , 100, 0, 10);
  TH1F * ho_top_cosmic_timing_hodtFired   = makeTH1F("ho_top_cosmic_timing_hodtFired"  , 100, 0, 10);

  TH1F * ho_bot_cosmic_timing_dtFired     = makeTH1F("ho_bot_cosmic_timing_dtFired"    , 100, 0, 10);
  TH1F * ho_bot_cosmic_timing_hoFired     = makeTH1F("ho_bot_cosmic_timing_hoFired"    , 100, 0, 10);
  TH1F * ho_bot_cosmic_timing_hodtFired   = makeTH1F("ho_bot_cosmic_timing_hodtFired"  , 100, 0, 10);

  TH1F * hbhe_cosmic_timing_dtFired   = makeTH1F("hbhe_cosmic_timing_dtFired"  , 100, 0, 10);
  TH1F * hbhe_cosmic_timing_hoFired   = makeTH1F("hbhe_cosmic_timing_hoFired"  , 100, 0, 10);
  TH1F * hbhe_cosmic_timing_hodtFired = makeTH1F("hbhe_cosmic_timing_hodtFired", 100, 0, 10);

  TH1F * ho_cosmic_recHitTiming_dtFired  = makeTH1F("ho_cosmic_recHitTiming_dtFired"    , 200, -100, 100);
  TH1F * ho_cosmic_recHitTiming_hoFired  = makeTH1F("ho_cosmic_recHitTiming_hoFired"    , 200, -100, 100);
  TH1F * ho_cosmic_recHitTiming_hodtFired  = makeTH1F("ho_cosmic_recHitTiming_hodtFired"    , 200, -100, 100);

  TH1F * hbhe_cosmic_recHitTiming_dtFired  = makeTH1F("hbhe_cosmic_recHitTiming_dtFired"    , 200, -100, 100);
  TH1F * hbhe_cosmic_recHitTiming_hoFired  = makeTH1F("hbhe_cosmic_recHitTiming_hoFired"    , 200, -100, 100);
  TH1F * hbhe_cosmic_recHitTiming_hodtFired  = makeTH1F("hbhe_cosmic_recHitTiming_hodtFired"    , 200, -100, 100);

//===============================
// Energy Plot
//===============================

  TH1F * ho_cosmic_energy_dtFired     = makeTH1F("ho_cosmic_energy_dtFired"    , 100, 0, 10);
  TH1F * ho_cosmic_energy_hoFired     = makeTH1F("ho_cosmic_energy_hoFired"    , 100, 0, 10);
  TH1F * ho_cosmic_energy_hodtFired   = makeTH1F("ho_cosmic_energy_hodtFired"  , 100, 0, 10);

  TH1F * hbhe_cosmic_energy_dtFired   = makeTH1F("hbhe_cosmic_energy_dtFired"  , 100, 0, 10);
  TH1F * hbhe_cosmic_energy_hoFired   = makeTH1F("hbhe_cosmic_energy_hoFired"  , 100, 0, 10);
  TH1F * hbhe_cosmic_energy_hodtFired = makeTH1F("hbhe_cosmic_energy_hodtFired", 100, 0, 10);

  TH2F * hbhe_cosmic_energy_vs_timing_dtFired   = makeTH2F("hbhe_cosmic_energy_vs_timing_dtFired"  , 100, 0, 10, 50,0,10 );
  TH2F * hbhe_cosmic_energy_vs_timing_hoFired   = makeTH2F("hbhe_cosmic_energy_vs_timing_hoFired"  , 100, 0, 10, 50,0,10 );
  TH2F * hbhe_cosmic_energy_vs_timing_hodtFired = makeTH2F("hbhe_cosmic_energy_vs_timing_hodtFired", 100, 0, 10, 50,0,10 );

  TH2F * ho_cosmic_energy_vs_timing_dtFired   = makeTH2F("ho_cosmic_energy_vs_timing_dtFired"  , 100, 0, 10, 50,0,10 );
  TH2F * ho_cosmic_energy_vs_timing_hoFired   = makeTH2F("ho_cosmic_energy_vs_timing_hoFired"  , 100, 0, 10, 50,0,10 );
  TH2F * ho_cosmic_energy_vs_timing_hodtFired = makeTH2F("ho_cosmic_energy_vs_timing_hodtFired", 100, 0, 10, 50,0,10 );

//===============================
// Occupancy Plot
//===============================

  TH2F * ho_cosmic_occupancy_dtFired     = makeTH2F("ho_cosmic_occupancy_dtFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_hoFired     = makeTH2F("ho_cosmic_occupancy_hoFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_hodtFired   = makeTH2F("ho_cosmic_occupancy_hodtFired"  , 31, -15.5, 15.5, 72, 0.5, 72.5 );

  TH2F * hbhe_cosmic_occupancy_dtFired     = makeTH2F("hbhe_cosmic_occupancy_dtFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_hoFired     = makeTH2F("hbhe_cosmic_occupancy_hbheFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_hodtFired   = makeTH2F("hbhe_cosmic_occupancy_hbhedtFired"  , 31, -15.5, 15.5, 72, 0.5, 72.5 );

  // Different Depths
  TH2F * hbhe_cosmic_occupancy_depth1_dtFired   = makeTH2F("hbhe_cosmic_occupancy_depth1_dtFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth1_hoFired   = makeTH2F("hbhe_cosmic_occupancy_depth1_hoFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth1_hodtFired = makeTH2F("hbhe_cosmic_occupancy_depth1_hodtFired", 59, -29.5, 29.5, 72, 0.5, 72.5 );

  TH2F * hbhe_cosmic_occupancy_depth2_dtFired   = makeTH2F("hbhe_cosmic_occupancy_depth2_dtFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth2_hoFired   = makeTH2F("hbhe_cosmic_occupancy_depth2_hoFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth2_hodtFired = makeTH2F("hbhe_cosmic_occupancy_depth2_hodtFired", 59, -29.5, 29.5, 72, 0.5, 72.5 );

  TH2F * hbhe_cosmic_occupancy_depth3_dtFired   = makeTH2F("hbhe_cosmic_occupancy_depth3_dtFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth3_hoFired   = makeTH2F("hbhe_cosmic_occupancy_depth3_hoFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_occupancy_depth3_hodtFired = makeTH2F("hbhe_cosmic_occupancy_depth3_hodtFired", 59, -29.5, 29.5, 72, 0.5, 72.5 );

  TH2F * ho_cosmic_occupancy_depth1_dtFired   = makeTH2F("ho_cosmic_occupancy_depth1_dtFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_depth1_hoFired   = makeTH2F("ho_cosmic_occupancy_depth1_hoFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_depth1_hodtFired = makeTH2F("ho_cosmic_occupancy_depth1_hodtFired", 59, -29.5, 29.5, 72, 0.5, 72.5 );

  TH2F * ho_cosmic_occupancy_depth2_dtFired   = makeTH2F("ho_cosmic_occupancy_depth2_dtFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_depth2_hoFired   = makeTH2F("ho_cosmic_occupancy_depth2_hoFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_depth2_hodtFired = makeTH2F("ho_cosmic_occupancy_depth2_hodtFired", 59, -29.5, 29.5, 72, 0.5, 72.5 );

  TH2F * ho_cosmic_occupancy_depth3_dtFired   = makeTH2F("ho_cosmic_occupancy_depth3_dtFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_depth3_hoFired   = makeTH2F("ho_cosmic_occupancy_depth3_hoFired"  , 59, -29.5, 29.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_depth3_hodtFired = makeTH2F("ho_cosmic_occupancy_depth3_hodtFired", 59, -29.5, 29.5, 72, 0.5, 72.5 );

  // Special Plots for validation
  TH2F * ho_cosmic_occupancy_noEnergy_dtFired     = makeTH2F("ho_cosmic_occupancy_noEnergy_dtFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_noEnergy_hoFired     = makeTH2F("ho_cosmic_occupancy_noEnergy_hoFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_noEnergy_hodtFired   = makeTH2F("ho_cosmic_occupancy_noEnergy_hodtFired"  , 31, -15.5, 15.5, 72, 0.5, 72.5 );

  TH2F * ho_cosmic_occupancy_badRHTiming_dtFired     = makeTH2F("ho_cosmic_occupancy_badRHTiming_dtFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_badRHTiming_hoFired     = makeTH2F("ho_cosmic_occupancy_badRHTiming_hoFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occupancy_badRHTiming_hodtFired   = makeTH2F("ho_cosmic_occupancy_badRHTiming_hodtFired"  , 31, -15.5, 15.5, 72, 0.5, 72.5 );

  
//===============================
// iphi vs recHitTiming Plot
//===============================

  TH2F * hbhe_cosmic_iphi_vs_recHitTiming_dtFired = makeTH2F("hbhe_cosmic_iphi_vs_recHitTiming_dtFired", 72, 0.5, 72.5 , 200, -100, 100 );
  TH2F * hbhe_cosmic_iphi_vs_recHitTiming_hoFired = makeTH2F("hbhe_cosmic_iphi_vs_recHitTiming_hoFired", 72, 0.5, 72.5 , 200, -100, 100 );
  TH2F * hbhe_cosmic_iphi_vs_recHitTiming_hodtFired = makeTH2F("hbhe_cosmic_iphi_vs_recHitTiming_hodtFired", 72, 0.5, 72.5 , 200, -100, 100 );
  
  TH2F * ho_cosmic_iphi_vs_recHitTiming_dtFired = makeTH2F("ho_cosmic_iphi_vs_recHitTiming_dtFired", 72, 0.5, 72.5 , 200, -100, 100 );
  TH2F * ho_cosmic_iphi_vs_recHitTiming_hoFired = makeTH2F("ho_cosmic_iphi_vs_recHitTiming_hoFired", 72, 0.5, 72.5 , 200, -100, 100 );
  TH2F * ho_cosmic_iphi_vs_recHitTiming_hodtFired = makeTH2F("ho_cosmic_iphi_vs_recHitTiming_hodtFired", 72, 0.5, 72.5 , 200, -100, 100 );

  // Special Plots for validation
  TH2F * hbhe_cosmic_recHitTiming_vs_iphi_minusphi_dtFired = makeTH2F("ho_cosmic_recHitTiming_vs_iphi_minusphi_dtFired", 200, -100, 100, 72, 0.5, 72.5 );
  TH2F * hbhe_cosmic_recHitTiming_vs_iphi_plusphi_dtFired = makeTH2F("ho_cosmic_recHitTiming_vs_iphi_plusphi_dtFired",200, -100, 100, 72, 0.5, 72.5 );

//===============================
// phi vs DigiTiming Plot
//===============================
  
  TH2F * hbhe_cosmic_phi_vs_timing_depth1_dtFired   = makeTH2F("hbhe_cosmic_phi_vs_timing_depth1_dtFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_timing_depth1_hoFired   = makeTH2F("hbhe_cosmic_phi_vs_timing_depth1_hoFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_timing_depth1_hodtFired = makeTH2F("hbhe_cosmic_phi_vs_timing_depth1_hodtFired", 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_timing_depth2_dtFired   = makeTH2F("hbhe_cosmic_phi_vs_timing_depth2_dtFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_timing_depth2_hoFired   = makeTH2F("hbhe_cosmic_phi_vs_timing_depth2_hoFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_timing_depth2_hodtFired = makeTH2F("hbhe_cosmic_phi_vs_timing_depth2_hodtFired", 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_timing_depth3_dtFired   = makeTH2F("hbhe_cosmic_phi_vs_timing_depth3_dtFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_timing_depth3_hoFired   = makeTH2F("hbhe_cosmic_phi_vs_timing_depth3_hoFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_timing_depth3_hodtFired = makeTH2F("hbhe_cosmic_phi_vs_timing_depth3_hodtFired", 72, -3.1416, 3.1416 , 200, -100, 100);

  TH2F * ho_cosmic_phi_vs_timing_dtFired     = makeTH2F("ho_cosmic_phi_vs_timing_dtFired"    , 72, -3.1416, 3.1416, 300, -10., 20. );
  TH2F * ho_cosmic_phi_vs_timing_hoFired     = makeTH2F("ho_cosmic_phi_vs_timing_hoFired"    , 72, -3.1416, 3.1416, 300, -10., 20. );
  TH2F * ho_cosmic_phi_vs_timing_hodtFired   = makeTH2F("ho_cosmic_phi_vs_timing_hodtFired"  , 72, -3.1416, 3.1416, 300, -10., 20. );


//===============================
// phi vs recHitTiming Plot
//===============================
  
  TH2F * hbhe_cosmic_phi_vs_recHitTiming_depth1_dtFired   = makeTH2F("hbhe_cosmic_phi_vs_recHitTiming_depth1_dtFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_recHitTiming_depth1_hoFired   = makeTH2F("hbhe_cosmic_phi_vs_recHitTiming_depth1_hoFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_recHitTiming_depth1_hodtFired = makeTH2F("hbhe_cosmic_phi_vs_recHitTiming_depth1_hodtFired", 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_recHitTiming_depth2_dtFired   = makeTH2F("hbhe_cosmic_phi_vs_recHitTiming_depth2_dtFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_recHitTiming_depth2_hoFired   = makeTH2F("hbhe_cosmic_phi_vs_recHitTiming_depth2_hoFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_recHitTiming_depth2_hodtFired = makeTH2F("hbhe_cosmic_phi_vs_recHitTiming_depth2_hodtFired", 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_recHitTiming_depth3_dtFired   = makeTH2F("hbhe_cosmic_phi_vs_recHitTiming_depth3_dtFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_recHitTiming_depth3_hoFired   = makeTH2F("hbhe_cosmic_phi_vs_recHitTiming_depth3_hoFired"  , 72, -3.1416, 3.1416 , 200, -100, 100);
  TH2F * hbhe_cosmic_phi_vs_recHitTiming_depth3_hodtFired = makeTH2F("hbhe_cosmic_phi_vs_recHitTiming_depth3_hodtFired", 72, -3.1416, 3.1416 , 200, -100, 100);


  TH2F * ho_cosmic_occuTiming_dtFired     = makeTH2F("ho_cosmic_occuTiming_dtFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occuTiming_hoFired     = makeTH2F("ho_cosmic_occuTiming_hoFired"    , 31, -15.5, 15.5, 72, 0.5, 72.5 );
  TH2F * ho_cosmic_occuTiming_hodtFired   = makeTH2F("ho_cosmic_occuTiming_hodtFired"  , 31, -15.5, 15.5, 72, 0.5, 72.5 );

//===============================
// DigiTiming vs RecHitTiming
//===============================
  
  TH2F * ho_cosmic_timing_recTiming_dtFired     = makeTH2F("ho_cosmic_timing_recTiming_dtFired"    , 200,-10,10,200,-100,100);
  TH2F * ho_cosmic_timing_recTiming_hoFired     = makeTH2F("ho_cosmic_timing_recTiming_hoFired"    , 200,-10,10,200,-100,100);
  TH2F * ho_cosmic_timing_recTiming_hodtFired   = makeTH2F("ho_cosmic_timing_recTiming_hodtFired"  , 200,-10,10,200,-100,100);

  TH2F * hbhe_cosmic_timing_recTiming_dtFired     = makeTH2F("hbhe_cosmic_timing_recTiming_dtFired"    , 200,-10,10,200,-100,100);
  TH2F * hbhe_cosmic_timing_recTiming_hoFired     = makeTH2F("hbhe_cosmic_timing_recTiming_hoFired"    , 200,-10,10,200,-100,100);
  TH2F * hbhe_cosmic_timing_recTiming_hodtFired   = makeTH2F("hbhe_cosmic_timing_recTiming_hodtFired"  , 200,-10,10,200,-100,100);

  // Special Plots for validation
  TH2F * ho_cosmic_timing_recTiming_noEnergy_dtFired     = makeTH2F("ho_cosmic_timing_recTiming_noEnergy_dtFired"    , 200,-10,10,200,-100,100);
  TH2F * ho_cosmic_timing_recTiming_noEnergy_hoFired     = makeTH2F("ho_cosmic_timing_recTiming_noEnergy_hoFired"    , 200,-10,10,200,-100,100);
  TH2F * ho_cosmic_timing_recTiming_noEnergy_hodtFired   = makeTH2F("ho_cosmic_timing_recTiming_noEnergy_hodtFired"  , 200,-10,10,200,-100,100);

  TH2F * ho_cosmic_timing_recTiming_withEnergyCut_dtFired     = makeTH2F("ho_cosmic_timing_recTiming_withEnergyCut_dtFired"    , 200,-10,10,200,-100,100);
  TH2F * ho_cosmic_timing_recTiming_withEnergyCut_hoFired     = makeTH2F("ho_cosmic_timing_recTiming_withEnergyCut_hoFired"    , 200,-10,10,200,-100,100);
  TH2F * ho_cosmic_timing_recTiming_withEnergyCut_hodtFired   = makeTH2F("ho_cosmic_timing_recTiming_withEnergyCut_hodtFired"  , 200,-10,10,200,-100,100);

//===============================
// fc vs timestamp
//===============================
  
  TH2F * ho_cosmic_timestamp_fc_dtFired = makeTH2F("ho_cosmic_timestamp_fc_dtFired",11,-0.5,10.5,100,0,10);
  TH2F * ho_cosmic_timestamp_fc_zeroTiming_dtFired = makeTH2F("ho_cosmic_timestamp_fc_zeroTiming_dtFired",11,-0.5,10.5,100,0,10);
  TH2F * ho_cosmic_timestamp_fc_nineTiming_dtFired = makeTH2F("ho_cosmic_timestamp_fc_nineTiming_dtFired",11,-0.5,10.5,100,0,10);

  TH2F * hbhe_cosmic_timestamp_fc_dtFired = makeTH2F("hbhe_cosmic_timestamp_fc_dtFired",11,-0.5,10.5,100,0,10);
  TH2F * hbhe_cosmic_timestamp_fc_zeroTiming_dtFired = makeTH2F("hbhe_cosmic_timestamp_fc_zeroTiming_dtFired",11,-0.5,10.5,100,0,10);
  TH2F * hbhe_cosmic_timestamp_fc_nineTiming_dtFired = makeTH2F("hbhe_cosmic_timestamp_fc_nineTiming_dtFired",11,-0.5,10.5,100,0,10);

  TH2F * ho_cosmic_timestamp_fc_hoFired = makeTH2F("ho_cosmic_timestamp_fc_hoFired",11,-0.5,10.5,100,0,10);
  TH2F * ho_cosmic_timestamp_fc_zeroTiming_hoFired = makeTH2F("ho_cosmic_timestamp_fc_zeroTiming_hoFired",11,-0.5,10.5,100,0,10);
  TH2F * ho_cosmic_timestamp_fc_nineTiming_hoFired = makeTH2F("ho_cosmic_timestamp_fc_nineTiming_hoFired",11,-0.5,10.5,100,0,10);

  TH2F * hbhe_cosmic_timestamp_fc_hoFired = makeTH2F("hbhe_cosmic_timestamp_fc_hoFired",11,-0.5,10.5,100,0,10);
  TH2F * hbhe_cosmic_timestamp_fc_zeroTiming_hoFired = makeTH2F("hbhe_cosmic_timestamp_fc_zeroTiming_hoFired",11,-0.5,10.5,100,0,10);
  TH2F * hbhe_cosmic_timestamp_fc_nineTiming_hoFired = makeTH2F("hbhe_cosmic_timestamp_fc_nineTiming_hoFired",11,-0.5,10.5,100,0,10);

  TH2F * ho_cosmic_timestamp_fc_hodtFired = makeTH2F("ho_cosmic_timestamp_fc_hodtFired",11,-0.5,10.5,100,0,10);
  TH2F * ho_cosmic_timestamp_fc_zeroTiming_hodtFired = makeTH2F("ho_cosmic_timestamp_fc_zeroTiming_hodtFired",11,-0.5,10.5,100,0,10);
  TH2F * ho_cosmic_timestamp_fc_nineTiming_hodtFired = makeTH2F("ho_cosmic_timestamp_fc_nineTiming_hodtFired",11,-0.5,10.5,100,0,10);

  TH2F * hbhe_cosmic_timestamp_fc_hodtFired = makeTH2F("hbhe_cosmic_timestamp_fc_hodtFired",11,-0.5,10.5,100,0,10);
  TH2F * hbhe_cosmic_timestamp_fc_zeroTiming_hodtFired = makeTH2F("hbhe_cosmic_timestamp_fc_zeroTiming_hodtFired",11,-0.5,10.5,100,0,10);
  TH2F * hbhe_cosmic_timestamp_fc_nineTiming_hodtFired = makeTH2F("hbhe_cosmic_timestamp_fc_nineTiming_hodtFired",11,-0.5,10.5,100,0,10);


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
  hbhe_cosmic_iphi_vs_recHitTiming_hoFired->Fill(hbheDigi.iphi(),hbheDigi.recHitTime());
  hbhe_cosmic_occupancy_hoFired -> Fill(hbheDigi.ieta(),hbheDigi.iphi());
	if (hbheDigi.depth() == 1 ) hbhe_cosmic_occupancy_depth1_hoFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 2 ) hbhe_cosmic_occupancy_depth2_hoFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 3 ) hbhe_cosmic_occupancy_depth3_hoFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());

	if (hbheDigi.depth() == 1 ) hbhe_cosmic_phi_vs_timing_depth1_hoFired -> Fill ( hbheDigi.phi(), hbheDigi.time());
	if (hbheDigi.depth() == 2 ) hbhe_cosmic_phi_vs_timing_depth2_hoFired -> Fill ( hbheDigi.phi(), hbheDigi.time());
	if (hbheDigi.depth() == 3 ) hbhe_cosmic_phi_vs_timing_depth3_hoFired -> Fill ( hbheDigi.phi(), hbheDigi.time());

  if (hbheDigi.depth() == 1 ) hbhe_cosmic_phi_vs_recHitTiming_depth1_hoFired -> Fill ( hbheDigi.phi(), hbheDigi.recHitTime());
  if (hbheDigi.depth() == 2 ) hbhe_cosmic_phi_vs_recHitTiming_depth2_hoFired -> Fill ( hbheDigi.phi(), hbheDigi.recHitTime());
  if (hbheDigi.depth() == 3 ) hbhe_cosmic_phi_vs_recHitTiming_depth3_hoFired -> Fill ( hbheDigi.phi(), hbheDigi.recHitTime());

  for (int i=0; i<hbheDigi.size(); i++){
    hbhe_cosmic_timestamp_fc_hoFired -> Fill(i,hbheDigi.fc(i));
    if (hbheDigi.time()<0.5){
      hbhe_cosmic_timestamp_fc_zeroTiming_hoFired -> Fill(i,hbheDigi.fc(i));
    };
    if (hbheDigi.time()>9.0){
      hbhe_cosmic_timestamp_fc_nineTiming_hoFired -> Fill(i,hbheDigi.fc(i));
    };
  };

      }

      if ( dt_trigger_fired && !ho_trigger_fired ) {
	hbhe_cosmic_energy_dtFired   -> Fill ( hbheDigi.energy() );
	hbhe_cosmic_timing_dtFired   -> Fill ( hbheDigi.time()   );
	hbhe_cosmic_energy_vs_timing_dtFired -> Fill ( hbheDigi.energy(), hbheDigi.time() );
  hbhe_cosmic_recHitTiming_dtFired->Fill(hbheDigi.recHitTime());
  hbhe_cosmic_iphi_vs_recHitTiming_dtFired->Fill(hbheDigi.iphi(),hbheDigi.recHitTime());
  hbhe_cosmic_occupancy_dtFired -> Fill(hbheDigi.ieta(),hbheDigi.iphi());

	if (hbheDigi.depth() == 1 ) hbhe_cosmic_occupancy_depth1_dtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 2 ) hbhe_cosmic_occupancy_depth2_dtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 3 ) hbhe_cosmic_occupancy_depth3_dtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());

	if (hbheDigi.depth() == 1 ) hbhe_cosmic_phi_vs_timing_depth1_dtFired -> Fill ( hbheDigi.phi(), hbheDigi.time());
	if (hbheDigi.depth() == 2 ) hbhe_cosmic_phi_vs_timing_depth2_dtFired -> Fill ( hbheDigi.phi(), hbheDigi.time());
	if (hbheDigi.depth() == 3 ) hbhe_cosmic_phi_vs_timing_depth3_dtFired -> Fill ( hbheDigi.phi(), hbheDigi.time());

  if (hbheDigi.depth() == 1 ) hbhe_cosmic_phi_vs_recHitTiming_depth1_dtFired -> Fill ( hbheDigi.phi(), hbheDigi.recHitTime());
  if (hbheDigi.depth() == 2 ) hbhe_cosmic_phi_vs_recHitTiming_depth2_dtFired -> Fill ( hbheDigi.phi(), hbheDigi.recHitTime());
  if (hbheDigi.depth() == 3 ) hbhe_cosmic_phi_vs_recHitTiming_depth3_dtFired -> Fill ( hbheDigi.phi(), hbheDigi.recHitTime());

  hbhe_cosmic_timing_recTiming_dtFired -> Fill(hbheDigi.time(),hbheDigi.recHitTime());


  // Validation Plots
  hbhe_cosmic_ieta_dtFired -> Fill(hbheDigi.ieta());

  if ((hbheDigi.phi() < 0) and (hbheDigi.recHitTime() < 20.) and (hbheDigi.recHitTime() > 5.)) {
    hbhe_cosmic_ieta_minusphi_TimingPlus20To5_dtFired->Fill(hbheDigi.ieta());
  };

  if ((hbheDigi.phi() < 0) and (hbheDigi.recHitTime() > -20.) and (hbheDigi.recHitTime() < 5.)) {
    hbhe_cosmic_ieta_minusphi_TimingMinus20To5_dtFired->Fill(hbheDigi.ieta());
  };
  if ((hbheDigi.phi() > 0) and (hbheDigi.recHitTime() < 5.) and (hbheDigi.recHitTime() > -15.)) {
    hbhe_cosmic_ieta_plusphi_TimingMinus15To5_dtFired->Fill(hbheDigi.ieta());
  };

 if ((hbheDigi.phi() > 0) and (hbheDigi.recHitTime() < -15.) and (hbheDigi.recHitTime() > -25.)) {
    hbhe_cosmic_ieta_plusphi_TimingMinus25ToMinus15_dtFired->Fill(hbheDigi.ieta());
  };

 if ((hbheDigi.phi() > 0) and (hbheDigi.recHitTime() < -25.) and (hbheDigi.recHitTime() > -40.)) {
    hbhe_cosmic_ieta_plusphi_TimingMinus40ToMinus25_dtFired->Fill(hbheDigi.ieta());
  };

 if ((hbheDigi.phi() > 0) and (hbheDigi.recHitTime() > -25.) and (hbheDigi.recHitTime() < 5.)) {
    hbhe_cosmic_ieta_plusphi_TimingMinus25To5_dtFired->Fill(hbheDigi.ieta());
  };

 if (hbheDigi.phi() < 0.){
    hbhe_cosmic_recHitTiming_vs_iphi_minusphi_dtFired -> Fill(hbheDigi.recHitTime(),hbheDigi.iphi());
 };

 if (hbheDigi.phi() > 0.){
    hbhe_cosmic_recHitTiming_vs_iphi_plusphi_dtFired -> Fill(hbheDigi.recHitTime(),hbheDigi.iphi());
 };
  
 //

  for (int i=0; i<hbheDigi.size(); i++){
    hbhe_cosmic_timestamp_fc_dtFired -> Fill(i,hbheDigi.fc(i));
    if (hbheDigi.time()<0.5){
      hbhe_cosmic_timestamp_fc_zeroTiming_dtFired -> Fill(i,hbheDigi.fc(i));
    };
    if (hbheDigi.time()>9.0){
      hbhe_cosmic_timestamp_fc_nineTiming_dtFired -> Fill(i,hbheDigi.fc(i));
    };
  };

      }
      
      if ( dt_trigger_fired &&  ho_trigger_fired ) {
	hbhe_cosmic_energy_hodtFired -> Fill ( hbheDigi.energy() );
	hbhe_cosmic_timing_hodtFired -> Fill ( hbheDigi.time()   );
	hbhe_cosmic_energy_vs_timing_hodtFired -> Fill ( hbheDigi.energy(), hbheDigi.time() );
  hbhe_cosmic_recHitTiming_hodtFired->Fill(hbheDigi.recHitTime());
  hbhe_cosmic_iphi_vs_recHitTiming_hodtFired->Fill(hbheDigi.iphi(),hbheDigi.recHitTime());
  hbhe_cosmic_occupancy_hodtFired -> Fill(hbheDigi.ieta(),hbheDigi.iphi());

	if (hbheDigi.depth() == 1 ) hbhe_cosmic_occupancy_depth1_hodtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 2 ) hbhe_cosmic_occupancy_depth2_hodtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());
	if (hbheDigi.depth() == 3 ) hbhe_cosmic_occupancy_depth3_hodtFired -> Fill ( hbheDigi.ieta(), hbheDigi.iphi());


	if (hbheDigi.depth() == 1 ) hbhe_cosmic_phi_vs_timing_depth1_hodtFired -> Fill ( hbheDigi.phi(), hbheDigi.time());
	if (hbheDigi.depth() == 2 ) hbhe_cosmic_phi_vs_timing_depth2_hodtFired -> Fill ( hbheDigi.phi(), hbheDigi.time());
	if (hbheDigi.depth() == 3 ) hbhe_cosmic_phi_vs_timing_depth3_hodtFired -> Fill ( hbheDigi.phi(), hbheDigi.time());

  if (hbheDigi.depth() == 1 ) hbhe_cosmic_phi_vs_recHitTiming_depth1_hodtFired -> Fill ( hbheDigi.phi(), hbheDigi.recHitTime());
  if (hbheDigi.depth() == 2 ) hbhe_cosmic_phi_vs_recHitTiming_depth2_hodtFired -> Fill ( hbheDigi.phi(), hbheDigi.recHitTime());
  if (hbheDigi.depth() == 3 ) hbhe_cosmic_phi_vs_recHitTiming_depth3_hodtFired -> Fill ( hbheDigi.phi(), hbheDigi.recHitTime());

  hbhe_cosmic_timing_recTiming_hodtFired -> Fill(hbheDigi.time(),hbheDigi.recHitTime());

  for (int i=0; i<hbheDigi.size(); i++){
    hbhe_cosmic_timestamp_fc_dtFired -> Fill(i,hbheDigi.fc(i));
    if (hbheDigi.time()<0.5){
      hbhe_cosmic_timestamp_fc_zeroTiming_hodtFired -> Fill(i,hbheDigi.fc(i));
    };
    if (hbheDigi.time()>9.0){
      hbhe_cosmic_timestamp_fc_nineTiming_hodtFired -> Fill(i,hbheDigi.fc(i));
    };
  };

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
	ho_cosmic_rhtiming_hoFired -> Fill ( hoDigi.recHitTime() );
	ho_cosmic_energy_hoFired   -> Fill ( hoDigi.energy() );
	ho_cosmic_timing_hoFired   -> Fill ( hoDigi.time()   );
	ho_cosmic_energy_vs_timing_hoFired -> Fill ( hoDigi.energy(), hoDigi.time() );
	ho_cosmic_occupancy_hoFired -> Fill ( hoDigi.ieta(), hoDigi.iphi());
	if (hoDigi.energy() < 0.2){
		ho_cosmic_occupancy_noEnergy_hoFired -> Fill ( hoDigi.ieta(), hoDigi.iphi());
    ho_cosmic_timing_recTiming_noEnergy_hoFired -> Fill(hoDigi.time(),hoDigi.recHitTime());
  }else{
    ho_cosmic_timing_recTiming_withEnergyCut_hoFired -> Fill(hoDigi.time(),hoDigi.recHitTime());
  };

  ho_cosmic_recHitTiming_hoFired->Fill(hoDigi.recHitTime());
  ho_cosmic_iphi_vs_recHitTiming_hoFired->Fill(hoDigi.iphi(),hoDigi.recHitTime());

	ho_cosmic_phi_vs_timing_hoFired -> Fill ( hoDigi.phi(), hoDigi.time());
	ho_cosmic_occuTiming_hoFired -> Fill ( hoDigi.ieta(), hoDigi.iphi(), hoDigi.time() );
	if ( hoDigi.recHitTime() < -94 ) ho_cosmic_occupancy_badRHTiming_hoFired -> Fill ( hoDigi.phi(), hoDigi.time());
	if ( hoDigi.phi() > 0 ) ho_top_cosmic_timing_hoFired -> Fill ( hoDigi.time() );
	else                    ho_bot_cosmic_timing_hoFired -> Fill ( hoDigi.time() );

  ho_cosmic_timing_recTiming_hoFired -> Fill(hoDigi.time(),hoDigi.recHitTime());

  for (int i=0; i<hoDigi.size(); i++){
    ho_cosmic_timestamp_fc_hoFired -> Fill(i,hoDigi.fc(i));
    if (hoDigi.time()<0.5){
      ho_cosmic_timestamp_fc_zeroTiming_hoFired -> Fill(i,hoDigi.fc(i));
    };
    if (hoDigi.time()>9.0){
      ho_cosmic_timestamp_fc_nineTiming_hoFired -> Fill(i,hoDigi.fc(i));
    };
  };

      }

      if ( dt_trigger_fired && !ho_trigger_fired ) {
	ho_cosmic_rhtiming_dtFired -> Fill ( hoDigi.recHitTime() );
	ho_cosmic_energy_dtFired   -> Fill ( hoDigi.energy() );
	ho_cosmic_timing_dtFired   -> Fill ( hoDigi.time()   );
	ho_cosmic_energy_vs_timing_dtFired -> Fill ( hoDigi.energy(), hoDigi.time() );
	ho_cosmic_occupancy_dtFired -> Fill ( hoDigi.ieta(), hoDigi.iphi());
	if (hoDigi.energy() < 0.2){
		ho_cosmic_occupancy_noEnergy_dtFired -> Fill ( hoDigi.ieta(), hoDigi.iphi());
    ho_cosmic_timing_recTiming_noEnergy_dtFired -> Fill(hoDigi.time(),hoDigi.recHitTime());
	}else{
    ho_cosmic_timing_recTiming_withEnergyCut_dtFired -> Fill(hoDigi.time(),hoDigi.recHitTime());

  };

  	ho_cosmic_recHitTiming_dtFired->Fill(hoDigi.recHitTime());
  	ho_cosmic_iphi_vs_recHitTiming_dtFired->Fill(hoDigi.iphi(),hoDigi.recHitTime());

	ho_cosmic_phi_vs_timing_dtFired -> Fill ( hoDigi.phi(), hoDigi.time());
	ho_cosmic_occuTiming_dtFired -> Fill ( hoDigi.ieta(), hoDigi.iphi(), hoDigi.time() );
	if ( hoDigi.recHitTime() < -94 ) ho_cosmic_occupancy_badRHTiming_dtFired -> Fill ( hoDigi.phi(), hoDigi.time());
	if ( hoDigi.phi() > 0 ) ho_top_cosmic_timing_dtFired -> Fill ( hoDigi.time() );
	else                    ho_bot_cosmic_timing_dtFired -> Fill ( hoDigi.time() );

  ho_cosmic_timing_recTiming_dtFired -> Fill(hoDigi.time(),hoDigi.recHitTime());

  for (int i=0; i<hoDigi.size(); i++){
    ho_cosmic_timestamp_fc_dtFired -> Fill(i,hoDigi.fc(i));
    if (hoDigi.time()<0.5){
      ho_cosmic_timestamp_fc_zeroTiming_dtFired -> Fill(i,hoDigi.fc(i));
    };
    if (hoDigi.time()>9.0){
      ho_cosmic_timestamp_fc_nineTiming_dtFired -> Fill(i,hoDigi.fc(i));
    };
  };

  };

      
      if ( dt_trigger_fired &&  ho_trigger_fired ) {
	ho_cosmic_rhtiming_hodtFired -> Fill ( hoDigi.recHitTime() );
	ho_cosmic_energy_hodtFired -> Fill ( hoDigi.energy() );
	ho_cosmic_timing_hodtFired -> Fill ( hoDigi.time()   );
	ho_cosmic_energy_vs_timing_hodtFired -> Fill ( hoDigi.energy(), hoDigi.time() );
	ho_cosmic_occupancy_hodtFired -> Fill ( hoDigi.ieta(), hoDigi.iphi());

	if (hoDigi.energy() < 0.2){
		ho_cosmic_occupancy_noEnergy_hodtFired -> Fill ( hoDigi.ieta(), hoDigi.iphi());
    ho_cosmic_timing_recTiming_noEnergy_hodtFired -> Fill(hoDigi.time(),hoDigi.recHitTime());
  }else{
    ho_cosmic_timing_recTiming_withEnergyCut_hodtFired -> Fill(hoDigi.time(),hoDigi.recHitTime());
  };

  ho_cosmic_recHitTiming_hodtFired->Fill(hoDigi.recHitTime());
  ho_cosmic_iphi_vs_recHitTiming_hodtFired->Fill(hoDigi.iphi(),hoDigi.recHitTime());

	ho_cosmic_phi_vs_timing_hodtFired -> Fill ( hoDigi.phi(), hoDigi.time());
	ho_cosmic_occuTiming_hodtFired -> Fill ( hoDigi.ieta(), hoDigi.iphi(), hoDigi.time() );
	if ( hoDigi.recHitTime() < -94 ) ho_cosmic_occupancy_badRHTiming_hodtFired -> Fill ( hoDigi.phi(), hoDigi.time());
	if ( hoDigi.phi() > 0 ) ho_top_cosmic_timing_hodtFired -> Fill ( hoDigi.time() );
	else                    ho_bot_cosmic_timing_hodtFired -> Fill ( hoDigi.time() );

    ho_cosmic_timing_recTiming_hodtFired -> Fill(hoDigi.time(),hoDigi.recHitTime());

  for (int i=0; i<hoDigi.size(); i++){
    ho_cosmic_timestamp_fc_hodtFired -> Fill(i,hoDigi.fc(i));
    if (hoDigi.time()<0.5){
      ho_cosmic_timestamp_fc_zeroTiming_hodtFired -> Fill(i,hoDigi.fc(i));
    };
    if (hoDigi.time()>9.0){
      ho_cosmic_timestamp_fc_nineTiming_hodtFired -> Fill(i,hoDigi.fc(i));
    };
  };

      }
      
    }
  }
}
