import ROOT as r
from array import array

phases = [ "m4", "m2", "m1", "0", "p1", "p2" ]

d_histName_phaseData = {}

out_file = r.TFile ("graphs.root","RECREATE")

shift_hist_depth1 = r.TH2F("shift_depth1", "shift_depth1", 85, -42.5, 42.5, 72, 0.5, 72.5 )
shift_hist_depth2 = r.TH2F("shift_depth2", "shift_depth2", 85, -42.5, 42.5, 72, 0.5, 72.5 )

for phase in phases:
    
    phase_value = float(phase[-1])
    if "m" in phase: phase_value *= (-1.0)

    # if phase == "m2" : phase_value = -1.
    # if phase == "m1" : phase_value = -2.

    file_name = "output_" + phase + ".root"
    file = r.TFile ( file_name )
    
    for key in file.GetListOfKeys():
        
        hist_name = key.GetName()
        hist = file.Get(hist_name)
        
        if hist_name not in d_histName_phaseData.keys():
            d_histName_phaseData[hist_name] = {}
        
        d_histName_phaseData[hist_name][phase_value] = [ hist.GetMean(), hist.GetRMS() ]

for histName in d_histName_phaseData.keys():
    phases = sorted(d_histName_phaseData[histName].keys())
    e_phases = []
    means = []
    mean_errors = []
    best_phase = -5
    best_diff = 999.;

    for phase in phases:
        means.append       ( d_histName_phaseData[histName][phase][0])
        mean_errors.append ( d_histName_phaseData[histName][phase][1])
        e_phases.append ( 0. )
        if abs ( d_histName_phaseData[histName][phase][0] - 1.5 ) < best_diff:
            best_diff = abs(d_histName_phaseData[histName][phase][0] - 1.5)
            best_phase = phase

    mean_3 = (d_histName_phaseData[histName][-4.][0] + 
              d_histName_phaseData[histName][-2.][0] ) / 2.
    
    if abs ( mean_3 - 1.5 ) < best_diff: best_phase = -3
        



    n  = len (phases)
    x  = array("d", phases)
    ex = array("d", e_phases)
    y  = array("d", means )
    ey = array("d", mean_errors )

    graph = r.TGraphErrors ( n, x, y, ex, ey )
    out_file.cd()
    graph.Write(histName)

    f = r.TF1("func", "pol1(0)", -4, 2)
    graph.Fit("func")
    b = f.GetParameter(0)
    m = f.GetParameter(1)
    jitter = (1.5 - b) / m
    
    ieta = int(histName.split("_")[1])
    iphi = int(histName.split("_")[2])
    depth = int(histName.split("_")[3])

    if depth == 1: shift_hist_depth1.Fill ( ieta, iphi, best_phase )
    if depth == 2: shift_hist_depth2.Fill ( ieta, iphi, best_phase )
    

out_file.cd()
shift_hist_depth1.Write()
shift_hist_depth2.Write()    
