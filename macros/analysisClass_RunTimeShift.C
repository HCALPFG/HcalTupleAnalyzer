#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"

int getHash ( const int & ieta, 
	      const int & iphi, 
	      const int & depth ){
  int ietaIndex = ieta + 41;
  int iphiIndex = iphi;
  int depthIndex = depth;
  
  int hash = 0;
  hash += (ietaIndex * 1);
  hash += (iphiIndex * 100);
  hash += (depthIndex * 10000);
  return hash;
};

void reverseHash ( const int & hash,
		   int & ieta,
		   int & iphi,
		   int & depth ){
  int tmp_hash = hash;
  ieta = (hash % 100) - 41;
  iphi = (hash / 100) % 100;
  depth = (hash / 10000);
};

void analysisClass::loop(){
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();
  std::cout << "n events = " << n_events << std::endl;

  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*", kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("run", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDepth", kTRUE);

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------
  std::map<int,std::map<int,TH1F*>> RecHitTiming;
  int hash;
  char histName[100];
  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 1000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;
    
    //-----------------------------------------------------------------
    // Collections of HBHE
    //-----------------------------------------------------------------
    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));

    int runNumber = tuple_tree -> run;

    if (RecHitTiming.find(runNumber) == RecHitTiming.end()){
      RecHitTiming[runNumber] = std::map<int,TH1F*>();
    };

    int nHBHEDigis = hbheDigis -> GetSize();
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if ( hbheDigi.energy() < 5.0 ) continue;

      hash = getHash( hbheDigi.ieta() , hbheDigi.iphi() , hbheDigi.depth() );
      if ( RecHitTiming[runNumber].find(hash) == RecHitTiming[runNumber].end() ){
        sprintf(histName, "%d_HBHE_%d_%d_%d", runNumber , hbheDigi.ieta(), hbheDigi.iphi(), hbheDigi.depth());
        RecHitTiming[runNumber].insert(std::pair<int,TH1F*>(hash, makeTH1F(histName,100,-10.,10.)));
      };

      RecHitTiming[runNumber][hash] -> Fill(hbheDigi.recHitTime());

    };
  };

  TH1F * graph = makeTH1F("RecHitTiming_vs_RunNumber",RecHitTiming.size(),-0.5,RecHitTiming.size()-0.5);
  char binLabel[100];
  int iBin = 1;
  for (std::map<int,std::map<int,TH1F*>>::iterator it = RecHitTiming.begin(); it != RecHitTiming.end(); it++){
    double sum = 0;
    double error2 = 0;
    int count = 0;
    for (std::map<int,TH1F*>::iterator it2 = it -> second.begin(); it2 != it -> second.end(); it2++){
      count += it2 -> second -> Integral(0,101);
      sum += (it2 -> second -> Integral(0,101))*(it2 -> second -> GetMean());
      error2 += (it2 -> second -> GetRMS())*(it2 -> second -> GetRMS());
    };

    graph -> SetBinContent( iBin , sum/count  );
    graph -> SetBinError(iBin , sqrt(error2/count) );
    sprintf(binLabel,"%d",it -> first);
    graph -> GetXaxis() -> SetBinLabel( iBin , binLabel );
    iBin++;
  };
   

};
