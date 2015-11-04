#include "HcalTupleTree.h"
#include "analysisClass.h"
#include "HFDigi.h"
#include <map>

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
}

void reverseHash ( const int & hash,
		   int & ieta,
		   int & iphi,
		   int & depth ){
  int tmp_hash = hash;
  ieta = (hash % 100) - 41;
  iphi = (hash / 100) % 100;
  depth = (hash / 10000);
}
	      

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
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFC"        , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDepth"     , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIEta"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIPhi"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiSize"      , kTRUE);
  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------

  const double min_charge12 = 50.;

  const int ndelays = 6;
  double mean_charge12[2][ndelays];
  double mean_charge12_err[2][ndelays];
  double delay[2][ndelays] = { {0,1,2,3,4,-1}, {0,0,0,0,0,0} };
  //double delay[ndelays] = {0,1,2,3,4,-1};
  
  for(int iloop=0; iloop<ndelays; iloop++){

    int hash; 
    int nHFDigis;
    double timing12 = 0.;
    double charge12 = 0.;
    char hist_name[200];
  
    std::map<int, TH1F*> map_hash_timing12;
    std::map<int, TH1F*>::iterator map_it;

    for (int i = 0; i < n_events; ++i){    
      tuple_tree -> GetEntry(i);

      //Progress Meter
      if (isatty(1)) {
	if(((i+1)%10000)==0){
	  printf("\r[HF Timing] Event: %i / %i (%i%%)",i,n_events,(int)((float)i/(float)n_events*100));
	  fflush(stdout);
	}
	if(i==(n_events-1)) printf("\n");
      }

      if(iloop==0&&!(tuple_tree->run==250897&&tuple_tree->ls<=64&&tuple_tree->ls>=11)) continue; //5050
      if(iloop==1&&!(tuple_tree->run==250897&&tuple_tree->ls<=132&&tuple_tree->ls>=72)) continue; //p1
      if(iloop==2&&!(tuple_tree->run==250897&&tuple_tree->ls<=187&&tuple_tree->ls>=140)) continue; //p2
      if(iloop==3&&!(tuple_tree->run==250897&&tuple_tree->ls<=230&&tuple_tree->ls>=195)) continue; //p3
      if(iloop==4&&!(tuple_tree->run==250902&&tuple_tree->ls<=40&&tuple_tree->ls>=1)) continue; //p4
      if(iloop==5&&!(tuple_tree->run==250902&&tuple_tree->ls<=103&&tuple_tree->ls>=73)) continue; //m1

      CollectionPtr hfDigis (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
    
      nHFDigis = hfDigis -> GetSize();

      for (int iHFDigi = 0; iHFDigi < nHFDigis; ++iHFDigi){
	HFDigi hfDigi = hfDigis -> GetConstituent<HFDigi>(iHFDigi);
      
	hash = getHash ( hfDigi.ieta(), hfDigi.iphi(), hfDigi.depth());
	charge12 = hfDigi.charge12();
	timing12 = hfDigi.time12();
	map_it = map_hash_timing12.find(hash);
      
	if ( map_hash_timing12.find(hash) == map_hash_timing12.end() ){
	  if(hfDigi.ieta()==41)	sprintf(hist_name, "HF_p%d_%d_%d_%d", hfDigi.ieta(), hfDigi.iphi(), hfDigi.depth(), iloop);
	  if(hfDigi.ieta()==-41) sprintf(hist_name, "HF_m%d_%d_%d_%d", abs(hfDigi.ieta()), hfDigi.iphi(), hfDigi.depth(), iloop);
	  map_hash_timing12.insert(std::pair<int, TH1F*>(hash, makeTH1F(hist_name, 20, 0.0, 1)));
	}
      
	if(charge12 > min_charge12)
	  map_hash_timing12[hash]->Fill(timing12);
      
      } // Digis loop
    } // Events loop

    mean_charge12[0][iloop] = map_hash_timing12[getHash(41,3,2)]->GetMean(); 
    mean_charge12_err[0][iloop] = map_hash_timing12[getHash(41,3,2)]->GetMeanError(); 

    mean_charge12[1][iloop] = map_hash_timing12[getHash(-41,3,2)]->GetMean(); 
    mean_charge12_err[1][iloop] = map_hash_timing12[getHash(-41,3,2)]->GetMeanError(); 

  } // Delay loop (iloop)
  
  TGraphErrors *h_curve5050p = makeTGraphErrors(ndelays,delay[0],mean_charge12[0], delay[1], mean_charge12_err[0]);
  h_curve5050p->SetName("curve5050p");
  h_curve5050p->SetMarkerStyle(20);
  h_curve5050p->SetTitle("iEta=41, iPhi=3, Depth=2");
  h_curve5050p->GetXaxis()->SetLabelSize(0.0425);
  h_curve5050p->GetXaxis()->SetTitle("Timing Offset [ns]");
  h_curve5050p->GetXaxis()->SetTitleOffset(1.15);
  h_curve5050p->GetXaxis()->SetTitleSize(0.0425);
  h_curve5050p->GetYaxis()->SetLabelSize(0.0425);
  h_curve5050p->GetYaxis()->SetTitle("<Q2/(Q1+Q2)>");
  h_curve5050p->GetYaxis()->SetTitleOffset(1.15);
  h_curve5050p->GetYaxis()->SetTitleSize(0.0425);

  TGraphErrors *h_curve5050m = makeTGraphErrors(ndelays,delay[0],mean_charge12[1], delay[1], mean_charge12_err[1]);
  h_curve5050m->SetName("curve5050m");
  h_curve5050m->SetMarkerStyle(20);
  h_curve5050m->SetTitle("iEta=-41, iPhi=3, Depth=2");
  h_curve5050p->GetXaxis()->SetLabelSize(0.0425);
  h_curve5050p->GetXaxis()->SetTitle("Timing Offset [ns]");
  h_curve5050p->GetXaxis()->SetTitleOffset(1.15);
  h_curve5050p->GetXaxis()->SetTitleSize(0.0425);
  h_curve5050p->GetYaxis()->SetLabelSize(0.0425);
  h_curve5050p->GetYaxis()->SetTitle("<Q2/(Q1+Q2)>");
  h_curve5050p->GetYaxis()->SetTitleOffset(1.15);
  h_curve5050p->GetYaxis()->SetTitleSize(0.0425);
}
