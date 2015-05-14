#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"
#include "HFDigi.h"
#include "HODigi.h"
#include "RBXMap.h"
#include <fstream>

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

  tuple_tree -> fChain -> SetBranchStatus("HLTKey", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerNames", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerDecisions", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HLTInsideDatasetTriggerPrescales", kTRUE);

  tuple_tree -> fChain -> SetBranchStatus("run", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("bcn", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiAllFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiNomFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPedFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRCGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFiberIdleOffset", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSubdet", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPresamples", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiADC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiCapID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDV", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiER", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFiber", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFiberChan", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRaw", kTRUE);

  tuple_tree -> fChain -> SetBranchStatus("HFDigiEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiAllFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiNomFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPedFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRCGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiberIdleOffset", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPresamples", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiSize", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiADC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiCapID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDV", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiER", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiber", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiberChan", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRaw", kTRUE);
  
  tuple_tree -> fChain -> SetBranchStatus("HODigiEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiRecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiAllFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiNomFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiPedFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiRCGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiDepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiFiberIdleOffset", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiPresamples", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiSize", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiADC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiCapID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiDV", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiER", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiFiber", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiFiberChan", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HODigiRaw", kTRUE);

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------

  TH1F * h_triggers = makeTH1F("triggers", 11, -0.5, 10.5);
  TH2F * h_triggers_by_event = makeTH2F("triggers_by_event", n_events, -0.5, float(n_events) - 0.5, 11, -0.5, 10.5 );
  TH1F * h_sumE = makeTH1F("sumE", 10000, 0, 1e7);
  TH1F * h_sumE_low = makeTH1F("sumE_low", 1000, 0, 1e4);
  TH2F * h_bcn_vs_difference = makeTH2F( "bcn_vs_difference", 20, 200.5, 220.5, 100, -5., 5.);
  TH2F * h_ls_vs_difference = makeTH2F( "ls_vs_difference", 350, 550.5, 900.5, 100, -5., 5.);
  
  std::vector<std::vector<TH2F*> > h_adc ( n_events, std::vector<TH2F*> (5));
  std::vector<std::vector<TH2F*> > h_gev ( n_events, std::vector<TH2F*> (5));
  std::vector<std::vector<TH2F*> > h_time ( n_events, std::vector<TH2F*> (5));
  std::vector<TH2F*> h_hb_eta_vs_rhtime (n_events);
  std::vector<std::vector<TH2F*> > h_hb_eta_vs_rhtime_iphi (n_events, std::vector<TH2F*> (73));

  char hist_name[200];
  std::vector<TH2F*> h_occupancy_saturated(5);

  for (int i = 1; i<=4; ++i){
    sprintf(hist_name, "occupancy_saturated_Depth%d", i );
    h_occupancy_saturated[i] = makeTH2F(hist_name,  85, -42.5, 42.5, 72, 0.5, 72.5 );  
  }
  
  std::string bptx_trigger ("HLT_L1Tech_BPTXplus_OR_BPTXminus_v1");
  std::string eg20_trigger ("HLT_L1SingleEG20_v1");
  std::string eg5_trigger ("HLT_L1SingleEG5_v1");

  //--------------------------------------------------------------------------------
  // Maps
  //--------------------------------------------------------------------------------

  std::map <int, std::string> m_eventNumber_eventString_minusSplash;
  std::map <int, std::string> m_eventNumber_eventString_plusSplash;

  char eventChar[200];

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  char bin_label[200];
  int counter = 0;

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 100 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    for (int depth = 1; depth <= 4; ++depth){
      sprintf(hist_name, "ADC_Run%d_Event%d_Lumi%d_Depth%d", tuple_tree -> run, tuple_tree -> event, tuple_tree -> ls, depth );
      h_adc[i][depth] = makeTH2F ( hist_name , 85, -42.5, 42.5, 72, 0.5, 72.5 );  
      sprintf(hist_name, "GEV_Run%d_Event%d_Lumi%d_Depth%d", tuple_tree -> run, tuple_tree -> event, tuple_tree -> ls, depth );
      h_gev[i][depth] = makeTH2F ( hist_name , 85, -42.5, 42.5, 72, 0.5, 72.5 );   
      sprintf(hist_name, "Time_Run%d_Event%d_Lumi%d_Depth%d", tuple_tree -> run, tuple_tree -> event, tuple_tree -> ls, depth );
      h_time[i][depth] = makeTH2F ( hist_name , 85, -42.5, 42.5, 72, 0.5, 72.5 );   
    }

    for (int iphi = 1; iphi <= 72; ++iphi){
      sprintf(hist_name, "hb_eta_vs_rhtime_Run%d_Event%d_Lumi%d_iphi%d", tuple_tree -> run, tuple_tree -> event, tuple_tree -> ls , iphi);
      h_hb_eta_vs_rhtime_iphi[i][iphi] = makeTH2F( hist_name, 30, -1.3, 1.3, 500, -100, 100 );
    }

    //-----------------------------------------------------------------
    // Did the trigger fire?
    //-----------------------------------------------------------------

    getTriggers ( tuple_tree -> HLTKey, 			
                  tuple_tree -> HLTInsideDatasetTriggerNames, 	
                  tuple_tree -> HLTInsideDatasetTriggerDecisions,  
                  tuple_tree -> HLTInsideDatasetTriggerPrescales ) ; 
    
    bool bptx_trigger_fired = triggerFired(bptx_trigger.c_str());
    bool eg20_trigger_fired = triggerFired(eg20_trigger.c_str());
    bool eg5_trigger_fired = triggerFired(eg5_trigger.c_str());

    std::map<std::string, bool>::iterator it     = triggerDecisionMap_.begin();
    std::map<std::string, bool>::iterator it_end = triggerDecisionMap_.end();
    
    for (int iTrigger = 0; it != it_end; ++it, ++iTrigger){
      if ( it -> second ) h_triggers -> Fill ( iTrigger );
      if ( it -> second ) h_triggers_by_event -> Fill ( i, iTrigger );
    }
    int bin = h_triggers_by_event -> GetXaxis() -> FindBin(i);
    sprintf(bin_label, "%d:%d:%d", tuple_tree -> run, tuple_tree -> ls, tuple_tree -> event );
    h_triggers_by_event -> GetXaxis() -> SetBinLabel(bin, bin_label);
    
    //-----------------------------------------------------------------
    // Collections of HBHE, HF, HO digis
    //-----------------------------------------------------------------

    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    CollectionPtr hfDigis   (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
    CollectionPtr hoDigis   (new Collection(*tuple_tree, tuple_tree -> HODigiIEta -> size()));
    
    float sumE = 0.;


    float avg_time_minus = 0.;
    float avg_time_plus = 0.;
    int n_minus = 0;
    int n_plus = 0;

    bool good_hpd = true;

    int nHBHEDigis = hbheDigis -> GetSize();
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);
      int bin = h_adc[i][hbheDigi.depth()] -> FindBin( hbheDigi.ieta(), hbheDigi.iphi() );
      h_adc[i][hbheDigi.depth()] -> Fill ( hbheDigi.ieta(), hbheDigi.iphi(), hbheDigi.maxADC());
      h_gev[i][hbheDigi.depth()] -> Fill ( hbheDigi.ieta(), hbheDigi.iphi(), hbheDigi.energy());
      if ( hbheDigi.maxADC() > 0 && hbheDigi.maxADC() < 127 ) h_time[i][hbheDigi.depth()] -> SetBinContent(bin, hbheDigi.recHitTime());
      sumE += hbheDigi.energy();

      if ( hbheDigi.iphi() == 54 && hbheDigi.ieta() > 0 ) good_hpd = false;
      else good_hpd = true;
      
      if ( hbheDigi.maxADC() == 127 ) h_occupancy_saturated[hbheDigi.depth()] -> Fill ( hbheDigi.ieta(), hbheDigi.iphi() );
      if ( hbheDigi.subdet() == 1 && hbheDigi.depth() == 1 )
	h_hb_eta_vs_rhtime_iphi[i][hbheDigi.iphi()] -> Fill ( hbheDigi.eta(), hbheDigi.recHitTime());
    }

    int nHODigis = hoDigis -> GetSize();
    for (int iHODigi = 0; iHODigi < nHODigis; ++iHODigi){
      HODigi hoDigi = hoDigis -> GetConstituent<HODigi>(iHODigi);
      int bin = h_adc[i][hoDigi.depth()] -> FindBin( hoDigi.ieta(), hoDigi.iphi() );
      h_adc[i][hoDigi.depth()] -> SetBinContent(bin, hoDigi.maxADC());
      h_gev[i][hoDigi.depth()] -> SetBinContent(bin, hoDigi.energy());
      sumE += hoDigi.energy();
      if ( hoDigi.maxADC() > 10 ) h_time[i][hoDigi.depth()] -> SetBinContent(bin, hoDigi.recHitTime());
      if ( hoDigi.maxADC() == 127 ) h_occupancy_saturated[hoDigi.depth()] -> Fill ( hoDigi.ieta(), hoDigi.iphi() );
    }
    
    int nHFDigis = hfDigis -> GetSize();
    for (int iHFDigi = 0; iHFDigi < nHFDigis; ++iHFDigi){
      HFDigi hfDigi = hfDigis -> GetConstituent<HFDigi>(iHFDigi);
      int bin = h_adc[i][hfDigi.depth()] -> FindBin( hfDigi.ieta(), hfDigi.iphi() );
      h_adc[i][hfDigi.depth()] -> SetBinContent(bin, hfDigi.maxADC());
      h_gev[i][hfDigi.depth()] -> SetBinContent(bin, hfDigi.energy());
      sumE += hfDigi.energy();

      if ( hfDigi.ieta() < 0 ) {
	++n_minus;
	avg_time_minus += hfDigi.recHitTime();
      }
      else {
	++n_plus;
	avg_time_plus += hfDigi.recHitTime();
      }


      if ( hfDigi.maxADC() > 10 ) h_time[i][hfDigi.depth()] -> SetBinContent(bin, hfDigi.recHitTime());
      if ( hfDigi.maxADC() == 127 ) h_occupancy_saturated[hfDigi.depth()] -> Fill ( hfDigi.ieta(), hfDigi.iphi() );
    }

    h_sumE -> Fill ( sumE );
    h_sumE_low -> Fill ( sumE );

    avg_time_minus /= float(n_minus);
    avg_time_plus /= float(n_plus); 

    float difference = avg_time_minus - avg_time_plus;


    if ( sumE > 500. ){
      ++counter;

      h_bcn_vs_difference -> Fill ( tuple_tree -> bcn, difference );
      if ( tuple_tree -> bcn >= 207 && tuple_tree -> bcn <= 208 ) {

	sprintf(eventChar, "%d:%d:%d", tuple_tree -> run , tuple_tree -> ls , tuple_tree -> event );
	std::string eventString ( eventChar );
	
	h_ls_vs_difference -> Fill ( tuple_tree -> ls, difference );
	std::cout << eventString
		  << "\t, bcn = " << tuple_tree -> bcn
		  << "\t, bptx = " << bptx_trigger_fired 
		  << "\t, EG20 = " << eg20_trigger_fired 
		  << "\t, EG5 = " << eg5_trigger_fired
		  << "\t, sumE = " << sumE
		  << "\t, diff = " << difference;
	if ( avg_time_minus < avg_time_plus ) std::cout << "\t- --> +" << std::endl;
	else std::cout << "\t+ --> -" << std::endl;

	if ( difference > 0 ) m_eventNumber_eventString_plusSplash.insert(std::pair<int, std::string>(tuple_tree -> event, eventString));
	else m_eventNumber_eventString_minusSplash.insert(std::pair<int, std::string>(tuple_tree -> event, eventString));
      }
    }
  }


  std::map<std::string, bool>::iterator it     = triggerDecisionMap_.begin();
  std::map<std::string, bool>::iterator it_end = triggerDecisionMap_.end();
  
  for (int iTrigger = 0; it != it_end; ++it, ++iTrigger) {
    int bin = h_triggers -> FindBin ( iTrigger );
    h_triggers -> GetXaxis() -> SetBinLabel(bin, it -> first.c_str() );
    bin = h_triggers_by_event -> GetYaxis() -> FindBin( iTrigger );
    h_triggers_by_event -> GetYaxis() -> SetBinLabel(bin, it -> first.c_str() );
  }

  
  ofstream minus_file, plus_file;
  minus_file.open ("minus_file.txt");
  plus_file.open ("plus_file.txt");

  std::map <int, std::string>::iterator it_minusSplash     = m_eventNumber_eventString_minusSplash.begin();
  std::map <int, std::string>::iterator it_minusSplash_end = m_eventNumber_eventString_minusSplash.end();
  for (; it_minusSplash != it_minusSplash_end; ++it_minusSplash) minus_file << it_minusSplash -> second << "\n";


  std::map <int, std::string>::iterator it_plusSplash     = m_eventNumber_eventString_plusSplash.begin();
  std::map <int, std::string>::iterator it_plusSplash_end = m_eventNumber_eventString_plusSplash.end();
  for (; it_plusSplash != it_plusSplash_end; ++it_plusSplash) plus_file << it_plusSplash -> second << "\n";

  minus_file.close();
  plus_file.close();

  
}
