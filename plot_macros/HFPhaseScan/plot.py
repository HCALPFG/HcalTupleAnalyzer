import ROOT as r
from array import array

contours = [ -4.5, -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5 ]
colors   = [ r.kViolet, r.kBlue, r.kCyan, r.kGreen, r.kWhite,r.kOrange, r.kRed ]



file = r.TFile("graphs.root")

hist1 = file.Get("shift_depth1")
hist1.SetContour(len(contours), array("d", contours))
hist1.SetTitle("Recommended timing shift [ns], depth = 1")
hist1.GetXaxis().SetTitle("ieta")
hist1.GetYaxis().SetTitle("iphi")
hist1.SetMinimum(-4.5)
hist1.SetMaximum(2.5)

hist2 = file.Get("shift_depth2")
hist2.SetContour(len(contours), array("d", contours))
hist2.SetTitle("Recommended timing shift [ns], depth = 2")
hist2.GetXaxis().SetTitle("ieta")
hist2.GetYaxis().SetTitle("iphi")
hist2.SetMinimum(-4.5)
hist2.SetMaximum(2.5)

r.gStyle.SetOptStat( 0 )
r.gStyle.SetPalette ( len (colors), array("i", colors))

canvas = r.TCanvas()
hist1.Draw("COLZ")
canvas.SaveAs("shift_depth1.png")

hist2.Draw("COLZ")
canvas.SaveAs("shift_depth2.png")


