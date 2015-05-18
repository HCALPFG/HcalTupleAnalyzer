import ROOT as r
import copy

r.gStyle.SetOptStat(0)
r.gStyle.SetOptTitle(0)

outFileName = "~/www/hcal/ExpressCosmics_EMapUpdated_237068/HcalRecHit.pdf"

variables = [
    "ho_cosmic_timing",
    "hbhe_cosmic_timing",
    "ho_cosmic_energy",
    "hbhe_cosmic_energy",
    "ho_cosmic_recHitTiming",
    "hbhe_cosmic_recHitTiming",
]

triggers = [
    "ho_fired",
    "dt_fired",
    "hodt_fired"
]

d_variable_title = {
    "ho_cosmic_timing"  : "Timing of HO DigiHits with muon hit",
    "hbhe_cosmic_timing": "Timing of HBHE DigiHits with muon hit",
    "ho_cosmic_energy"  : "Energy of HO RecHits with muon hit",
    "hbhe_cosmic_energy": "Energy of HBHE RecHits with muon hit",
    "ho_cosmic_recHitTiming": "RecHit Timing of HO RecHits with muon hit",
    "hbhe_cosmic_recHitTiming": "RecHit Timing of HBHE RecHits with muon hit",
}

d_variable_xaxisTitle = {
    "ho_cosmic_timing"  : "HO DigiHit timing [25 ns]",
    "hbhe_cosmic_timing": "HBHE DigiHit timing [25 ns]",
    "ho_cosmic_energy"  : "HO RecHits energy [GeV]",
    "hbhe_cosmic_energy": "HBHE RecHits energy [GeV]",
    "ho_cosmic_recHitTiming": "HO RecHit timing [25 ns]",
    "hbhe_cosmic_recHitTiming": "HBHE RecHit timing [25 ns]",
}

yaxisTitle = "A.U. [unit-normalized]"

hcal_file = r.TFile("output_ECR_237068.root");
dt_file   = r.TFile("output_ECR_237068.root");

canvas = r.TCanvas();
canvas.Print(outFileName+"[")

