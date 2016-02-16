//
// This code creates an array of TS0-9 collections to be analyzed
// Then it performs the analysis of looking at 
//
//

using namespace std;
#include <stdio.h>
#include <iostream>
#include "TH1.h"
#include "TH2.h"
#include "TProfile2D.h"
#include "TF1.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TPad.h"

#include <TROOT.h>
#include <TBranch.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <vector>


//void Hcal_Timing_v2()
void Hcal_Timing_v2(int runNumber,TString stream)
{
  gROOT->ProcessLine(".L loader.C+");
  std::vector< std::vector<float> > *HBHEDigiFC		=0;
  std::vector<int>  *HBHEDigiIEta			=0;
  std::vector<int>  *HBHEDigiIPhi			=0;
  std::vector<int>  *HBHEDigiDepth			=0;
  std::vector<float>  *HBHEDigiRecEnergy		=0;

  std::vector< std::vector<float> > *HFDigiFC		=0;
  std::vector<int>    *HFDigiDepth			=0;
  std::vector<int>    *HFDigiIEta			=0;
  std::vector<int>    *HFDigiIPhi			=0;
  std::vector<float>  *HFDigiRecEnergy			=0;
  std::vector<float>  *HFDigiRecTime			=0;

  TBranch *b_HFDigiFC		=0;
  TBranch *b_HFDigiDepth	=0;
  TBranch *b_HFDigiIEta		=0;
  TBranch *b_HFDigiIPhi		=0;
  TBranch *b_HFDigiRecEnergy	=0;
  TBranch *b_HFDigiRecTime	=0;
  TBranch *b_HBHEDigiFC		=0;
  TBranch *b_HBHEDigiIEta	=0;
  TBranch *b_HBHEDigiIPhi	=0;
  TBranch *b_HBHEDigiDepth	=0;
  TBranch *b_HBHEDigiRecEnergy	=0;

  char inputFile[100], outputFile[100];

  //sprintf(inputFile,"/mnt/hadoop/users/mkwok/HCAL/%i/HCAL_DigiTiming_%i_*.root",runNumber,runNumber);
  //sprintf(inputFile,"root://eoscms//eos/cms/store/user/klo//Collision_%i/*.root",runNumber);
  //sprintf(inputFile,"../output/%i/HCAL_DigiTiming_%i_*.root",runNumber,runNumber);
  sprintf(inputFile,"../output/%i/HCAL_DigiTiming_noise_%i_*.root",runNumber,runNumber);
  TChain chain("hcalTupleTree/tree");
  //chain.Add("../output/251252/HCAL_DigiTiming_251252_90.root");
  
  cout<<"Adding files from :"<< inputFile<<endl;
  chain.Add(inputFile);
  chain.LoadTree(0);

  chain.SetBranchAddress("HBHEDigiFC", &HBHEDigiFC, &b_HBHEDigiFC);
  chain.SetBranchAddress("HBHEDigiIEta", &HBHEDigiIEta, &b_HBHEDigiIEta);
  chain.SetBranchAddress("HBHEDigiIPhi", &HBHEDigiIPhi, &b_HBHEDigiIPhi);
  chain.SetBranchAddress("HBHEDigiDepth", &HBHEDigiDepth, &b_HBHEDigiDepth);
  chain.SetBranchAddress("HBHEDigiRecEnergy", &HBHEDigiRecEnergy, &b_HBHEDigiRecEnergy);
  chain.SetBranchAddress("HFDigiFC", &HFDigiFC, &b_HFDigiFC);
  chain.SetBranchAddress("HFDigiIEta", &HFDigiIEta, &b_HFDigiIEta);
  chain.SetBranchAddress("HFDigiIPhi", &HFDigiIPhi, &b_HFDigiIPhi);
  chain.SetBranchAddress("HFDigiDepth", &HFDigiDepth, &b_HFDigiDepth);
  chain.SetBranchAddress("HFDigiRecEnergy", &HFDigiRecEnergy, &b_HFDigiRecEnergy);
  chain.SetBranchAddress("HFDigiRecTime", &HFDigiRecTime, &b_HFDigiRecTime);

  std::cout << "Opened chain " << chain.GetName() << std::endl;

  const int nentries = chain.GetEntries();
  cout << chain.GetEntries() <<endl;
  //const int nentries = 5000;
  std::cout << "nentries is : " << nentries << std::endl;

  // Initialize the 2D arrays

  int N_TS4_cut[4]={0,0,0,0} ;
  int N_HF_TS=0 ;
  int event = 0;
  int nHBHEDigiSize = 0, nHFDigiSize =0 ; 		//# of pulses in each event
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

  TH1F *HF_Time_D1  	 = new TH1F("HF_Time_D1"         ,"HF: E>5GeV, Depth 1", 50, -50, 50);
  TH1F *HF_Time_D2  	 = new TH1F("HF_Time_D2"         ,"HF: E>5GeV  Depth 2", 50, -50, 50);
  TH1F *HF_Time_TSWeight = new TH1F("HF_Time_TSWeight"   ,"HF: E>5GeV  time weighted by TS1/TS2", 50, -50, 50);

  TH2F *HF_Time_Ratio_D1 = new TH2F("HF_Time_Ratio_D1"   ,"HF: E>5GeV Depth 1", 50, -50, 50, 10, 0, 0);
  TH2F *HF_Time_Ratio_D2 = new TH2F("HF_Time_Ratio_D2"   ,"HF: E>5GeV Depth 2", 50, -50, 50, 10, 0, 0);
  TH2F *HF_TimeMap_TS0_D1      = new TH2F("HF_TimeMap_TS0_D1"  ,"HF: E>5GeV, TS0>40fC, Depth 1", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TimeMap_TS0_D2      = new TH2F("HF_TimeMap_TS0_D2"  ,"HF: E>5GeV, TS0>40fC  Depth 2", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TimeMap_TS2_D1      = new TH2F("HF_TimeMap_TS2_D1"  ,"HF: E>5GeV, TS2>60fC  Depth 1", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TimeMap_TS2_D2      = new TH2F("HF_TimeMap_TS2_D2"  ,"HF: E>5GeV, TS2>60fC  Depth 2", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TimeMap_TS0TS2_D1   = new TH2F("HF_TimeMap_TS0TS2_D1"  ,"HF: E>5GeV, TS2>60fC && TS0>40fC  Depth 1", 86, -43, 43, 74, 0, 74);
  TH2F *HF_TimeMap_TS0TS2_D2   = new TH2F("HF_TimeMap_TS0TS2_D2"  ,"HF: E>5GeV, TS2>60fC && TS0>40fC  Depth 2", 86, -43, 43, 74, 0, 74);
  TH1F *HF_Time_fC  	 = new TH1F("HF_Time_fC"      ,"HF: E>5GeV, -9ns<t<-7ns, |TS1/TS2|<0.2", 4, 0, 4);
 
  // Maps of HF uniformity in TS1/TS2, binned by energy
  TH1F *HF_TSRatio_D1		      = new TH1F("HF_TSRatio_D1","HF: E>5GeV Depth 1", 40, 0,0);
  TH1F *HF_TSRatio_E1_D1	      = new TH1F("HF_TSRatio_E1_D1","HF: 5GeV<E<10GeV Depth 1", 40, 0,0);
  TH1F *HF_TSRatio_E2_D1	      = new TH1F("HF_TSRatio_E2_D1","HF: 10GeV<E<20GeV Depth 1", 40, 0,0);
  TH1F *HF_TSRatio_E3_D1	      = new TH1F("HF_TSRatio_E3_D1","HF: E>20GeV Depth 1", 40, 0,0);

  TH1F *HF_TSRatio_D2		      = new TH1F("HF_TSRatio_D2","HF: E>5GeV Depth 2", 40, 0,0);
  TH1F *HF_TSRatio_E1_D2	      = new TH1F("HF_TSRatio_E1_D2","HF: 5GeV<E<10GeV Depth 2", 40, 0,0);
  TH1F *HF_TSRatio_E2_D2	      = new TH1F("HF_TSRatio_E2_D2","HF: 10GeV<E<20GeV Depth 2", 40, 0,0);
  TH1F *HF_TSRatio_E3_D2	      = new TH1F("HF_TSRatio_E3_D2","HF: E>20GeV Depth 2", 40, 0,0);

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

  TH1F *HF_Energy_Tplus  = new TH1F("HF_Energy_Tplus" ,"HF E>5GeV w/ t>0", 75, 0, 75);
  TH1F *HF_Energy_Tminus = new TH1F("HF_Energy_Tminus","HF E>5GeV w/ t<0", 75, 0, 75);

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

  TH1F *HBHE_TSdist_22_5	      = new TH1F("HBHE_TSdist_22_5" ,"HBHE: TS[n]>30fC,ieta=-22 iphi=5", 10, 0, 10);
  TH1F *HBHE_TSdist_30		      = new TH1F("HBHE_TSdist_30" ,"HBHE: TS[n]>30fC", 10, 0, 10);
  TH1F *HBHE_TSdist_50		      = new TH1F("HBHE_TSdist_50" ,"HBHE: TS[n]>50fC", 10, 0, 10);
  TH1F *HBHE_TSdist_100		      = new TH1F("HBHE_TSdist_100" ,"HBHE: TS[n]>100fC", 10, 0, 10);
  TH1F *HBHE_nTS_fired_30	      = new TH1F("HBHE_nTS_fired_30" ,"HBHE: # of TS with >30fC", 10, 0, 10);
  TH1F *HBHE_nTS_fired_50	      = new TH1F("HBHE_nTS_fired_50" ,"HBHE: # of TS with >50fC", 10, 0, 10);
  TH1F *HBHE_nTS_fired_100	      = new TH1F("HBHE_nTS_fired_100" ,"HBHE: # of TS with >100fC", 10, 0, 10);
  TH1F *HBHE_Energy_D1		      = new TH1F("HBHE_Energy_D1" ,"HBHE: E>5GeV Depth 1", 50, 0, 0);
  TH1F *HBHE_TSRatio_D1		      = new TH1F("HBHE_TSRatio_D1","HBHE: TS4>30fC  Depth 1", 30, 0,0);
  TH1F *HBHE_TSRatio_D2		      = new TH1F("HBHE_TSRatio_D2","HBHE: TS4>30fC  Depth 2", 30, 0,0);
  TH1F *HBHE_TSRatio_D3		      = new TH1F("HBHE_TSRatio_D3","HBHE: TS4>30fC  Depth 3", 30, 0,0);
  TH1F *HBHE_TSRatio_a		      = new TH1F("HBHE_TSRatio_a ","HBHEa: TS4>30fC", 30, 0,0);
  TH1F *HBHE_TSRatio_b		      = new TH1F("HBHE_TSRatio_b ","HBHEb: TS4>30fC", 30, 0,0);
  TH1F *HBHE_TSRatio_c		      = new TH1F("HBHE_TSRatio_c ","HBHEc: TS4>30fC", 30, 0,0);

  TH1F *HBHE_TSRatio_fC1_D1	      = new TH1F("HBHE_TSRatio_fC1_D1","HBHE: 30fC<TS4<100fC    Depth 1", 30, 0,0);
  TH1F *HBHE_TSRatio_fC2_D1	      = new TH1F("HBHE_TSRatio_fC2_D1","HBHE: 100fC<TS4<200fC   Depth 1", 30, 0,0);
  TH1F *HBHE_TSRatio_fC3_D1	      = new TH1F("HBHE_TSRatio_fC3_D1","HBHE: 200fC<TS4<600fC   Depth 1", 30, 0,0);
  TH1F *HBHE_TSRatio_fC4_D1	      = new TH1F("HBHE_TSRatio_fC4_D1","HBHE: 600fC<TS4<2000fC  Depth 1", 30, 0,0);

  TH1F *HBHE_TSRatio_fC1_D2	      = new TH1F("HBHE_TSRatio_fC1_D2","HBHE: 30fC<TS4<100fC    Depth 2", 30, 0,0);
  TH1F *HBHE_TSRatio_fC2_D2	      = new TH1F("HBHE_TSRatio_fC2_D2","HBHE: 100fC<TS4<200fC   Depth 2", 30, 0,0);
  TH1F *HBHE_TSRatio_fC3_D2	      = new TH1F("HBHE_TSRatio_fC3_D2","HBHE: 200fC<TS4<600fC   Depth 2", 30, 0,0);
  TH1F *HBHE_TSRatio_fC4_D2	      = new TH1F("HBHE_TSRatio_fC4_D2","HBHE: 600fC<TS4<2000fC  Depth 2", 30, 0,0);

  TH1F *HBHE_TSRatio_fC1_D3	      = new TH1F("HBHE_TSRatio_fC1_D3","HBHE: 30fC<TS4<100fC    Depth 3", 30, 0,0);
  TH1F *HBHE_TSRatio_fC2_D3	      = new TH1F("HBHE_TSRatio_fC2_D3","HBHE: 100fC<TS4<200fC   Depth 3", 30, 0,0);
  TH1F *HBHE_TSRatio_fC3_D3	      = new TH1F("HBHE_TSRatio_fC3_D3","HBHE: 200fC<TS4<600fC   Depth 3", 30, 0,0);
  TH1F *HBHE_TSRatio_fC4_D3	      = new TH1F("HBHE_TSRatio_fC4_D3","HBHE: 600fC<TS4<2000fC  Depth 3", 30, 0,0);

  TH2F *HBHE_TSRatioMap_Avg_D1           = new TH2F("HBHE_TSRatioMap_Avg_D1"       ,"HBHE: TS4>30fC Depth 1, Avg TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Rms_D1           = new TH2F("HBHE_TSRatioMap_Rms_D1"       ,"HBHE: TS4>30fC Depth 1, Rms TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_nEvt_D1          = new TH2F("HBHE_TSRatioMap_nEvt_D1"      ,"HBHE: TS4>30fC Depth 1 nEvt ", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Pull_D1          = new TH2F("HBHE_TSRatioMap_Pull_D1"      ,"HBHE: TS4>30fC Depth 1, Pull of ratio=|r-r#{_avg}}|/ (rms/sqrt{N})", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC1_D1       = new TH2F("HBHE_TSRatioMap_Avg_fC1_D1"   ,"HBHE: 30fC<TS4<100fC   , Avg TS5/TS4 Depth 1", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC2_D1       = new TH2F("HBHE_TSRatioMap_Avg_fC2_D1"   ,"HBHE: 100fC<TS4<200fC  , Avg TS5/TS4 Depth 1", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC3_D1       = new TH2F("HBHE_TSRatioMap_Avg_fC3_D1"   ,"HBHE: 200fC<TS4<600fC  , Avg TS5/TS4 Depth 1", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC4_D1       = new TH2F("HBHE_TSRatioMap_Avg_fC4_D1"   ,"HBHE: 600fC<TS4<2000fC , Avg TS5/TS4 Depth 1", 60, -30, 30, 74, 0, 74);

  TH2F *HBHE_TSRatioMap_Avg_D2         = new TH2F("HBHE_TSRatioMap_Avg_D2"       ,"HBHE: TS4>30fC Depth 2, Avg TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Rms_D2         = new TH2F("HBHE_TSRatioMap_Rms_D2"       ,"HBHE: TS4>30fC Depth 2, Rms TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_nEvt_D2         = new TH2F("HBHE_TSRatioMap_nEvt_D2"   ,"HBHE: TS4>30fC Depth 2 nEvt ", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Pull_D2         = new TH2F("HBHE_TSRatioMap_Pull_D2"   ,"HBHE: TS4>30fC Depth 2, Pull of ratio=|r-r#{_avg}}|/ (rms/sqrt{N})", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC1_D2      = new TH2F("HBHE_TSRatioMap_Avg_fC1_D2"  ,"HBHE: 30fC<TS4<100fC    , Avg TS5/TS4 Depth 2", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC2_D2      = new TH2F("HBHE_TSRatioMap_Avg_fC2_D2"  ,"HBHE: 100fC<TS4<200fC   , Avg TS5/TS4 Depth 2", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC3_D2      = new TH2F("HBHE_TSRatioMap_Avg_fC3_D2"  ,"HBHE: 200fC<TS4<600fC   , Avg TS5/TS4 Depth 2", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC4_D2      = new TH2F("HBHE_TSRatioMap_Avg_fC4_D2"  ,"HBHE: 600fC<TS4<2000fC  , Avg TS5/TS4 Depth 2", 60, -30, 30, 74, 0, 74);

  TH2F *HBHE_TSRatioMap_Avg_D3         = new TH2F("HBHE_TSRatioMap_Avg_D3"     ,"HBHE: TS4>30fC Depth 3, Avg TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Rms_D3         = new TH2F("HBHE_TSRatioMap_Rms_D3"     ,"HBHE: TS4>30fC Depth 3, Rms TS5/TS4", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_nEvt_D3           = new TH2F("HBHE_TSRatioMap_nEvt_D3"   ,"HBHE: TS4>30fC Depth 3 nEvt ", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Pull_D3         = new TH2F("HBHE_TSRatioMap_Pull_D3"   ,"HBHE: TS4>30fC Depth 3, Pull of ratio=|r-r#{_avg}}|/ (rms/sqrt{N})", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC1_D3      = new TH2F("HBHE_TSRatioMap_Avg_fC1_D3"  ,"HBHE:  30fC<TS4<100fC   , Avg TS5/TS4 Depth 3", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC2_D3      = new TH2F("HBHE_TSRatioMap_Avg_fC2_D3"  ,"HBHE:  100fC<TS4<200fC  , Avg TS5/TS4 Depth 3", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC3_D3      = new TH2F("HBHE_TSRatioMap_Avg_fC3_D3"  ,"HBHE:  200fC<TS4<600fC  , Avg TS5/TS4 Depth 3", 60, -30, 30, 74, 0, 74);
  TH2F *HBHE_TSRatioMap_Avg_fC4_D3      = new TH2F("HBHE_TSRatioMap_Avg_fC4_D3"  ,"HBHE:  600fC<TS4<2000fC , Avg TS5/TS4 Depth 3", 60, -30, 30, 74, 0, 74);

  float TS4=0, TS5=0, hbhe_energy=0;
  int   hbhe_depth=0, hbhe_ieta=0, hbhe_iphi=0;

  int  nTS_fired[3] ={0,0,0};

  for(int event=0; event<nentries ;event++) {
  chain.GetEntry(event);
  // nObj = total # of HBHE pulses in the current event
  nHBHEDigiSize = (*HBHEDigiIEta).size();  

    // Loop over all HBHE pulses in the current event to fill a TS Entry
    for(int iHBHEPulse=0 ;iHBHEPulse< nHBHEDigiSize;++iHBHEPulse){
      for(int i=0;i<3;i++){ nTS_fired[i]=0;}
      for (int n=0; n<10; ++n) {
	// Estimate the pedestal event by event
	if( (*HBHEDigiFC)[iHBHEPulse][n]>30 ){
		HBHE_TSdist_30->Fill(n);
		if( (*HBHEDigiIEta)[iHBHEPulse]== -22 && (*HBHEDigiIPhi)[iHBHEPulse] ==5){
			HBHE_TSdist_22_5->Fill(n);
		}
		nTS_fired[0]++;
		if( (*HBHEDigiFC)[iHBHEPulse][n]>50 ){
			HBHE_TSdist_50->Fill(n);
			nTS_fired[1]++;
			if( (*HBHEDigiFC)[iHBHEPulse][n]>100 ){
				HBHE_TSdist_100->Fill(n); 
				nTS_fired[2]++;
			}
		}
	}
      }
      HBHE_nTS_fired_30->Fill(nTS_fired[0]);	
      HBHE_nTS_fired_50->Fill(nTS_fired[1]);
      HBHE_nTS_fired_100->Fill(nTS_fired[2]);	
      TS4 = (*HBHEDigiFC)[iHBHEPulse][4];
      TS5 = (*HBHEDigiFC)[iHBHEPulse][5];
      hbhe_depth  = (*HBHEDigiDepth)[iHBHEPulse];
      hbhe_energy = (*HBHEDigiRecEnergy)[iHBHEPulse];
      hbhe_ieta = (*HBHEDigiIEta)[iHBHEPulse];
      hbhe_iphi = (*HBHEDigiIPhi)[iHBHEPulse];

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
    int nHFDigiSize = (*HFDigiRecEnergy).size();
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
    for(int iHFPulse=0 ; iHFPulse < nHFDigiSize ; ++iHFPulse){
       hf_depth  = (*HFDigiDepth)[iHFPulse];
       hf_ieta  = (*HFDigiIEta)[iHFPulse];
       hf_iphi  = (*HFDigiIPhi)[iHFPulse];
       hf_energy = (*HFDigiRecEnergy)[iHFPulse]; 
       hf_time   = (*HFDigiRecTime)[iHFPulse];
       TS0       = (*HFDigiFC)[iHFPulse][0]; 
       TS1       = (*HFDigiFC)[iHFPulse][1]; 
       TS2       = (*HFDigiFC)[iHFPulse][2]; 
       TS3       = (*HFDigiFC)[iHFPulse][3]; 
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
   if(event%500==0)std::cout<<"Number of event processed: "<<event<<std::endl;
  }
  HF_Time_fC->Scale(1./N_HF_TS);
  std::cout << "Read " << event << " events" << std::endl;

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

 //  Ratios0->Draw();
 //  Ratios0->GetYaxis()->SetRangeUser(0,Ratios0->GetBinContent(Ratios0->GetMaximumBin()));
 //  Ratios0->SetLineColor(4);
 //  Ratios1->Draw("SAMES");
 //  Ratios1->SetLineColor(9);
 //  Ratios2->Draw("SAMES");
 //  Ratios2->SetLineColor(8);
 //  Ratios3->Draw("SAMES");
 //  Ratios3->SetLineColor(2);
 //  Ratios4->Draw("SAMES");
 //  Ratios4->SetLineColor(34);

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
 
  sprintf(outputFile,"tsRatios_%i_%s_test.root",runNumber,stream.Data());
  TFile* fout = new TFile(outputFile,"RECREATE");
  // Writing HBHE histograms
  HBHE_TSdist_22_5->Write();
  HBHE_TSdist_30->Write();
  HBHE_TSdist_50->Write();
  HBHE_TSdist_100->Write();

  HBHE_nTS_fired_30->Write();
  HBHE_nTS_fired_50->Write();
  HBHE_nTS_fired_100->Write();

  HBHE_Energy_D1->Write();
  HBHE_TSRatio_D1->Write();
  HBHE_TSRatio_D2->Write();
  HBHE_TSRatio_D3->Write();

  HBHE_TSRatio_a->Write();
  HBHE_TSRatio_b->Write();
  HBHE_TSRatio_c->Write();

  HBHE_TSRatio_fC1_D1->Write();
  HBHE_TSRatio_fC2_D1->Write();
  HBHE_TSRatio_fC3_D1->Write();
  HBHE_TSRatio_fC4_D1->Write();

  HBHE_TSRatio_fC1_D2->Write();
  HBHE_TSRatio_fC2_D2->Write();
  HBHE_TSRatio_fC3_D2->Write();
  HBHE_TSRatio_fC4_D2->Write();

  HBHE_TSRatio_fC1_D3->Write();
  HBHE_TSRatio_fC2_D3->Write();
  HBHE_TSRatio_fC3_D3->Write();
  HBHE_TSRatio_fC4_D3->Write();

  HBHE_TSRatioMap_Avg_D1   ->Write();
  HBHE_TSRatioMap_Rms_D1   ->Write();
  HBHE_TSRatioMap_nEvt_D1   ->Write();
  HBHE_TSRatioMap_Pull_D1   ->Write();
  HBHE_TSRatioMap_Avg_fC1_D1->Write();
  HBHE_TSRatioMap_Avg_fC2_D1->Write();
  HBHE_TSRatioMap_Avg_fC3_D1->Write();
  HBHE_TSRatioMap_Avg_fC4_D1->Write();

  HBHE_TSRatioMap_Avg_D2   ->Write();
  HBHE_TSRatioMap_Rms_D2   ->Write();
  HBHE_TSRatioMap_nEvt_D2   ->Write();
  HBHE_TSRatioMap_Pull_D2   ->Write();
  HBHE_TSRatioMap_Avg_fC1_D2->Write();
  HBHE_TSRatioMap_Avg_fC2_D2->Write();
  HBHE_TSRatioMap_Avg_fC3_D2->Write();
  HBHE_TSRatioMap_Avg_fC4_D2->Write();

  HBHE_TSRatioMap_Avg_D3   ->Write();
  HBHE_TSRatioMap_Rms_D3   ->Write();
  HBHE_TSRatioMap_nEvt_D3   ->Write();
  HBHE_TSRatioMap_Pull_D3   ->Write();
  HBHE_TSRatioMap_Avg_fC1_D3->Write();
  HBHE_TSRatioMap_Avg_fC2_D3->Write();
  HBHE_TSRatioMap_Avg_fC3_D3->Write();
  HBHE_TSRatioMap_Avg_fC4_D3->Write();

  // Writing HF histograms
  HF_Time_D1->Write();
  HF_Time_D2->Write();
  HF_Time_TSWeight->Write();
  HF_Time_Ratio_D1->Write();
  HF_Time_Ratio_D2->Write();

  HF_TSRatio_D1->Write();
  HF_TSRatio_E1_D1->Write();
  HF_TSRatio_E2_D1->Write();
  HF_TSRatio_E3_D1->Write();

  HF_TSRatio_D2->Write();
  HF_TSRatio_E1_D2->Write();
  HF_TSRatio_E2_D2->Write();
  HF_TSRatio_E3_D2->Write();

  HF_TimeMap_TS0_D1     ->Write();  
  HF_TimeMap_TS0_D2     ->Write();  
  HF_TimeMap_TS2_D1     ->Write();  
  HF_TimeMap_TS2_D2     ->Write();  
  HF_TimeMap_TS0TS2_D1  ->Write();  
  HF_TimeMap_TS0TS2_D2  ->Write(); 
 
  HF_TSRatioMap_Double_D1   ->Write();
  HF_TSRatioMap_Double_D2   ->Write();

  HF_TSRatioMap_nEvt_D1   ->Write();
  HF_TSRatioMap_Avg_D1   ->Write();
  HF_TSRatioMap_Rms_D1   ->Write();
  HF_TSRatioMap_Avg_E1_D1   ->Write();
  HF_TSRatioMap_Avg_E2_D1   ->Write();
  HF_TSRatioMap_Avg_E3_D1   ->Write();
  HF_TSRatioMap_nEvt_D2   ->Write();
  HF_TSRatioMap_Avg_D2   ->Write();
  HF_TSRatioMap_Rms_D2   ->Write();
  HF_TSRatioMap_Avg_E1_D2   ->Write();
  HF_TSRatioMap_Avg_E2_D2   ->Write();
  HF_TSRatioMap_Avg_E3_D2   ->Write();

  HF_Time_fC->Write();
  HF_Energy_Tplus->Write();
  HF_Energy_Tminus->Write();
  fout->Close();
}

