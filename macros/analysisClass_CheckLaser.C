#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"

//__________________________________________________________________________________________________________________________________
// Author: Lucien Lo
// Code to investigate the performance of laser filters in Run 2015D data
// 
// The logic is with reference to the laser filter in 2012: http://cmslxr.fnal.gov/source/EventFilter/HcalRawToDigi/plugins/HcalLaserHBHEHFFilter2012.cc
//__________________________________________________________________________________________________________________________________

bool isLaserRegion(int ieta,int iphi,int subDet){
  const int HcalBarrel = 1;
  if ((ieta < 0) && (subDet == HcalBarrel){
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
  const double recHitEnergyCut = 1.;
  const int nBad = 72*3; // 3 bad RBXes, 72 channels each
  const int nGood = 2592*2 - nBad;  // remaining HBHE channels are 'good'

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
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSubdet"    , kTRUE);

  //--------------------------------------------------------------------------------
  // Histograms
  //--------------------------------------------------------------------------------
  TH2F* noLaserOccup_vs_laserOccp = makeTH2F("noLaserOccup_vs_laserOccp",50,0.,1.,50,0.,1.);
  noLaserOccup_vs_laserOccp -> SetTitle(" ; Bad RBX Fraction ; Good RBX Fraction ");

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  int nHBHEDigis;

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 10000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    
    nHBHEDigis = hbheDigis -> GetSize();

    double laserRegion_occupancy = 0;
    double noLaserRegion_occupancy = 0;
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if (hbheDigi.energy() < recHitEnergyCut) continue;
      if ( isLaserRegion( hbheDigi.ieta() , hbheDigi.iphi() , hbheDigi.subdet() ) ) {
        laserRegion_occupancy++;
      } else {
        noLaserRegion_occupancy++;
      };
    };
    noLaserOccup_vs_laserOccp -> Fill( noLaserRegion_occupancy/((double)nBad ) ,  laserRegion_occupancy/((double)nGood) );
  };
}
