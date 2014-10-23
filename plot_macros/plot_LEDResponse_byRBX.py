import ROOT as r

r.gStyle.SetOptStat(0)
r.gStyle.SetOptTitle(0)

in_file = r.TFile("Run228119.root");

RBXs = ["HO2M02",
        "HO2M04",
        "HO2M06",
        "HO2M08",
        "HO2M10",
        "HO2M12",
        "HO1M02",
        "HO1M04",
        "HO1M06",
        "HO1M08",
        "HO1M10",
        "HO1M12",
        "HO001",
        "HO002",
        "HO003",
        "HO004",
        "HO005",
        "HO006",
        "HO007",
        "HO008",
        "HO009",
        "HO010",
        "HO011",
        "HO012",
        "HO1P02",
        "HO1P04",
        "HO1P06",
        "HO1P08",
        "HO1P10",
        "HO1P12",
        "HO2P02",
        "HO2P04",
        "HO2P06",
        "HO2P08",
        "HO2P10",
        "HO2P12" ]

x = []
y = []
ex = []
ey = []

response_hist = r.TH1F("response_hist", "response_hist", 36, -0.5, 35.5)
for iRBX, RBX in enumerate(RBXs):
    response_hist.GetXaxis().SetBinLabel(iRBX + 1, RBX)
response_hist.LabelsOption("V")
response_hist.SetLineColor(r.kBlue)
response_hist.SetMarkerColor(r.kBlue)
response_hist.SetLineWidth(3)
    
for iRBX, RBX in enumerate(RBXs):
    hist_name = RBX + "_energy"
    hist = in_file.Get(hist_name)
    mean = hist.GetMean()
    rms  = hist.GetRMS()
    response_hist.SetBinContent(iRBX + 1, mean)
    response_hist.SetBinError  (iRBX + 1, rms )

canvas = r.TCanvas()
canvas.cd()
canvas.SetGridx()
canvas.SetGridy()
response_hist.Draw("E")

canvas.SaveAs("LED_response.pdf")
