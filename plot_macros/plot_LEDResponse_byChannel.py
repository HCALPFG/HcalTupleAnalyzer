import ROOT as r
import sys

old = r.gStyle.GetOptStat()
r.gStyle.SetOptStat(0)
r.gStyle.SetOptTitle(0)

in_file = r.TFile("Run228119.root");

keys = in_file.GetListOfKeys()

response_hist_mean = r.TH2F("response_hist_mean", "response_hist_mean", 31, -15.5, 15.5, 72, 0.5, 72.5 );
response_hist_rms  = r.TH2F("response_hist_rms" , "response_hist_rms" , 31, -15.5, 15.5, 72, 0.5, 72.5 );
response_hist_2D   = r.TH2F("response_hist_2D", "response_hist_2D", 100, 0, 3500, 100, 0, 150 )

response_hist_mean.GetXaxis().SetTitle("ieta")
response_hist_mean.GetYaxis().SetTitle("iphi")
response_hist_rms.GetXaxis().SetTitle("ieta")
response_hist_rms.GetYaxis().SetTitle("iphi")
response_hist_2D.GetXaxis().SetTitle("Mean of charge integrated over all TS [fC]")
response_hist_2D.GetYaxis().SetTitle("RMS of charge integrated over all TS [fC]")

save_hists = []

for key in keys:
    name = key.GetName()
    if "HO_Side" not in name: continue
    side = int(name.split("Side")[1].split("_")[0])
    ieta = int(name.split("IEta")[1].split("_")[0])
    ieta *= side
    iphi = int(name.split("IPhi")[1].split("_")[0])
    depth = int(name.split("Depth")[1].split("_")[0])

    bin = response_hist_mean.FindBin(ieta, iphi)
    
    hist = in_file.Get(name)
    mean = hist.GetMean()
    rms  = hist.GetRMS()

    response_hist_2D.Fill(mean, rms)

    if mean < 200. or rms < 40:
        print "HO(", ieta, ",", iphi, "," , depth, ")", "\t mean = %1.1f" % mean, "\t rms = %1.1f" % rms
        save_hists.append ( hist )
        save_hists[-1].GetXaxis().SetTitle("Charge integrated over all TS [fC]")
        save_hists[-1].GetYaxis().SetTitle("Number of events")
    
    response_hist_mean.SetBinContent(bin, mean )
    response_hist_rms.SetBinContent(bin, rms )

canvas = r.TCanvas()
canvas.cd()
canvas.SetGridx()
canvas.SetGridy()

canvas.SetRightMargin(0.15)

save_name ="LED_response_channels.pdf"

canvas.Print(save_name +"[")
response_hist_mean.Draw("COLZ")


canvas.Update()
xmin = canvas.GetUxmin();
xmax = canvas.GetUxmax();
ymin = canvas.GetUymin();
ymax = canvas.GetUymax();
ylength = ymax - ymin

tex = r.TLatex()
tex.SetTextSize(0.05)
tex.SetTextFont(42)
tex.SetTextColor(r.kBlack)
tex.DrawLatex(xmin, ymin + 1.03 * ylength, "Mean of charge [fC] integrated over all TS" )

canvas.Print(save_name)
response_hist_rms.Draw("COLZ")

canvas.Update()
xmin = canvas.GetUxmin();
xmax = canvas.GetUxmax();
ymin = canvas.GetUymin();
ymax = canvas.GetUymax();
ylength = ymax - ymin

tex = r.TLatex()
tex.SetTextSize(0.05)
tex.SetTextFont(42)
tex.SetTextColor(r.kBlack)
tex.DrawLatex(xmin, ymin + 1.03 * ylength, "RMS of charge [fC] integrated over all TS" )


canvas.Print(save_name)
response_hist_2D.Draw("COLZ")


canvas.Update()
xmin = canvas.GetUxmin();
xmax = canvas.GetUxmax();
ymin = canvas.GetUymin();
ymax = canvas.GetUymax();
ylength = ymax - ymin

tex = r.TLatex()
tex.SetTextSize(0.05)
tex.SetTextFont(42)
tex.SetTextColor(r.kBlack)
tex.DrawLatex(xmin, ymin + 1.03 * ylength, "Mean vs. RMS of charge [fC] integrated over all TS")


canvas.Print(save_name)

r.gStyle.SetOptStat(old)

for hist in save_hists:
    hist.GetXaxis().SetRangeUser(0, 300);
    hist.Draw()

    
    canvas.Update()
    xmin = canvas.GetUxmin();
    xmax = canvas.GetUxmax();
    ymin = canvas.GetUymin();
    ymax = canvas.GetUymax();
    ylength = ymax - ymin

    
    name = hist.GetName()
    side = int(name.split("Side")[1].split("_")[0])
    ieta = int(name.split("IEta")[1].split("_")[0])
    ieta *= side
    iphi = int(name.split("IPhi")[1].split("_")[0])
    depth = int(name.split("Depth")[1].split("_")[0])

    title = "HO(" + str(ieta) + ", " + str(iphi) + ", " + str(depth) + ") charge [fC] integrated over all TS"
    
    tex = r.TLatex()
    tex.SetTextSize(0.05)
    tex.SetTextFont(42)
    tex.SetTextColor(r.kBlack)
    tex.DrawLatex(xmin, ymin + 1.03 * ylength, title)
    canvas.Print(save_name)


canvas.Print(save_name +"]")

