#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"
#include "HcalTP.h"

void analysisClass::loop(){

  //--------------------------------------------------------------------------------
  // Configurables
  //--------------------------------------------------------------------------------
  const int nSample = 10;
  const double min_charge = 20.;
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * utca_tree = getTree<HcalTupleTree>("tuple_tree","utca_file");
  HcalTupleTree * vme_tree = getTree<HcalTupleTree>("tuple_tree","vme_file");
 
  //--------------------------------------------------------------------------------
  // Check number of events
  //--------------------------------------------------------------------------------

  int n_utca_events = utca_tree -> fChain -> GetEntries();
  std::cout << "n events in utca tree = " << n_utca_events << std::endl;
  int n_vme_events = vme_tree -> fChain -> GetEntries();
  std::cout << "n events in vme tree = " << n_vme_events << std::endl;

  if (n_utca_events != n_vme_events){
    std::cout << "Number of events in utca trees not equal to number of vme trees" << std::endl;
    return;
  };

  int n_events = n_utca_events;
  std::map<std::string,HcalTupleTree*> treeMap;
  treeMap["utca"] = utca_tree;
  treeMap["vme"] = vme_tree;

  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------

  std::map<std::string,HcalTupleTree*>::iterator it = treeMap.begin();
  for (; it != treeMap.end(); ++it){
  it -> second -> fChain -> SetBranchStatus("*"                 , kFALSE);
  it -> second -> fChain -> SetBranchStatus("run"               , kTRUE);
  it -> second -> fChain -> SetBranchStatus("event"             , kTRUE);
  it -> second -> fChain -> SetBranchStatus("ls"                , kTRUE);
  it -> second -> fChain -> SetBranchStatus("HBHEDigiFC"        , kTRUE);
  it -> second -> fChain -> SetBranchStatus("HBHEDigiADC"       , kTRUE);
  it -> second -> fChain -> SetBranchStatus("HBHEDigiIEta"      , kTRUE);
  it -> second -> fChain -> SetBranchStatus("HBHEDigiIPhi"      , kTRUE);
  it -> second -> fChain -> SetBranchStatus("HBHEDigiDepth"     , kTRUE);
  it -> second -> fChain -> SetBranchStatus("HBHEDigiSize"      , kTRUE);
  it -> second -> fChain -> SetBranchStatus("HcalTriggerPrimitiveCompressedEtSOI",kTRUE);
  it -> second -> fChain -> SetBranchStatus("HcalTriggerPrimitiveIEta",kTRUE);
  it -> second -> fChain -> SetBranchStatus("HcalTriggerPrimitiveIPhi",kTRUE);
  };

  //--------------------------------------------------------------------------------
  // Basic Histograms
  //--------------------------------------------------------------------------------
  
  char histName[100];
  char titleName[100];

  TH2F * h_utcaOccp = makeTH2F("h_utcaOccp",81,-40.5,40.5,72,0.5,72.5);
  h_utcaOccp -> SetTitle(" ; uTCA i#eta ; uTCA i#phi ");

  TH2F * h_vmeOccp = makeTH2F("h_vmeOccp",81,-40.5,40.5,72,0.5,72.5);
  h_vmeOccp -> SetTitle(" ; VME i#eta ; VME i#phi ");

  TH2F * h_fcTotal = makeTH2F("h_fcTotal",100,0.,200.,100.,0.,200.);
  h_fcTotal -> SetTitle(" ; uTCA Total fC ; VME Total fC ");

  std::map <int,TH2F*> h_fc;
  std::map <int,TH1F*> h_uTCAfC;
  std::map <int,TH1F*> h_vmefC;

  for (int ifc = 0; ifc != nSample; ifc++){
    sprintf(histName,"h_fc%d",ifc);
    h_fc[ifc] = makeTH2F(histName,50,0.,50.,50,0.,50.);
    sprintf(titleName," ; uTCA fC at TS %d ; VME fC at TS %d ",ifc,ifc);
    h_fc[ifc] -> SetTitle(titleName);

    sprintf(histName,"h_uTCAfc%d",ifc);
    h_uTCAfC[ifc] = makeTH1F(histName,50,0.,50.);
    sprintf(titleName," ; uTCA fC at TS %d ; ",ifc);
    h_uTCAfC[ifc] -> SetTitle(titleName);
    
    sprintf(histName,"h_vmefc%d",ifc);
    h_vmefC[ifc] = makeTH1F(histName,50,0.,50.);
    sprintf(titleName," ; vme fC at TS %d ; ",ifc);
    h_vmefC[ifc] -> SetTitle(titleName);
  };

  TH2F * h_adcTotal = makeTH2F("h_adcTotal",201,-0.5,200.5,201,-0.5,200.5);
  h_adcTotal -> SetTitle(" ; uTCA Total ADC ; VME Total ADC ");

  TH2F * h_tpEt = makeTH2F("h_tpEt",50,0.,100.,50,0.,100.);
  h_tpEt -> SetTitle(" ; uTCA TP ET ; VME TP ET");

  //--------------------------------------------------------------------------------
  // Custom Histograms
  //--------------------------------------------------------------------------------
  TH2F * h_utcaOccp_cut = makeTH2F("h_utcaOccp_cut",81,-40.5,40.5,72,0.5,72.5);
  h_utcaOccp_cut -> SetTitle("Cut ; uTCA i#eta ; uTCA i#phi ");

  TH2F * h_vmeOccp_cut = makeTH2F("h_vmeOccp_cut",81,-40.5,40.5,72,0.5,72.5);
  h_vmeOccp_cut -> SetTitle("Cut ; VME i#eta ; VME i#phi ");


  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  for (int i = 0; i < n_events; ++i){
    
    utca_tree -> GetEntry(i);
    vme_tree -> GetEntry(i);

    if ( (i + 1) % 100 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    // HBHE Digi
    CollectionPtr utcaDigis (new Collection(*utca_tree, utca_tree -> HBHEDigiIEta -> size()));
    CollectionPtr vmeDigis (new Collection(*vme_tree, vme_tree -> HBHEDigiIEta -> size()));
    
    int n_utcaDigis = utcaDigis -> GetSize();
    int n_vmeDigis = vmeDigis -> GetSize();

    //--------------------------------------------------------------------------------
    // uTCA Digis
    //--------------------------------------------------------------------------------

    for (int i_utcaDigis = 0; i_utcaDigis < n_utcaDigis; i_utcaDigis++){
      HBHEDigi utcaDigi = utcaDigis -> GetConstituent<HBHEDigi>(i_utcaDigis);
      h_utcaOccp -> Fill( utcaDigi.ieta() , utcaDigi.iphi() );

      if ( utcaDigi.fc(4) + utcaDigi.fc(5) > min_charge){
	h_utcaOccp_cut -> Fill( utcaDigi.ieta() , utcaDigi.iphi() );
      };

      for (int ifc = 0; ifc != nSample; ifc++){
        h_uTCAfC[ifc] -> Fill( utcaDigi.fc(ifc) ); 
      };
    };

    //--------------------------------------------------------------------------------
    // VME Digis
    //--------------------------------------------------------------------------------

    for (int i_vmeDigis = 0; i_vmeDigis < n_vmeDigis; i_vmeDigis++){
      HBHEDigi vmeDigi = vmeDigis -> GetConstituent<HBHEDigi>(i_vmeDigis);
      h_vmeOccp -> Fill( vmeDigi.ieta() , vmeDigi.iphi() );

      if ( vmeDigi.fc(4) + vmeDigi.fc(5) > min_charge){
	h_vmeOccp_cut -> Fill( vmeDigi.ieta() , vmeDigi.iphi() );
      };

      for (int ifc = 0; ifc != nSample; ifc++){
        h_vmefC[ifc] -> Fill( vmeDigi.fc(ifc) ); 
      };
    };

    //--------------------------------------------------------------------------------
    // Matching uTCA and VME Digis
    //--------------------------------------------------------------------------------

    for (int i_utcaDigis = 0; i_utcaDigis < n_utcaDigis; i_utcaDigis++){

      HBHEDigi utcaDigi = utcaDigis -> GetConstituent<HBHEDigi>(i_utcaDigis);

      for (int i_vmeDigis = 0; i_vmeDigis < n_vmeDigis; i_vmeDigis++){

        HBHEDigi vmeDigi = vmeDigis -> GetConstituent<HBHEDigi>(i_vmeDigis);

	if ( ( utcaDigi.ieta() != vmeDigi.ieta() ) || ( utcaDigi.iphi() != vmeDigi.iphi() ) || ( utcaDigi.depth() != vmeDigi.depth() ) ) continue;
        
        h_fcTotal -> Fill( utcaDigi.fcTotal() , vmeDigi.fcTotal() );
	h_adcTotal -> Fill( utcaDigi.adcTotal() , vmeDigi.adcTotal() );

        for (int ifc = 0; ifc != nSample; ifc++){
          h_fc[ifc] -> Fill( utcaDigi.fc(ifc) , vmeDigi.fc(ifc) ); 
        };
      };
    };

    //--------------------------------------------------------------------------------
    // TPs
    //--------------------------------------------------------------------------------

    CollectionPtr utcaTPs (new Collection(*utca_tree, utca_tree -> HcalTriggerPrimitiveIEta -> size()));
    CollectionPtr vmeTPs (new Collection(*vme_tree, vme_tree -> HcalTriggerPrimitiveIEta -> size()));

    int n_uTCATPs = utcaTPs -> GetSize();
    int n_vmeTPs = vmeTPs -> GetSize();

    for (int i_uTCATP = 0; i_uTCATP < n_uTCATPs; i_uTCATP++){
      HcalTP utcaTP = utcaTPs -> GetConstituent<HcalTP>(i_uTCATP);

      for (int i_vmeTP = 0; i_vmeTP < n_vmeTPs; i_vmeTP++){
        HcalTP vmeTP = vmeTPs -> GetConstituent<HcalTP>(i_vmeTP);
        
        if ( ( utcaTP.ieta() != vmeTP.ieta() ) || ( utcaTP.iphi() != vmeTP.iphi() )  ) continue;

	h_tpEt -> Fill( utcaTP.Et() , vmeTP.Et() );
		
      };
    };

  };
}
