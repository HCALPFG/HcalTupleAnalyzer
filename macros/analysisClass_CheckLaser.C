#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"

bool isLaserRegion(int ieta,int iphi){
  if (ieta > 0){
    if ((iphi >= 50) && (iphi <= 54)){
      return false;
    };
  } else {
    if ( ( (iphi >=15) && (iphi <= 18) ) || ( (iphi >= 27) && (iphi <=34) ) ){
      return false;
    };
  };
  return true;
};

void analysisClass::loop(){
 
  //--------------------------------------------------------------------------------
  // Configurables
  //--------------------------------------------------------------------------------
  const double recHitEnergyCut = 0.;

  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();
  std::cout << "n events = " << n_events << std::endl;
  
  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("run"             , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event"           , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls"              , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC"        , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDepth"     , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecTime"   , kTRUE);

  //--------------------------------------------------------------------------------
  // Histograms
  //--------------------------------------------------------------------------------
  TH2F* laserOccup_vs_noLaserOccp = makeTH2F("laserOccup_vs_noLaserOccp",100,0.,10000.,100,0.,10000.);

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  int nHBHEDigis;

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 10000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    
    nHBHEDigis = hbheDigis -> GetSize();

    int laserRegion_occupancy = 0;
    int noLaserRegion_occupancy = 0;
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if (hbheDigi.energy() < recHitEnergyCut) continue;
      if ( isLaserRegion( hbheDigi.ieta() , hbheDigi.iphi() ) ) {
        laserRegion_occupancy += hbheDigi.fcTotal();
      } else {
        noLaserRegion_occupancy += hbheDigi.fcTotal();
      };
    };
    laserOccup_vs_noLaserOccp -> Fill( laserRegion_occupancy ,  noLaserRegion_occupancy );
  };
}
