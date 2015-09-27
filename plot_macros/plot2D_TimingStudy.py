import ROOT as r
import copy

r.gStyle.SetOptStat(0)
# r.gStyle.SetOptTitle(0)

Title = "Super Pointing Muon Dataset"
outFileName = "~/www/hcal/20150420_SuperPointingMuon/Timing2DPlots.pdf"


# detectors = ["ho","hbhe"]
detectors = ["hbhe"]
# detectors = ["ho"]

variables = [
		# "cosmic_iphi_vs_recHitTiming",	
	    "cosmic_occupancy",
	    "cosmic_phi_vs_recHitTiming_depth1",
        # "cosmic_occupancy_noEnergy",
        # "cosmic_timing_recTiming",
        # "cosmic_timing_recTiming_noEnergy",
        # "cosmic_timing_recTiming_withEnergyCut",
        # "cosmic_timestamp_fc",
        # "cosmic_timestamp_fc_zeroTiming",
        # "cosmic_timestamp_fc_nineTiming",

		]

triggers = {
    # "hoFired": "Only HO Fired",
    "dtFired": "Only DT Fired",
    # "hodtFired": "Both Fired"
    }

titles = {
    "cosmic_iphi_vs_recHitTiming": " ; ".join([Title,"i#phi","RecHitTiming [ns]"]),
    "cosmic_occupancy": "Occupancy ; i#eta ; i#phi ",
    "cosmic_occupancy_noEnergy": "Occupancy from Digi with Energy < 0.2 ; i#eta ; i#phi ",    
    "cosmic_timing_recTiming": "; DigiTiming ; RecHitTiming [ns] ",
    "cosmic_timing_recTiming_noEnergy": " Digi with Energy < 0.2 ; DigiTiming ; RecHitTiming [ns] ",
    "cosmic_timing_recTiming_withEnergyCut":" Digi with Energy > 0.2 ; DigiTiming ; RecHitTiming [ns] ",
    "cosmic_timestamp_fc": " ; Timestamp ; Femtocoulomb ",
    "cosmic_timestamp_fc_zeroTiming": " Timing < 0.5 ; Timestamp ; Femtocoulomb ",
    "cosmic_timestamp_fc_nineTiming": " Timing > 9.0 ; Timestamp ; Femtocoulomb ",
    "cosmic_phi_vs_recHitTiming_depth1": " Depth 1 ; #phi  ; RecHitTiming [ns]",

}

hcal_file = r.TFile("output/20150420_SuperPointingMuon.root")

canvas = r.TCanvas();
canvas.Print(outFileName+"[")

for detector in detectors:
    for variable in variables:
        for trigger,label in triggers.iteritems():

            histName = "_".join([detector,variable,trigger])
            hist = hcal_file.Get(histName)

            print histName
            # hist.SetStats(0)
            hist.SetTitle(detector.upper()+" RecHits, "+label+", "+titles[variable])
            # print detector+" "+titles[variable]

            hist.Draw("colz")

            # canvas.SaveAs(variable + ".pdf") 
            canvas.Print(outFileName)

canvas.Print(outFileName+"]")
