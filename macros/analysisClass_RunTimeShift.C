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
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize", kTRUE);

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------
  std::map<int,std::map<int,TH1F*>> RecHitTiming;
  std::map<int,std::map<int,TH1F*>> AvgTiming;

  // std::map<int,std::map<int,TH1F*>> HBRecHitTiming;
  // std::map<int,std::map<int,TH1F*>> HBAvgTiming;

  // std::map<int,std::map<int,TH1F*>> HERecHitTiming;
  // std::map<int,std::map<int,TH1F*>> HEAvgTiming;

  int hash;
  char histName[100];
  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 10000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    int runNumber = tuple_tree -> run;

    //-----------------------------------------------------------------
    // Collections of HBHE
    //-----------------------------------------------------------------
    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));

    if (RecHitTiming.find(runNumber) == RecHitTiming.end()){
      RecHitTiming[runNumber] = std::map<int,TH1F*>();
    };
    if (AvgTiming.find(runNumber) == AvgTiming.end()){
      AvgTiming[runNumber] = std::map<int,TH1F*>();
    };
    // if (HBRecHitTiming.find(runNumber) == HBRecHitTiming.end()){
    //   HBRecHitTiming[runNumber] = std::map<int,TH1F*>();
    // };
    // if (HBAvgTiming.find(runNumber) == HBAvgTiming.end()){
    //   HBAvgTiming[runNumber] = std::map<int,TH1F*>();
    // };
    // if (HERecHitTiming.find(runNumber) == HERecHitTiming.end()){
    //   HBRecHitTiming[runNumber] = std::map<int,TH1F*>();
    // };
    // if (HEAvgTiming.find(runNumber) == HEAvgTiming.end()){
    //   HEAvgTiming[runNumber] = std::map<int,TH1F*>();
    // };

    int nHBHEDigis = hbheDigis -> GetSize();
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if ( hbheDigi.energy() < 5.0 ) continue;

      hash = getHash( hbheDigi.ieta() , hbheDigi.iphi() , hbheDigi.depth() );
      
      if ( RecHitTiming[runNumber].find(hash) == RecHitTiming[runNumber].end() ){
        sprintf(histName, "%d_RecHitTiming_HBHE_%d_%d_%d", runNumber , hbheDigi.ieta(), hbheDigi.iphi(), hbheDigi.depth());
        RecHitTiming[runNumber].insert(std::pair<int,TH1F*>(hash, makeTH1F(histName,100,-10.,10.)));
      };

      if ( AvgTiming[runNumber].find(hash) == AvgTiming[runNumber].end() ){
        sprintf(histName, "%d_AvgTiming_HBHE_%d_%d_%d", runNumber , hbheDigi.ieta(), hbheDigi.iphi(), hbheDigi.depth());
        AvgTiming[runNumber].insert(std::pair<int,TH1F*>(hash, makeTH1F(histName,100,0.,10.)));
      };

      RecHitTiming[runNumber][hash] -> Fill(hbheDigi.recHitTime());
      AvgTiming[runNumber][hash] -> Fill(hbheDigi.time());

      // if (hbheDigi.ieta() <= 16){
      //   if ( HBRecHitTiming[runNumber].find(hash) == HBRecHitTiming[runNumber].end() ){
      //     sprintf(histName, "%d_RecHitTiming_HB_%d_%d_%d", runNumber , hbheDigi.ieta(), hbheDigi.iphi(), hbheDigi.depth());
      //     HBRecHitTiming[runNumber].insert(std::pair<int,TH1F*>(hash, makeTH1F(histName,100,-10.,10.)));
      //   };

      //   if ( HBAvgTiming[runNumber].find(hash) == HBAvgTiming[runNumber].end() ){
      //     sprintf(histName, "%d_HBAvgTiming_HBHE_%d_%d_%d", runNumber , hbheDigi.ieta(), hbheDigi.iphi(), hbheDigi.depth());
      //     HBAvgTiming[runNumber].insert(std::pair<int,TH1F*>(hash, makeTH1F(histName,100,0.,10.)));
      //   };

      //   HBRecHitTiming[runNumber][hash] -> Fill(hbheDigi.recHitTime());
      //   HBAvgTiming[runNumber][hash] -> Fill(hbheDigi.time());
      // };

      // if ((hbheDigi.ieta() > 16) and (hbheDigi.ieta() <= 29)){
      //   if ( HERecHitTiming[runNumber].find(hash) == HERecHitTiming[runNumber].end() ){
      //     sprintf(histName, "%d_RecHitTiming_HE_%d_%d_%d", runNumber , hbheDigi.ieta(), hbheDigi.iphi(), hbheDigi.depth());
      //     HERecHitTiming[runNumber].insert(std::pair<int,TH1F*>(hash, makeTH1F(histName,100,-10.,10.)));
      //   };

      //   if ( HEAvgTiming[runNumber].find(hash) == HEAvgTiming[runNumber].end() ){
      //     sprintf(histName, "%d_AvgTiming_HE_%d_%d_%d", runNumber , hbheDigi.ieta(), hbheDigi.iphi(), hbheDigi.depth());
      //     HEAvgTiming[runNumber].insert(std::pair<int,TH1F*>(hash, makeTH1F(histName,100,0.,10.)));
      //   };

      //   HERecHitTiming[runNumber][hash] -> Fill(hbheDigi.recHitTime());
      //   HEAvgTiming[runNumber][hash] -> Fill(hbheDigi.time());
      // };

    };
  };
  
  // TH1F * graph = makeTH1F("HBRecHitTiming_vs_RunNumber",HBRecHitTiming.size(),-0.5,HBRecHitTiming.size()-0.5);
  // char binLabel[100];
  // int iBin = 1;
  // for (std::map<int,std::map<int,TH1F*>>::iterator it = HBRecHitTiming.begin(); it != HBRecHitTiming.end(); it++){
  //   double sum = 0;
  //   double error2 = 0;
  //   int count = 0;
  //   int channelCount = 0;
  //   for (std::map<int,TH1F*>::iterator it2 = it -> second.begin(); it2 != it -> second.end(); it2++){
  //     channelCount++;
  //     count += it2 -> second -> Integral(0,101);
  //     sum += (it2 -> second -> Integral(0,101))*(it2 -> second -> GetMean());
  //     error2 += (it2 -> second -> GetRMS())*(it2 -> second -> GetRMS())*( it2 -> second -> Integral(0,101));
  //   };

  //   graph -> SetBinContent( iBin , sum/count  );
  //   graph -> SetBinError(iBin , sqrt(error2/count/channelCount) );
  //   sprintf(binLabel,"%d",it -> first);
  //   graph -> GetXaxis() -> SetBinLabel( iBin , binLabel );
  //   iBin++;
  // };
  // 
  // TH1F * graph2 = makeTH1F("HBAvgTiming_vs_RunNumber",HBAvgTiming.size(),-0.5,HBAvgTiming.size()-0.5);
  // iBin = 1;
  // for (std::map<int,std::map<int,TH1F*>>::iterator it = HBAvgTiming.begin(); it != HBAvgTiming.end(); it++){
  //   double sum = 0;
  //   double error2 = 0;
  //   int count = 0;
  //   int channelCount = 0;
  //   for (std::map<int,TH1F*>::iterator it2 = it -> second.begin(); it2 != it -> second.end(); it2++){
  //     channelCount++;
  //     count += it2 -> second -> Integral(0,101);
  //     sum += (it2 -> second -> Integral(0,101))*(it2 -> second -> GetMean());
  //     error2 += (it2 -> second -> GetRMS())*(it2 -> second -> GetRMS())*( it2 -> second -> Integral(0,101));
  //   };

  //   graph2 -> SetBinContent( iBin , sum/count  );
  //   graph2 -> SetBinError(iBin , sqrt(error2/count/channelCount) );
  //   sprintf(binLabel,"%d",it -> first);
  //   graph2 -> GetXaxis() -> SetBinLabel( iBin , binLabel );
  //   iBin++;
  // };

  // TH1F * graph3 = makeTH1F("HERecHitTiming_vs_RunNumber",HERecHitTiming.size(),-0.5,HERecHitTiming.size()-0.5);
  // iBin = 1;
  // for (std::map<int,std::map<int,TH1F*>>::iterator it = HERecHitTiming.begin(); it != HERecHitTiming.end(); it++){
  //   double sum = 0;
  //   double error2 = 0;
  //   int count = 0;
  //   int channelCount = 0;
  //   for (std::map<int,TH1F*>::iterator it2 = it -> second.begin(); it2 != it -> second.end(); it2++){
  //     channelCount++;
  //     count += it2 -> second -> Integral(0,101);
  //     sum += (it2 -> second -> Integral(0,101))*(it2 -> second -> GetMean());
  //     error2 += (it2 -> second -> GetRMS())*(it2 -> second -> GetRMS())*( it2 -> second -> Integral(0,101));
  //   };

  //   graph3 -> SetBinContent( iBin , sum/count  );
  //   graph3 -> SetBinError(iBin , sqrt(error2/count/channelCount) );
  //   sprintf(binLabel,"%d",it -> first);
  //   graph3 -> GetXaxis() -> SetBinLabel( iBin , binLabel );
  //   iBin++;
  // };
  // 
  // TH1F * graph4 = makeTH1F("HEAvgTiming_vs_RunNumber",HEAvgTiming.size(),-0.5,HEAvgTiming.size()-0.5);
  // iBin = 1;
  // for (std::map<int,std::map<int,TH1F*>>::iterator it = HEAvgTiming.begin(); it != HEAvgTiming.end(); it++){
  //   double sum = 0;
  //   double error2 = 0;
  //   int count = 0;
  //   int channelCount = 0;
  //   for (std::map<int,TH1F*>::iterator it2 = it -> second.begin(); it2 != it -> second.end(); it2++){
  //     channelCount++;
  //     count += it2 -> second -> Integral(0,101);
  //     sum += (it2 -> second -> Integral(0,101))*(it2 -> second -> GetMean());
  //     error2 += (it2 -> second -> GetRMS())*(it2 -> second -> GetRMS())*( it2 -> second -> Integral(0,101));
  //   };

  //   graph4 -> SetBinContent( iBin , sum/count  );
  //   graph4 -> SetBinError(iBin , sqrt(error2/count/channelCount) );
  //   sprintf(binLabel,"%d",it -> first);
  //   graph4 -> GetXaxis() -> SetBinLabel( iBin , binLabel );
  //   iBin++;
  // };

  TH1F * graph = makeTH1F("RecHitTiming_vs_RunNumber",RecHitTiming.size(),-0.5,RecHitTiming.size()-0.5);
  char binLabel[100];
  int iBin = 1;
  for (std::map<int,std::map<int,TH1F*>>::iterator it = RecHitTiming.begin(); it != RecHitTiming.end(); it++){
    double sum = 0;
    double error2 = 0;
    int count = 0;
    int channelCount = 0;
    for (std::map<int,TH1F*>::iterator it2 = it -> second.begin(); it2 != it -> second.end(); it2++){
      channelCount++;
      count += it2 -> second -> Integral(0,101);
      sum += (it2 -> second -> Integral(0,101))*(it2 -> second -> GetMean());
      error2 += (it2 -> second -> GetRMS())*(it2 -> second -> GetRMS())*( it2 -> second -> Integral(0,101));
    };

    graph -> SetBinContent( iBin , sum/count  );
    graph -> SetBinError(iBin , sqrt(error2/count/channelCount) );
    sprintf(binLabel,"%d",it -> first);
    graph -> GetXaxis() -> SetBinLabel( iBin , binLabel );
    iBin++;
  };
  
  TH1F * graph2 = makeTH1F("AvgTiming_vs_RunNumber",AvgTiming.size(),-0.5,AvgTiming.size()-0.5);
  iBin = 1;
  for (std::map<int,std::map<int,TH1F*>>::iterator it = AvgTiming.begin(); it != AvgTiming.end(); it++){
    double sum = 0;
    double error2 = 0;
    int count = 0;
    int channelCount = 0;
    for (std::map<int,TH1F*>::iterator it2 = it -> second.begin(); it2 != it -> second.end(); it2++){
      channelCount++;
      count += it2 -> second -> Integral(0,101);
      sum += (it2 -> second -> Integral(0,101))*(it2 -> second -> GetMean());
      error2 += (it2 -> second -> GetRMS())*(it2 -> second -> GetRMS())*( it2 -> second -> Integral(0,101));
    };

    graph2 -> SetBinContent( iBin , sum/count  );
    graph2 -> SetBinError(iBin , sqrt(error2/count/channelCount) );
    sprintf(binLabel,"%d",it -> first);
    graph2 -> GetXaxis() -> SetBinLabel( iBin , binLabel );
    iBin++;
  };

};