for variable in variables:
    
    save_name = variable + ".pdf"

    ho_fired_hist_name   = variable + "_hoFired"
    dt_fired_hist_name   = variable + "_dtFired"
    hodt_fired_hist_name = variable + "_hodtFired"

    ho_fired_hist   = hcal_file.Get(ho_fired_hist_name)
    dt_fired_hist   = dt_file  .Get(dt_fired_hist_name)
    hodt_fired_hist = hcal_file.Get(hodt_fired_hist_name)

    print hodt_fired_hist_name
    
    dtSolo_fired_hist = copy.deepcopy ( dt_fired_hist )
    dtSolo_fired_hist.Add( hodt_fired_hist )

    hoSolo_fired_hist = copy.deepcopy ( ho_fired_hist )
    dtSolo_fired_hist.Add( hodt_fired_hist )
    
    ho_fired_hist.SetFillColor(r.kBlue)
    dt_fired_hist.SetFillColor(r.kRed)
    hodt_fired_hist.SetFillColor(r.kViolet)
    dtSolo_fired_hist.SetFillColor(r.kGreen )
    hoSolo_fired_hist.SetFillColor(r.kOrange) 

    ho_fired_hist.SetLineColor(r.kBlue)
    dt_fired_hist.SetLineColor(r.kRed)
    hodt_fired_hist.SetLineColor(r.kViolet)
    dtSolo_fired_hist.SetLineColor(r.kGreen )
    hoSolo_fired_hist.SetLineColor(r.kOrange )

    ho_fired_hist.SetFillStyle(3004)
    dt_fired_hist.SetFillStyle(3005)
    hodt_fired_hist.SetFillStyle(3006)
    dtSolo_fired_hist.SetFillStyle(3006)
    hoSolo_fired_hist.SetFillStyle(3006)

    i_ho_fired_hist     = ho_fired_hist    .Integral ( 0, ho_fired_hist    .GetNbinsX() + 1 )
    i_dt_fired_hist     = dt_fired_hist    .Integral ( 0, dt_fired_hist    .GetNbinsX() + 1 )
    i_hodt_fired_hist   = hodt_fired_hist  .Integral ( 0, hodt_fired_hist  .GetNbinsX() + 1 )
    i_dtSolo_fired_hist = dtSolo_fired_hist.Integral ( 0, dtSolo_fired_hist.GetNbinsX() + 1 )
    i_hoSolo_fired_hist = hoSolo_fired_hist.Integral ( 0, hoSolo_fired_hist.GetNbinsX() + 1 )

    ho_fired_hist.Sumw2()
    dt_fired_hist.Sumw2()
    hodt_fired_hist.Sumw2()
    dtSolo_fired_hist.Sumw2()
    hoSolo_fired_hist.Sumw2()

    if i_ho_fired_hist > 0:
        ho_fired_hist.Scale ( 1.0 / i_ho_fired_hist )

    if i_dt_fired_hist > 0:
        dt_fired_hist.Scale ( 1.0 / i_dt_fired_hist )

    if i_hodt_fired_hist > 0:
        hodt_fired_hist.Scale ( 1.0 / i_hodt_fired_hist )

    if i_dtSolo_fired_hist > 0:
        dtSolo_fired_hist.Scale ( 1.0 / i_dtSolo_fired_hist )

    if i_hoSolo_fired_hist > 0:
        hoSolo_fired_hist.Scale ( 1.0 / i_hoSolo_fired_hist )

    my_max = max ( ho_fired_hist.GetMaximum(), dt_fired_hist.GetMaximum())
    my_max = max ( my_max, hodt_fired_hist.GetMaximum() )
    my_max = max ( my_max, dtSolo_fired_hist.GetMaximum())
    my_max = max ( my_max, hoSolo_fired_hist.GetMaximum())
    my_max *= 1.2
    
    ho_fired_hist.SetMaximum(my_max)
    dt_fired_hist.SetMaximum(my_max)
    hodt_fired_hist.SetMaximum(my_max)
    dtSolo_fired_hist.SetMaximum(my_max)
    hoSolo_fired_hist.SetMaximum(my_max)
    
    ho_fired_hist.GetYaxis().SetTitleOffset(1.2)
    ho_fired_hist.GetXaxis().SetTitle(d_variable_xaxisTitle[variable])
    ho_fired_hist.GetYaxis().SetTitle(yaxisTitle)

    ho_fired_hist.Draw("HIST E")
    dt_fired_hist.Draw("SAME HIST E")
    hodt_fired_hist.Draw("SAME HIST E")
    # dtSolo_fired_hist.Draw("SAME HIST E")
    # hoSolo_fired_hist.Draw("SAME HIST E")

    canvas.Update()
    xmin = canvas.GetUxmin();
    xmax = canvas.GetUxmax();
    ymin = canvas.GetUymin();
    ymax = canvas.GetUymax();
    ylength = ymax - ymin

    tex = r.TLatex()
    tex.SetTextSize(0.033)
    tex.SetTextFont(42)
    tex.SetTextColor(r.kBlack)
    tex.DrawLatex(xmin, ymin + 1.05 * ylength,d_variable_title[variable] )

    l = r.TLegend(0.6, 0.6, 0.85, 0.85);
    l.SetFillColor(r.kWhite);
    l.SetBorderSize(1);
    l.SetShadowColor(10);
    l.SetMargin(0.2);
    l.SetTextFont(42);
    l.AddEntry(ho_fired_hist, "HO: yes, DT: NO", "lf")
    l.AddEntry(dt_fired_hist, "HO = NO, DT = yes", "lf")
    l.AddEntry(hodt_fired_hist, "HO = yes, DT = yes", "lf")
    # l.AddEntry(dtSolo_fired_hist, "DT = yes", "lf")
    # l.AddEntry(hoSolo_fired_hist, "HO = yes", "lf")
    l.Draw();

    # canvas.SaveAs(variable + ".pdf") 
    canvas.Print(outFileName)

canvas.Print(outFileName+"]")
