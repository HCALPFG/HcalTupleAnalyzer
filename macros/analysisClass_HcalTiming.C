#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HFDigi.h"
#include "HBHEDigi.h"
#include <map>


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
  
  tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("run"             , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event"           , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls"              , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFC"                  , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDepth"               , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIEta"                , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIPhi"                , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecEnergy"           , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecTime"             , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC"                , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta"              , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi"              , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDepth"             , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy"         , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("FEDBCN"        , kTRUE);
 
  //--------------------------------------------------------------------------------
  // Prepare the histograms and variables
  //--------------------------------------------------------------------------------

  int N_TS4_cut[4]={0,0,0,0} ;
  int N_HF_TS=0 ;
  int nHBHEDigis = 0, nHFDigis =0 ; 		//# of pulses in each event
  int IEta=0,  IPhi=0;

  // Array of vectors to hold the data. array index = position, vector index = data entries
  float HF_TSRatioMap_D1_sum[86][74],HF_TSRatioMap_E1_D1_sum[86][74],HF_TSRatioMap_E2_D1_sum[86][74],HF_TSRatioMap_E3_D1_sum[86][74];	
  float HF_TSRatioMap_D2_sum[86][74],HF_TSRatioMap_E1_D2_sum[86][74],HF_TSRatioMap_E2_D2_sum[86][74],HF_TSRatioMap_E3_D2_sum[86][74];	

  float HF_TSRatioMap_D1_nEvt[86][74],HF_TSRatioMap_E1_D1_nEvt[86][74],HF_TSRatioMap_E2_D1_nEvt[86][74],HF_TSRatioMap_E3_D1_nEvt[86][74];	
  float HF_TSRatioMap_D2_nEvt[86][74],HF_TSRatioMap_E1_D2_nEvt[86][74],HF_TSRatioMap_E2_D2_nEvt[86][74],HF_TSRatioMap_E3_D2_nEvt[86][74];

  float HF_TSRatioMap_D1_sum2[86][74];
  float HF_TSRatioMap_D2_sum2[86][74];	

  for(int i=0;i<86;i++){
	for(int j=0;j<74;j++){
  		HF_TSRatioMap_D1_sum[i][j]=0; HF_TSRatioMap_E1_D1_sum[i][j]=0; HF_TSRatioMap_E2_D1_sum[i][j]=0;HF_TSRatioMap_E3_D1_sum[i][j]=0;	
  		HF_TSRatioMap_D2_sum[i][j]=0; HF_TSRatioMap_E1_D2_sum[i][j]=0; HF_TSRatioMap_E2_D2_sum[i][j]=0;HF_TSRatioMap_E3_D2_sum[i][j]=0;	
  		HF_TSRatioMap_D1_nEvt[i][j]=0; HF_TSRatioMap_E1_D1_nEvt[i][j]=0; HF_TSRatioMap_E2_D1_nEvt[i][j]=0;HF_TSRatioMap_E3_D1_nEvt[i][j]=0;	
  		HF_TSRatioMap_D2_nEvt[i][j]=0; HF_TSRatioMap_E1_D2_nEvt[i][j]=0; HF_TSRatioMap_E2_D2_nEvt[i][j]=0;HF_TSRatioMap_E3_D2_nEvt[i][j]=0;
		HF_TSRatioMap_D1_sum2[i][j]=0;	
		HF_TSRatioMap_D2_sum2[i][j]=0;	
	}
  }

  TH1F *HF_Time_D1  	 = makeTH1F("HF_Time_D1"         ,"HF: E>5GeV, Depth 1", 50, -50, 50);
  TH1F *HF_Time_D2  	 = makeTH1F("HF_Time_D2"         ,"HF: E>5GeV  Depth 2", 50, -50, 50);
  TH1F *HF_Time_TSWeight = makeTH1F("HF_Time_TSWeight"   ,"HF: E>5GeV  time weighted by TS1/TS2", 50, -50, 50);

  TH2F *HF_Time_Ratio_D1 = new TH2F("HF_Time_Ratio_D1"   ,"HF: E>5GeV Depth 1", 50, -50, 50, 10, 0, 0);
  TH2F *HF_Time_Ratio_D2 = new TH2F("HF_Time_Ratio_D2"   ,"HF: E>5GeV Depth 2", 50, -50, 50, 10, 0, 0);
  TH2F *HF_TimeMap_TS0_D1      = new TH2F("HF_TimeMap_TS0_D1"  ,"HF: E>5GeV, TS0>40fC, Depth 1", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TimeMap_TS0_D2      = new TH2F("HF_TimeMap_TS0_D2"  ,"HF: E>5GeV, TS0>40fC  Depth 2", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TimeMap_TS2_D1      = new TH2F("HF_TimeMap_TS2_D1"  ,"HF: E>5GeV, TS2>60fC  Depth 1", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TimeMap_TS2_D2      = new TH2F("HF_TimeMap_TS2_D2"  ,"HF: E>5GeV, TS2>60fC  Depth 2", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TimeMap_TS0TS2_D1   = new TH2F("HF_TimeMap_TS0TS2_D1"  ,"HF: E>5GeV, TS2>60fC && TS0>40fC  Depth 1", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TimeMap_TS0TS2_D2   = new TH2F("HF_TimeMap_TS0TS2_D2"  ,"HF: E>5GeV, TS2>60fC && TS0>40fC  Depth 2", 86, -43, 43, 74, 0, 74);
  TH1F *HF_Time_fC  	 = makeTH1F("HF_Time_fC"      ,"HF: E>5GeV, -9ns<t<-7ns, |TS1/TS2|<0.2", 4, 0, 4);
 
  // Maps of HF uniformity in TS1/TS2, binned by energy
  TH1F *HF_TSRatio_D1		      = makeTH1F("HF_TSRatio_D1","HF: E>5GeV Depth 1", 40, 0,0);
  TH1F *HF_TSRatio_E1_D1	      = makeTH1F("HF_TSRatio_E1_D1","HF: 5GeV<E<10GeV Depth 1", 40, 0,0);
  TH1F *HF_TSRatio_E2_D1	      = makeTH1F("HF_TSRatio_E2_D1","HF: 10GeV<E<20GeV Depth 1", 40, 0,0);
  TH1F *HF_TSRatio_E3_D1	      = makeTH1F("HF_TSRatio_E3_D1","HF: E>20GeV Depth 1", 40, 0,0);

  TH1F *HF_TSRatio_D2		      = makeTH1F("HF_TSRatio_D2","HF: E>5GeV Depth 2", 40, 0,0);
  TH1F *HF_TSRatio_E1_D2	      = makeTH1F("HF_TSRatio_E1_D2","HF: 5GeV<E<10GeV Depth 2", 40, 0,0);
  TH1F *HF_TSRatio_E2_D2	      = makeTH1F("HF_TSRatio_E2_D2","HF: 10GeV<E<20GeV Depth 2", 40, 0,0);
  TH1F *HF_TSRatio_E3_D2	      = makeTH1F("HF_TSRatio_E3_D2","HF: E>20GeV Depth 2", 40, 0,0);

  TH2F *HF_TSRatioMap_Double_D1         = new TH2F("HF_TSRatioMap_Double_D1"  ,"HF: E>5GeV Depth 1, n entries with >1 pulse/event", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Double_D2         = new TH2F("HF_TSRatioMap_Double_D2"  ,"HF: E>5GeV Depth 2, n entries with >1 pulse/event", 86, -43, 43, 74, 0, 74);

  TH2F *HF_TSRatioMap_nEvt_D1         = new TH2F("HF_TSRatioMap_nEvt_D1"  ,"HF: E>5GeV Depth 1, nEntries", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Avg_D1          = new TH2F("HF_TSRatioMap_Avg_D1"  ,"HF: E>5GeV Depth 1, Avg TS1/TS2", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Rms_D1          = new TH2F("HF_TSRatioMap_Rms_D1"  ,"HF: E>5GeV Depth 1, Rms TS1/TS2", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Avg_E1_D1       = new TH2F("HF_TSRatioMap_Avg_E1_D1"   ,"HF: 5GeV<E<10GeV , Avg TS1/TS2 Depth 1", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Avg_E2_D1       = new TH2F("HF_TSRatioMap_Avg_E2_D1"   ,"HF: 10GeV<E<20GeV, Avg TS1/TS2 Depth 1", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Avg_E3_D1       = new TH2F("HF_TSRatioMap_Avg_E3_D1"   ,"HF: E>20GeV, Avg TS1/TS2 Depth 1", 86, -43, 43, 74, 0, 74);

  TH2F *HF_TSRatioMap_nEvt_D2         = new TH2F("HF_TSRatioMap_nEvt_D2"    ,"HF: E>5GeV Depth 2, nEntries", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Avg_D2         = new TH2F("HF_TSRatioMap_Avg_D2"      ,"HF: E>5GeV Depth 2, Avg TS1/TS2", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Rms_D2         = new TH2F("HF_TSRatioMap_Rms_D2"      ,"HF: E>5GeV Depth 2, Rms TS1/TS2", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Avg_E1_D2      = new TH2F("HF_TSRatioMap_Avg_E1_D2"   ,"HF: 5GeV<E<10GeV, Avg TS1/TS2 Depth 2", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Avg_E2_D2      = new TH2F("HF_TSRatioMap_Avg_E2_D2"   ,"HF: 10GeV<E<20GeV, Avg TS1/TS2 Depth 2", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TSRatioMap_Avg_E3_D2      = new TH2F("HF_TSRatioMap_Avg_E3_D2"   ,"HF: E>20GeV, Avg TS1/TS2 Depth 2", 86, -43, 43, 74, 0, 74);

  TH1F *HF_Energy_Tplus  = makeTH1F("HF_Energy_Tplus" ,"HF E>5GeV w/ t>0", 75, 0, 75);
  TH1F *HF_Energy_Tminus = makeTH1F("HF_Energy_Tminus","HF E>5GeV w/ t<0", 75, 0, 75);

  TH2F *RatiosMap1 = new TH2F("AvgRatiosMap1","Avg TS5/TS4 ratios 30<TS4<100" , 60, -30, 30, 74, 0, 74);
  TH2F *RatiosMap2 = new TH2F("AvgRatiosMap2","Avg TS5/TS4 ratios 100<TS4<200", 60, -30, 30, 74, 0, 74);
  TH2F *RatiosMap3 = new TH2F("AvgRatiosMap3","Avg TS5/TS4 ratios 200<TS4<600", 60, -30, 30, 74, 0, 74);
  TH2F *RatiosMap4 = new TH2F("AvgRatiosMap4","Avg TS5/TS4 ratios 600<TS4<2000", 60, -30, 30, 74, 0, 74);

// Maps of HBHE uniformity in TS5/TS4, binned by energy
  float HBHE_TSRatioMap_D1_sum[60][74],HBHE_TSRatioMap_fC1_D1_sum[60][74],HBHE_TSRatioMap_fC2_D1_sum[60][74],HBHE_TSRatioMap_fC3_D1_sum[60][74],HBHE_TSRatioMap_fC4_D1_sum[60][74];	
  float HBHE_TSRatioMap_D2_sum[60][74],HBHE_TSRatioMap_fC1_D2_sum[60][74],HBHE_TSRatioMap_fC2_D2_sum[60][74],HBHE_TSRatioMap_fC3_D2_sum[60][74],HBHE_TSRatioMap_fC4_D2_sum[60][74];	
  float HBHE_TSRatioMap_D3_sum[60][74],HBHE_TSRatioMap_fC1_D3_sum[60][74],HBHE_TSRatioMap_fC2_D3_sum[60][74],HBHE_TSRatioMap_fC3_D3_sum[60][74],HBHE_TSRatioMap_fC4_D3_sum[60][74];	

 float HBHE_TSRatioMap_D1_nEvt[60][74],HBHE_TSRatioMap_fC1_D1_nEvt[60][74],HBHE_TSRatioMap_fC2_D1_nEvt[60][74],HBHE_TSRatioMap_fC3_D1_nEvt[60][74],HBHE_TSRatioMap_fC4_D1_nEvt[60][74];	
 float HBHE_TSRatioMap_D2_nEvt[60][74],HBHE_TSRatioMap_fC1_D2_nEvt[60][74],HBHE_TSRatioMap_fC2_D2_nEvt[60][74],HBHE_TSRatioMap_fC3_D2_nEvt[60][74],HBHE_TSRatioMap_fC4_D2_nEvt[60][74];	
 float HBHE_TSRatioMap_D3_nEvt[60][74],HBHE_TSRatioMap_fC1_D3_nEvt[60][74],HBHE_TSRatioMap_fC2_D3_nEvt[60][74],HBHE_TSRatioMap_fC3_D3_nEvt[60][74],HBHE_TSRatioMap_fC4_D3_nEvt[60][74];	

  float HBHE_TSRatioMap_D1_sum2[60][74];	
  float HBHE_TSRatioMap_D2_sum2[60][74];	
  float HBHE_TSRatioMap_D3_sum2[60][74];

  for(int i=0;i<60;i++){
	for(int j=0;j<74;j++){
  	HBHE_TSRatioMap_D1_sum[i][j]=0;HBHE_TSRatioMap_fC1_D1_sum[i][j]=0;HBHE_TSRatioMap_fC2_D1_sum[i][j]=0;HBHE_TSRatioMap_fC3_D1_sum[i][j]=0;HBHE_TSRatioMap_fC4_D1_sum[i][j]=0;	
  	HBHE_TSRatioMap_D2_sum[i][j]=0;HBHE_TSRatioMap_fC1_D2_sum[i][j]=0;HBHE_TSRatioMap_fC2_D2_sum[i][j]=0;HBHE_TSRatioMap_fC3_D2_sum[i][j]=0;HBHE_TSRatioMap_fC4_D2_sum[i][j]=0;	
  	HBHE_TSRatioMap_D3_sum[i][j]=0;HBHE_TSRatioMap_fC1_D3_sum[i][j]=0;HBHE_TSRatioMap_fC2_D3_sum[i][j]=0;HBHE_TSRatioMap_fC3_D3_sum[i][j]=0;HBHE_TSRatioMap_fC4_D3_sum[i][j]=0;	

   HBHE_TSRatioMap_D1_nEvt[i][j]=0;HBHE_TSRatioMap_fC1_D1_nEvt[i][j]=0;HBHE_TSRatioMap_fC2_D1_nEvt[i][j]=0;HBHE_TSRatioMap_fC3_D1_nEvt[i][j]=0;HBHE_TSRatioMap_fC4_D1_nEvt[i][j]=0;	
   HBHE_TSRatioMap_D2_nEvt[i][j]=0;HBHE_TSRatioMap_fC1_D2_nEvt[i][j]=0;HBHE_TSRatioMap_fC2_D2_nEvt[i][j]=0;HBHE_TSRatioMap_fC3_D2_nEvt[i][j]=0;HBHE_TSRatioMap_fC4_D2_nEvt[i][j]=0;
   HBHE_TSRatioMap_D3_nEvt[i][j]=0;HBHE_TSRatioMap_fC1_D3_nEvt[i][j]=0;HBHE_TSRatioMap_fC2_D3_nEvt[i][j]=0;HBHE_TSRatioMap_fC3_D3_nEvt[i][j]=0;HBHE_TSRatioMap_fC4_D3_nEvt[i][j]=0;
	
	HBHE_TSRatioMap_D1_sum2[i][j]=0;
	HBHE_TSRatioMap_D2_sum2[i][j]=0;
	HBHE_TSRatioMap_D3_sum2[i][j]=0;
	}
  }	

  TH1F *HBHE_TSdist_22_5	      = makeTH1F("HBHE_TSdist_22_5" ,"HBHE: TS[n]>30fC,ieta=-22 iphi=5", 10, 0, 10);
  TH1F *HBHE_TSdist_30		      = makeTH1F("HBHE_TSdist_30" ,"HBHE: TS[n]>30fC", 10, 0, 10);
  TH1F *HBHE_TSdist_50		      = makeTH1F("HBHE_TSdist_50" ,"HBHE: TS[n]>50fC", 10, 0, 10);
  TH1F *HBHE_TSdist_100		      = makeTH1F("HBHE_TSdist_100" ,"HBHE: TS[n]>100fC", 10, 0, 10);
  TH1F *HBHE_nTS_fired_30	      = makeTH1F("HBHE_nTS_fired_30" ,"HBHE: # of TS with >30fC", 10, 0, 10);
  TH1F *HBHE_nTS_fired_50	      = makeTH1F("HBHE_nTS_fired_50" ,"HBHE: # of TS with >50fC", 10, 0, 10);
  TH1F *HBHE_nTS_fired_100	      = makeTH1F("HBHE_nTS_fired_100" ,"HBHE: # of TS with >100fC", 10, 0, 10);
  TH1F *HBHE_Energy_D1		      = makeTH1F("HBHE_Energy_D1" ,"HBHE: E>5GeV Depth 1", 50, 0, 0);
  TH1F *HBHE_TSRatio_D1		      = makeTH1F("HBHE_TSRatio_D1","HBHE: TS4>30fC  Depth 1", 30, 0,0);
  TH1F *HBHE_TSRatio_D2		      = makeTH1F("HBHE_TSRatio_D2","HBHE: TS4>30fC  Depth 2", 30, 0,0);
  TH1F *HBHE_TSRatio_D3		      = makeTH1F("HBHE_TSRatio_D3","HBHE: TS4>30fC  Depth 3", 30, 0,0);
  TH1F *HBHE_TSRatio_a		      = makeTH1F("HBHE_TSRatio_a ","HBHEa: TS4>30fC", 30, 0,0);
  TH1F *HBHE_TSRatio_b		      = makeTH1F("HBHE_TSRatio_b ","HBHEb: TS4>30fC", 30, 0,0);
  TH1F *HBHE_TSRatio_c		      = makeTH1F("HBHE_TSRatio_c ","HBHEc: TS4>30fC", 30, 0,0);

  TH1F *HBHE_TSRatio_fC1_D1	      = makeTH1F("HBHE_TSRatio_fC1_D1","HBHE: 30fC<TS4<100fC    Depth 1", 30, 0,0);
  TH1F *HBHE_TSRatio_fC2_D1	      = makeTH1F("HBHE_TSRatio_fC2_D1","HBHE: 100fC<TS4<200fC   Depth 1", 30, 0,0);
  TH1F *HBHE_TSRatio_fC3_D1	      = makeTH1F("HBHE_TSRatio_fC3_D1","HBHE: 200fC<TS4<600fC   Depth 1", 30, 0,0);
  TH1F *HBHE_TSRatio_fC4_D1	      = makeTH1F("HBHE_TSRatio_fC4_D1","HBHE: 600fC<TS4<2000fC  Depth 1", 30, 0,0);

  TH1F *HBHE_TSRatio_fC1_D2	      = makeTH1F("HBHE_TSRatio_fC1_D2","HBHE: 30fC<TS4<100fC    Depth 2", 30, 0,0);
  TH1F *HBHE_TSRatio_fC2_D2	      = makeTH1F("HBHE_TSRatio_fC2_D2","HBHE: 100fC<TS4<200fC   Depth 2", 30, 0,0);
  TH1F *HBHE_TSRatio_fC3_D2	      = makeTH1F("HBHE_TSRatio_fC3_D2","HBHE: 200fC<TS4<600fC   Depth 2", 30, 0,0);
  TH1F *HBHE_TSRatio_fC4_D2	      = makeTH1F("HBHE_TSRatio_fC4_D2","HBHE: 600fC<TS4<2000fC  Depth 2", 30, 0,0);

  TH1F *HBHE_TSRatio_fC1_D3	      = makeTH1F("HBHE_TSRatio_fC1_D3","HBHE: 30fC<TS4<100fC    Depth 3", 30, 0,0);
  TH1F *HBHE_TSRatio_fC2_D3	      = makeTH1F("HBHE_TSRatio_fC2_D3","HBHE: 100fC<TS4<200fC   Depth 3", 30, 0,0);
  TH1F *HBHE_TSRatio_fC3_D3	      = makeTH1F("HBHE_TSRatio_fC3_D3","HBHE: 200fC<TS4<600fC   Depth 3", 30, 0,0);
  TH1F *HBHE_TSRatio_fC4_D3	      = makeTH1F("HBHE_TSRatio_fC4_D3","HBHE: 600fC<TS4<2000fC  Depth 3", 30, 0,0);

  TH2F *HBHE_TSRatioMap_Avg_D1           = makeTH2F("HBHE_TSRatioMap_Avg_D1"       ,"HBHE: TS4>30fC Depth 1, Avg TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Rms_D1           = makeTH2F("HBHE_TSRatioMap_Rms_D1"       ,"HBHE: TS4>30fC Depth 1, Rms TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_nEvt_D1          = makeTH2F("HBHE_TSRatioMap_nEvt_D1"      ,"HBHE: TS4>30fC Depth 1 nEvt ", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Pull_D1          = makeTH2F("HBHE_TSRatioMap_Pull_D1"      ,"HBHE: TS4>30fC Depth 1, Pull of ratio=|r-r#{_avg}}|/ (rms/sqrt{N})", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC1_D1       = makeTH2F("HBHE_TSRatioMap_Avg_fC1_D1"   ,"HBHE: 30fC<TS4<100fC   , Avg TS5/TS4 Depth 1", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC2_D1       = makeTH2F("HBHE_TSRatioMap_Avg_fC2_D1"   ,"HBHE: 100fC<TS4<200fC  , Avg TS5/TS4 Depth 1", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC3_D1       = makeTH2F("HBHE_TSRatioMap_Avg_fC3_D1"   ,"HBHE: 200fC<TS4<600fC  , Avg TS5/TS4 Depth 1", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC4_D1       = makeTH2F("HBHE_TSRatioMap_Avg_fC4_D1"   ,"HBHE: 600fC<TS4<2000fC , Avg TS5/TS4 Depth 1", 60, -30, 30, 74, 0, 74);

  TH2F *HBHE_TSRatioMap_Avg_D2         = makeTH2F("HBHE_TSRatioMap_Avg_D2"       ,"HBHE: TS4>30fC Depth 2, Avg TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Rms_D2         = makeTH2F("HBHE_TSRatioMap_Rms_D2"       ,"HBHE: TS4>30fC Depth 2, Rms TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_nEvt_D2         = makeTH2F("HBHE_TSRatioMap_nEvt_D2"   ,"HBHE: TS4>30fC Depth 2 nEvt ", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Pull_D2         = makeTH2F("HBHE_TSRatioMap_Pull_D2"   ,"HBHE: TS4>30fC Depth 2, Pull of ratio=|r-r#{_avg}}|/ (rms/sqrt{N})", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC1_D2      = makeTH2F("HBHE_TSRatioMap_Avg_fC1_D2"  ,"HBHE: 30fC<TS4<100fC    , Avg TS5/TS4 Depth 2", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC2_D2      = makeTH2F("HBHE_TSRatioMap_Avg_fC2_D2"  ,"HBHE: 100fC<TS4<200fC   , Avg TS5/TS4 Depth 2", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC3_D2      = makeTH2F("HBHE_TSRatioMap_Avg_fC3_D2"  ,"HBHE: 200fC<TS4<600fC   , Avg TS5/TS4 Depth 2", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC4_D2      = makeTH2F("HBHE_TSRatioMap_Avg_fC4_D2"  ,"HBHE: 600fC<TS4<2000fC  , Avg TS5/TS4 Depth 2", 60, -30, 30, 74, 0, 74);

  TH2F *HBHE_TSRatioMap_Avg_D3         = makeTH2F("HBHE_TSRatioMap_Avg_D3"     ,"HBHE: TS4>30fC Depth 3, Avg TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Rms_D3         = makeTH2F("HBHE_TSRatioMap_Rms_D3"     ,"HBHE: TS4>30fC Depth 3, Rms TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_nEvt_D3           = makeTH2F("HBHE_TSRatioMap_nEvt_D3"   ,"HBHE: TS4>30fC Depth 3 nEvt ", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Pull_D3         = makeTH2F("HBHE_TSRatioMap_Pull_D3"   ,"HBHE: TS4>30fC Depth 3, Pull of ratio=|r-r#{_avg}}|/ (rms/sqrt{N})", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC1_D3      = makeTH2F("HBHE_TSRatioMap_Avg_fC1_D3"  ,"HBHE:  30fC<TS4<100fC   , Avg TS5/TS4 Depth 3", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC2_D3      = makeTH2F("HBHE_TSRatioMap_Avg_fC2_D3"  ,"HBHE:  100fC<TS4<200fC  , Avg TS5/TS4 Depth 3", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC3_D3      = makeTH2F("HBHE_TSRatioMap_Avg_fC3_D3"  ,"HBHE:  200fC<TS4<600fC  , Avg TS5/TS4 Depth 3", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC4_D3      = makeTH2F("HBHE_TSRatioMap_Avg_fC4_D3"  ,"HBHE:  600fC<TS4<2000fC , Avg TS5/TS4 Depth 3", 60, -30, 30, 74, 0, 74);

  float TS4=0, TS5=0, hbhe_energy=0;
  int   hbhe_depth=0, hbhe_ieta=0, hbhe_iphi=0;

  int  nTS_fired[3] ={0,0,0};

  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 1000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));

    // nObj = total # of HBHE pulses in the current event
    nHBHEDigis = hbheDigis->GetSize();  

    // Loop over all HBHE pulses in the current event to fill a TS Entry
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);
      for(int i=0;i<3;i++){ nTS_fired[i]=0;}
      for (int n=0; n<10; ++n) {
	// Estimate the pedestal event by event
	if( hbheDigi.fc(n)>30 ){
		HBHE_TSdist_30->Fill(n);
		if( hbheDigi.ieta()== -22 && hbheDigi.iphi() ==5){
			HBHE_TSdist_22_5->Fill(n);
		}
		nTS_fired[0]++;
		if( hbheDigi.fc(n) >50 ){
			HBHE_TSdist_50->Fill(n);
			nTS_fired[1]++;
			if( hbheDigi.fc(n)>100 ){
				HBHE_TSdist_100->Fill(n); 
				nTS_fired[2]++;
			}
		}
	}
      }
      HBHE_nTS_fired_30->Fill(nTS_fired[0]);	
      HBHE_nTS_fired_50->Fill(nTS_fired[1]);
      HBHE_nTS_fired_100->Fill(nTS_fired[2]);	
      TS4 = hbheDigi.fc(4);
      TS5 = hbheDigi.fc(5);
      hbhe_depth  = hbheDigi.depth();
      hbhe_energy = hbheDigi.energy();
      hbhe_ieta =   hbheDigi.ieta();
      hbhe_iphi =   hbheDigi.iphi();

      // Fill the TS5/TS4 ratio map of HBHE, Binned by energies
	if(hbhe_energy>5)		HBHE_Energy_D1->Fill( hbhe_energy );
	 if(TS4>30){
		if( hbhe_iphi >=3  && hbhe_iphi<=26) HBHE_TSRatio_a->Fill(TS5/TS4);
		if( hbhe_iphi >=27 && hbhe_iphi<=50) HBHE_TSRatio_b->Fill(TS5/TS4);
		 if( (hbhe_iphi >=51 && hbhe_iphi<=72) || hbhe_iphi==1 || hbhe_iphi==2) HBHE_TSRatio_c->Fill(TS5/TS4);
	 }
	 if(hbhe_depth==1){
	 	if(TS4>30){
	 		HBHE_TSRatio_D1 ->Fill(TS5/TS4);
		        HBHE_TSRatioMap_D1_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
		        HBHE_TSRatioMap_D1_sum2[hbhe_ieta+30][hbhe_iphi]+= ((TS5/TS4)*(TS5/TS4));
		        HBHE_TSRatioMap_D1_nEvt[hbhe_ieta+30][hbhe_iphi]++;
		}
		if(TS4>30 && TS4<100)  {
			HBHE_TSRatioMap_fC1_D1_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC1_D1_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC1_D1->Fill(TS5/TS4);
		}
		if(TS4>100 && TS4<200)  {
			HBHE_TSRatioMap_fC2_D1_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC2_D1_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC2_D1->Fill(TS5/TS4);
		}
		if(TS4>200 && TS4<600)  {
			HBHE_TSRatioMap_fC3_D1_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC3_D1_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC3_D1->Fill(TS5/TS4);
		}
		if(TS4>600 && TS4<2000)  {
			HBHE_TSRatioMap_fC4_D1_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC4_D1_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC4_D1->Fill(TS5/TS4);
		}
	 }
	 if(hbhe_depth==2){ 
		if(TS4>30){
	 		HBHE_TSRatio_D2 ->Fill(TS5/TS4);
		        HBHE_TSRatioMap_D2_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
		        HBHE_TSRatioMap_D2_sum2[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4)*(TS5/TS4);
		        HBHE_TSRatioMap_D2_nEvt[hbhe_ieta+30][hbhe_iphi]++;
		}
		if(TS4>30 && TS4<100)  {
			HBHE_TSRatioMap_fC1_D2_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC1_D2_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC1_D2->Fill(TS5/TS4);
		}
		if(TS4>100 && TS4<200)  {
			HBHE_TSRatioMap_fC2_D2_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC2_D2_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC2_D2->Fill(TS5/TS4);
		}
		if(TS4>200 && TS4<600)  {
			HBHE_TSRatioMap_fC3_D2_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC3_D2_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC3_D2->Fill(TS5/TS4);
		}
		if(TS4>600 && TS4<2000)  {
			HBHE_TSRatioMap_fC4_D2_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC4_D2_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC4_D2->Fill(TS5/TS4);
		}
	 }
	 if(hbhe_depth==3){ 
		if(TS4>30){
	 		HBHE_TSRatio_D3 ->Fill(TS5/TS4);
		        HBHE_TSRatioMap_D3_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
		        HBHE_TSRatioMap_D3_sum2[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4)*(TS5/TS4);
		        HBHE_TSRatioMap_D3_nEvt[hbhe_ieta+30][hbhe_iphi]++;
		}
		if(TS4>30 && TS4<100)  {
			HBHE_TSRatioMap_fC1_D3_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC1_D3_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC1_D3->Fill(TS5/TS4);
		}
		if(TS4>100 && TS4<200)  {
			HBHE_TSRatioMap_fC2_D3_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC2_D3_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC2_D3->Fill(TS5/TS4);
		}
		if(TS4>200 && TS4<600)  {
			HBHE_TSRatioMap_fC3_D3_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC3_D3_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC3_D3->Fill(TS5/TS4);
		}
		if(TS4>600 && TS4<2000)  {
			HBHE_TSRatioMap_fC4_D3_sum[hbhe_ieta+30][hbhe_iphi]+=(TS5/TS4);
			HBHE_TSRatioMap_fC4_D3_nEvt[hbhe_ieta+30][hbhe_iphi]++;
			HBHE_TSRatio_fC4_D3->Fill(TS5/TS4);
		}

	 }

      // Fill the histograms of HBHE TS ratios:  
    }
    /////////////// Loop over HF pulses  ///////////////////////////////////////////////
    int hf_depth =0, hf_ieta=0, hf_iphi=0;
    float hf_energy = 0 ,hf_time =0, TS0=0, TS1=0, TS2=0,TS3=0;
    int nEvt_D1_b4[86][74],nEvt_D1_after[86][74];
    int nEvt_D2_b4[86][74],nEvt_D2_after[86][74];
    int HF_D1_isFired[86][74],HF_D2_isFired[86][74];

    for(int i=0;i<86;i++){
	for(int j=0;j<74;j++){
		nEvt_D1_b4[i][j] = HF_TSRatioMap_D1_nEvt[i][j];
		nEvt_D2_b4[i][j] = HF_TSRatioMap_D2_nEvt[i][j];
		HF_D1_isFired[i][j] = 0;
		HF_D2_isFired[i][j] = 0;
	}
    }

    CollectionPtr hfDigis (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));

    nHFDigis = hfDigis -> GetSize();

    for (int iHFDigi = 0; iHFDigi < nHFDigis; ++iHFDigi){
       HFDigi hfDigi = hfDigis -> GetConstituent<HFDigi>(iHFDigi); 

       hf_depth  = hfDigi.depth();
       hf_ieta  =  hfDigi.ieta();
       hf_iphi  =  hfDigi.iphi();
       hf_energy = hfDigi.energy(); 
       hf_time   = hfDigi.recHitTime();
       TS0       = hfDigi.fc(0); 
       TS1       = hfDigi.fc(1); 
       TS2       = hfDigi.fc(2); 
       TS3       = hfDigi.fc(3); 
       if(hf_energy>5){
		// center of TS2 = 12.5 ns, output time weighted by charge collected in TS1 and TS2
		HF_Time_TSWeight ->Fill( -12.5*(TS1/TS2) + 12.5*(1- TS1/TS2));
	 if(hf_depth==1){ 
            if(HF_D1_isFired[hf_ieta+43][hf_iphi]==0){
		HF_Time_D1  ->Fill( hf_time );
	 	HF_Time_Ratio_D1 ->Fill( hf_time, TS1/TS2);
	 	HF_TSRatio_D1 ->Fill(TS1/TS2);
		HF_TSRatioMap_D1_sum[hf_ieta+43][hf_iphi]+=(TS1/TS2);
		HF_TSRatioMap_D1_sum2[hf_ieta+43][hf_iphi]+=( (TS1/TS2)*(TS1/TS2));
		HF_TSRatioMap_D1_nEvt[hf_ieta+43][hf_iphi]++;
		HF_D1_isFired[hf_ieta+43][hf_iphi]++;
		if(hf_energy>5 && hf_energy<10)   {
			HF_TSRatioMap_E1_D1_sum[hf_ieta+43][hf_iphi]+=(TS1/TS2);
			HF_TSRatioMap_E1_D1_nEvt[hf_ieta+43][hf_iphi]++;
			HF_TSRatio_E1_D1 ->Fill(TS1/TS2);
		}
		if(hf_energy>=10 && hf_energy<20) {
			HF_TSRatioMap_E2_D1_sum[hf_ieta+43][hf_iphi]+=(TS1/TS2);		
			HF_TSRatioMap_E2_D1_nEvt[hf_ieta+43][hf_iphi]++;		
			HF_TSRatio_E2_D1 ->Fill(TS1/TS2);
		}
		if(hf_energy>=20)		  {
			HF_TSRatioMap_E3_D1_sum[hf_ieta+43][hf_iphi]+=(TS1/TS2);
			HF_TSRatioMap_E3_D1_nEvt[hf_ieta+43][hf_iphi]++;
			HF_TSRatio_E3_D1 ->Fill(TS1/TS2);
		}
	    }
	 }
	 if(hf_depth==2){
	    if(HF_D2_isFired[hf_ieta+43][hf_iphi]==0){
		 HF_Time_D2  ->Fill( hf_time );
	 	 HF_Time_Ratio_D2 ->Fill( hf_time, TS1/TS2); 
	 	 HF_TSRatio_D2 ->Fill(TS1/TS2);
    		 HF_TSRatioMap_D2_sum[hf_ieta+43][hf_iphi]+=(TS1/TS2);
    		 HF_TSRatioMap_D2_sum2[hf_ieta+43][hf_iphi]+= ((TS1/TS2)*(TS1/TS2));
    		 HF_TSRatioMap_D2_nEvt[hf_ieta+43][hf_iphi]++;
		 HF_D2_isFired[hf_ieta+43][hf_iphi]++;
		
		if(hf_energy>5 && hf_energy<10)   {
			HF_TSRatioMap_E1_D2_sum[hf_ieta+43][hf_iphi]+=(TS1/TS2);
			HF_TSRatioMap_E1_D2_nEvt[hf_ieta+43][hf_iphi]++;
			HF_TSRatio_E1_D2 ->Fill(TS1/TS2);
		}
		if(hf_energy>=10 && hf_energy<20) {
			HF_TSRatioMap_E2_D2_sum[hf_ieta+43][hf_iphi]+=(TS1/TS2);
			HF_TSRatioMap_E2_D2_nEvt[hf_ieta+43][hf_iphi]++;
			HF_TSRatio_E2_D2 ->Fill(TS1/TS2);
		}
		if(hf_energy>=20)		  {
			HF_TSRatioMap_E3_D2_sum[hf_ieta+43][hf_iphi]+=(TS1/TS2);
			HF_TSRatioMap_E3_D2_nEvt[hf_ieta+43][hf_iphi]++;
			HF_TSRatio_E3_D2 ->Fill(TS1/TS2);
		}
	    }
	 }
	 if( hf_time <-7 && hf_time>-9 && TS1/TS2 >0 && TS1/TS2 <0.2) {
		HF_Time_fC ->Fill(0.5,TS0);
		HF_Time_fC ->Fill(1.5,TS1);
		HF_Time_fC ->Fill(2.5,TS2);
		HF_Time_fC ->Fill(3.5,TS3);
		N_HF_TS++;
		 if(hf_depth==1){
			if(TS0>40) 	   HF_TimeMap_TS0_D1->Fill( hf_ieta, hf_iphi);
			if(TS2>60)	   HF_TimeMap_TS2_D1->Fill( hf_ieta, hf_iphi);
			if(TS0>40&&TS2>60) HF_TimeMap_TS0TS2_D1->Fill( hf_ieta, hf_iphi);
		 }
		 if(hf_depth==2){
			if(TS0>40) 	   HF_TimeMap_TS0_D2->Fill( hf_ieta, hf_iphi);
			if(TS2>60)	   HF_TimeMap_TS2_D2->Fill( hf_ieta, hf_iphi);
			if(TS0>40&&TS2>60) HF_TimeMap_TS0TS2_D2->Fill( hf_ieta, hf_iphi);
	 	}

	//std::cout<< (*HFDigiFC)[iHFPulse][0] <<"   " <<TS1<<"    "<<TS2<<"    "<< (*HFDigiFC)[iHFPulse][3] <<std::endl;
	 }
	 if(hf_time>0) 				  HF_Energy_Tplus ->Fill(hf_energy);
         if(hf_time<0 && hf_time>-50)		  HF_Energy_Tminus->Fill(hf_energy);
      }
     
    }// end of HF pulse loop
    for(int i=0;i<86;i++){
        for(int j=0;j<74;j++){
                nEvt_D1_after[i][j] = HF_TSRatioMap_D1_nEvt[i][j];
                nEvt_D2_after[i][j] = HF_TSRatioMap_D2_nEvt[i][j];
		if( ( nEvt_D1_after[i][j] - nEvt_D1_b4[i][j] )>1){
			  HF_TSRatioMap_Double_D1->Fill(i-43,j);
//			  cout <<" Before = "<<nEvt_D1_b4[i][j] << " After = "<<nEvt_D1_after[i][j]<<"  Diff= " << nEvt_D1_after[i][j] - nEvt_D1_b4[i][j] <<endl;
		}
		if( ( nEvt_D2_after[i][j] - nEvt_D2_b4[i][j] )>1)  HF_TSRatioMap_Double_D2->Fill(i-43,j);
        }
    }

    }// end of event loop

  //--------------------------------------------------------------------------------
  // Analysis
  //--------------------------------------------------------------------------------
  HF_Time_fC->Scale(1./N_HF_TS);
  std::cout << "Read " << n_events << " events" << std::endl;

  const int n_HBHE_fault=1000;
  int n_HBHE_D1=0, n_HBHE_D2=0, n_HBHE_D3=0;
  char hname[100],htitle[100];

  // Filling the HBHE 2D Ratio map: 
  std::cout<<"List of HBHE D1 channels:"<<std::endl; 
  float hbhe_avg[5]={0,0,0,0,0}, hbhe_rms=0;
  float hbhe_D1_avg= HBHE_TSRatio_D1->GetMean();
  float hbhe_D2_avg= HBHE_TSRatio_D2->GetMean();
  float hbhe_D3_avg= HBHE_TSRatio_D3->GetMean();
  for (int i=0; i<60; i++) {
  	for (int j=0; j<74; j++) {
		if( HBHE_TSRatioMap_D1_nEvt[i][j] !=0){
			hbhe_avg[0] = HBHE_TSRatioMap_D1_sum[i][j] / HBHE_TSRatioMap_D1_nEvt[i][j];
			hbhe_rms = sqrt( (HBHE_TSRatioMap_D1_sum2[i][j] / HBHE_TSRatioMap_D1_nEvt[i][j])   -  (hbhe_avg[0])*(hbhe_avg[0]));  //RMS = sqrt(<X^2> - <X>^2)

			hbhe_avg[1] = HBHE_TSRatioMap_fC1_D1_sum[i][j] / HBHE_TSRatioMap_fC1_D1_nEvt[i][j];
			hbhe_avg[2] = HBHE_TSRatioMap_fC2_D1_sum[i][j] / HBHE_TSRatioMap_fC2_D1_nEvt[i][j];
			hbhe_avg[3] = HBHE_TSRatioMap_fC3_D1_sum[i][j] / HBHE_TSRatioMap_fC3_D1_nEvt[i][j];
			hbhe_avg[4] = HBHE_TSRatioMap_fC4_D1_sum[i][j] / HBHE_TSRatioMap_fC4_D1_nEvt[i][j];
			if(  hbhe_avg[0] >2 || hbhe_rms> 10 ){
				std::cout<<"HBHE Depth =1 IEta= "<<i-43<<" IPhi= "<<j<<"      avg(TS1/TS2) = "<<hbhe_avg[0];
										cout<<"     rms(TS1/TS2) = "<<hbhe_rms;
										cout<<"     nEvt = "<< HBHE_TSRatioMap_D1_nEvt[i][j] <<endl;	
				n_HBHE_D1++;
			}
			HBHE_TSRatioMap_nEvt_D1  ->SetBinContent(i,j,HBHE_TSRatioMap_D1_nEvt[i][j] );
			HBHE_TSRatioMap_Avg_D1   ->SetBinContent(i,j,hbhe_avg[0]);
			HBHE_TSRatioMap_Rms_D1   ->SetBinContent(i,j,hbhe_rms);
			HBHE_TSRatioMap_Pull_D1  ->SetBinContent(i,j,abs(hbhe_avg[0]-hbhe_D1_avg)/ (hbhe_rms/ sqrt(HBHE_TSRatioMap_D1_nEvt[i][j])));
			HBHE_TSRatioMap_Avg_fC1_D1->SetBinContent(i,j,hbhe_avg[1]);
			HBHE_TSRatioMap_Avg_fC2_D1->SetBinContent(i,j,hbhe_avg[2]);
			HBHE_TSRatioMap_Avg_fC3_D1->SetBinContent(i,j,hbhe_avg[3]);
			HBHE_TSRatioMap_Avg_fC4_D1->SetBinContent(i,j,hbhe_avg[4]);
		}
	}
   }
  std::cout<<"# of fault HBHE D1 channels:  "<<n_HBHE_D1 <<std::endl; 
  std::cout<<"List of HBHE D2 channels:"<<std::endl; 
   for (int i=0; i<60; i++) {
  	for (int j=0; j<74; j++) {
		if( HBHE_TSRatioMap_D2_nEvt[i][j] !=0){
			hbhe_avg[0] = HBHE_TSRatioMap_D2_sum[i][j] / HBHE_TSRatioMap_D2_nEvt[i][j];
			hbhe_rms = sqrt( (HBHE_TSRatioMap_D2_sum2[i][j] / HBHE_TSRatioMap_D2_nEvt[i][j])   -  (hbhe_avg[0])*(hbhe_avg[0]));  //RMS = sqrt(<X^2> - <X>^2)

			hbhe_avg[1] = HBHE_TSRatioMap_fC1_D2_sum[i][j] / HBHE_TSRatioMap_fC1_D2_nEvt[i][j];
			hbhe_avg[2] = HBHE_TSRatioMap_fC2_D2_sum[i][j] / HBHE_TSRatioMap_fC2_D2_nEvt[i][j];
			hbhe_avg[3] = HBHE_TSRatioMap_fC3_D2_sum[i][j] / HBHE_TSRatioMap_fC3_D2_nEvt[i][j];
			hbhe_avg[4] = HBHE_TSRatioMap_fC4_D2_sum[i][j] / HBHE_TSRatioMap_fC4_D2_nEvt[i][j];
			if(  hbhe_avg[0] >2 || hbhe_rms> 10 ){
				std::cout<<"HBHE Depth =1 IEta= "<<i-43<<" IPhi= "<<j<<"      avg(TS1/TS2) = "<<hbhe_avg[0];
										cout<<"     rms(TS1/TS2) = "<<hbhe_rms;
										cout<<"     nEvt = "<< HBHE_TSRatioMap_D2_nEvt[i][j] <<endl;	
				n_HBHE_D2++;
			}
			HBHE_TSRatioMap_nEvt_D2  ->SetBinContent(i,j,HBHE_TSRatioMap_D2_nEvt[i][j] );
			HBHE_TSRatioMap_Avg_D2   ->SetBinContent(i,j,hbhe_avg[0]);
			HBHE_TSRatioMap_Rms_D2   ->SetBinContent(i,j,hbhe_rms);
			HBHE_TSRatioMap_Pull_D2  ->SetBinContent(i,j,abs(hbhe_avg[0]-hbhe_D2_avg)/ (hbhe_rms/ sqrt(HBHE_TSRatioMap_D2_nEvt[i][j])));
			HBHE_TSRatioMap_Avg_fC1_D2->SetBinContent(i,j,hbhe_avg[1]);
			HBHE_TSRatioMap_Avg_fC2_D2->SetBinContent(i,j,hbhe_avg[2]);
			HBHE_TSRatioMap_Avg_fC3_D2->SetBinContent(i,j,hbhe_avg[3]);
			HBHE_TSRatioMap_Avg_fC4_D2->SetBinContent(i,j,hbhe_avg[4]);
		}
	}
   }

  std::cout<<"# of fault HBHE D2 channels:  "<<n_HBHE_D2 <<std::endl; 
  std::cout<<"List of HBHE D3 channels:"<<std::endl; 
  for (int i=0; i<60; i++) {
  	for (int j=0; j<74; j++) {
		if( HBHE_TSRatioMap_D3_nEvt[i][j] !=0){
			hbhe_avg[0] = HBHE_TSRatioMap_D3_sum[i][j] / HBHE_TSRatioMap_D3_nEvt[i][j];
			hbhe_rms = sqrt( (HBHE_TSRatioMap_D3_sum2[i][j] / HBHE_TSRatioMap_D3_nEvt[i][j])   -  (hbhe_avg[0])*(hbhe_avg[0]));  //RMS = sqrt(<X^2> - <X>^2)

			hbhe_avg[1] = HBHE_TSRatioMap_fC1_D3_sum[i][j] / HBHE_TSRatioMap_fC1_D3_nEvt[i][j];
			hbhe_avg[2] = HBHE_TSRatioMap_fC2_D3_sum[i][j] / HBHE_TSRatioMap_fC2_D3_nEvt[i][j];
			hbhe_avg[3] = HBHE_TSRatioMap_fC3_D3_sum[i][j] / HBHE_TSRatioMap_fC3_D3_nEvt[i][j];
			hbhe_avg[4] = HBHE_TSRatioMap_fC4_D3_sum[i][j] / HBHE_TSRatioMap_fC4_D3_nEvt[i][j];
			if(  hbhe_avg[0] >2 || hbhe_rms> 10 ){
				std::cout<<"HBHE Depth =1 IEta= "<<i-43<<" IPhi= "<<j<<"      avg(TS1/TS2) = "<<hbhe_avg[0];
										cout<<"     rms(TS1/TS2) = "<<hbhe_rms;
										cout<<"     nEvt = "<< HBHE_TSRatioMap_D3_nEvt[i][j] <<endl;	
				n_HBHE_D3++;
			}
			HBHE_TSRatioMap_nEvt_D3  ->SetBinContent(i,j,HBHE_TSRatioMap_D3_nEvt[i][j] );
			HBHE_TSRatioMap_Avg_D3   ->SetBinContent(i,j,hbhe_avg[0]);
			HBHE_TSRatioMap_Rms_D3   ->SetBinContent(i,j,hbhe_rms);
			HBHE_TSRatioMap_Pull_D3  ->SetBinContent(i,j,abs(hbhe_avg[0]-hbhe_D3_avg)/ (hbhe_rms/ sqrt(HBHE_TSRatioMap_D3_nEvt[i][j])));
			HBHE_TSRatioMap_Avg_fC1_D2->SetBinContent(i,j,hbhe_avg[1]);
			HBHE_TSRatioMap_Avg_fC1_D3->SetBinContent(i,j,hbhe_avg[1]);
			HBHE_TSRatioMap_Avg_fC2_D3->SetBinContent(i,j,hbhe_avg[2]);
			HBHE_TSRatioMap_Avg_fC3_D3->SetBinContent(i,j,hbhe_avg[3]);
			HBHE_TSRatioMap_Avg_fC4_D3->SetBinContent(i,j,hbhe_avg[4]);
		}
	}
   }

  std::cout<<"# of fault HBHE D3 channels:  "<<n_HBHE_D3 <<std::endl; 

  // Fill the HF 2F Ratio map: 
  std::cout<<"List of HF D1 channels:"<<std::endl; 
  int n_HF_D1=0, n_HF_D2=0;
  float avg_d1[4] ={0,0,0,0}, rms_d1=0 ;
  for(int i=0;i<86;i++){
	for(int j=0;j<74;j++){
		if( HF_TSRatioMap_D1_nEvt[i][j] !=0){
			avg_d1[0] = HF_TSRatioMap_D1_sum[i][j] / HF_TSRatioMap_D1_nEvt[i][j];
			rms_d1 = sqrt( (HF_TSRatioMap_D1_sum2[i][j] / HF_TSRatioMap_D1_nEvt[i][j])   -  (avg_d1[0])*(avg_d1[0]));  //RMS = sqrt(<X^2> - <X>^2)

			avg_d1[1] = HF_TSRatioMap_E1_D1_sum[i][j] / HF_TSRatioMap_E1_D1_nEvt[i][j];
			avg_d1[2] = HF_TSRatioMap_E2_D1_sum[i][j] / HF_TSRatioMap_E2_D1_nEvt[i][j];
			avg_d1[3] = HF_TSRatioMap_E3_D1_sum[i][j] / HF_TSRatioMap_E3_D1_nEvt[i][j];
			if(  avg_d1[0] >2 || rms_d1> 10 ){
				std::cout<<"HF Depth =1 IEta= "<<i-43<<" IPhi= "<<j<<"      avg(TS1/TS2) = "<<avg_d1[0];
										cout<<"     rms(TS1/TS2) = "<<rms_d1;
										cout<<"	    sum = " << HF_TSRatioMap_D1_sum[i][j];
										cout<<"	    sum2 = " << HF_TSRatioMap_D1_sum2[i][j];
										cout<<"     nEvt = "<< HF_TSRatioMap_D1_nEvt[i][j] <<endl;
				n_HF_D1++;
			}
			HF_TSRatioMap_nEvt_D1  ->SetBinContent(i,j,HF_TSRatioMap_D1_nEvt[i][j] );
			HF_TSRatioMap_Avg_D1   ->SetBinContent(i,j,avg_d1[0]);
			HF_TSRatioMap_Rms_D1   ->SetBinContent(i,j,rms_d1);
			HF_TSRatioMap_Avg_E1_D1->SetBinContent(i,j,avg_d1[1]);
			HF_TSRatioMap_Avg_E2_D1->SetBinContent(i,j,avg_d1[2]);
			HF_TSRatioMap_Avg_E3_D1->SetBinContent(i,j,avg_d1[3]);
		}
  	}
  }
  float avg_d2[4] ={0,0,0,0}, rms_d2 =0;
  std::cout<<"# of fault HF D1 channels:  "<<n_HF_D1 <<std::endl; 
  std::cout<<"List of HF D2 channels:"<<std::endl; 
  for(int i=0;i<86;i++){
	for(int j=0;j<74;j++){
		if( HF_TSRatioMap_D2_nEvt[i][j] !=0){
			avg_d2[0] = HF_TSRatioMap_D2_sum[i][j] / HF_TSRatioMap_D2_nEvt[i][j];
			rms_d2 = sqrt( (HF_TSRatioMap_D2_sum2[i][j] / HF_TSRatioMap_D2_nEvt[i][j])   -  (avg_d2[0])*(avg_d2[0]));  //RMS = sqrt(<X^2> - <X>^2)

			avg_d2[1] = HF_TSRatioMap_E1_D2_sum[i][j] / HF_TSRatioMap_E1_D2_nEvt[i][j];
			avg_d2[2] = HF_TSRatioMap_E2_D2_sum[i][j] / HF_TSRatioMap_E2_D2_nEvt[i][j];
			avg_d2[3] = HF_TSRatioMap_E3_D2_sum[i][j] / HF_TSRatioMap_E3_D2_nEvt[i][j];
			if(  avg_d2[0] >2 || rms_d2> 10 ){
				std::cout<<"HF Depth =2 IEta= "<<i-43<<" IPhi= "<<j<<"      avg(TS1/TS2) = "<<avg_d2[0];
										cout<<"     rms(TS1/TS2) = "<<rms_d2;
										cout<<"	    sum = " << HF_TSRatioMap_D2_sum[i][j];
										cout<<"	    sum2 = " << HF_TSRatioMap_D2_sum2[i][j];
										cout<<"     nEvt = "<< HF_TSRatioMap_D2_nEvt[i][j] <<endl;
				n_HF_D2++;	
			}
			HF_TSRatioMap_nEvt_D2  ->SetBinContent(i,j,HF_TSRatioMap_D2_nEvt[i][j] );
			HF_TSRatioMap_Avg_D2   ->SetBinContent(i,j,avg_d2[0]);
			HF_TSRatioMap_Rms_D2   ->SetBinContent(i,j,rms_d2);
			HF_TSRatioMap_Avg_E1_D2->SetBinContent(i,j,avg_d2[1]);
			HF_TSRatioMap_Avg_E2_D2->SetBinContent(i,j,avg_d2[2]);
			HF_TSRatioMap_Avg_E3_D2->SetBinContent(i,j,avg_d2[3]);
		}
  	}
  }

  cout<< "HBHE Depth 1 "<<endl;
  std::cout << "Read " << HBHE_TSRatio_fC1_D1->GetEntries() << " events with 30fC<TS4<100fC" << std::endl;
  std::cout << "Read " << HBHE_TSRatio_fC2_D1->GetEntries() << " events with 100fC<TS4<200fC" << std::endl;
  std::cout << "Read " << HBHE_TSRatio_fC3_D1->GetEntries() << " events with 200fC<TS4<600fC" << std::endl;
  std::cout << "Read " << HBHE_TSRatio_fC4_D1->GetEntries() << " events with 600fC<TS4<2000fC" << std::endl;

  HF_TSRatioMap_nEvt_D1->GetZaxis()->SetRangeUser(0,HF_TSRatioMap_nEvt_D1->GetMaximum());
  HF_TSRatioMap_Avg_D1->GetZaxis()->SetRangeUser(0,HF_TSRatioMap_Avg_D1->GetMaximum());
  HF_TSRatioMap_Avg_E1_D1->GetZaxis()->SetRangeUser(0,HF_TSRatioMap_Avg_E1_D1->GetMaximum());
  HF_TSRatioMap_Avg_E2_D1->GetZaxis()->SetRangeUser(0,HF_TSRatioMap_Avg_E2_D1->GetMaximum());
  HF_TSRatioMap_Avg_E3_D1->GetZaxis()->SetRangeUser(0,HF_TSRatioMap_Avg_E3_D1->GetMaximum());
  HF_TSRatioMap_nEvt_D2->GetZaxis()->SetRangeUser(0,HF_TSRatioMap_nEvt_D2->GetMaximum());
  HF_TSRatioMap_Avg_D2->GetZaxis()->SetRangeUser(0,HF_TSRatioMap_Avg_D2->GetMaximum());
  HF_TSRatioMap_Avg_E1_D2->GetZaxis()->SetRangeUser(0,HF_TSRatioMap_Avg_E1_D2->GetMaximum());
  HF_TSRatioMap_Avg_E2_D2->GetZaxis()->SetRangeUser(0,HF_TSRatioMap_Avg_E2_D2->GetMaximum());
  HF_TSRatioMap_Avg_E3_D2->GetZaxis()->SetRangeUser(0,HF_TSRatioMap_Avg_E3_D2->GetMaximum());
 

}
