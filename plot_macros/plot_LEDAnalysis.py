import ROOT as r
from array import array

inputFilePath = "output/HO_LED_LocalRuns_JanToMay2015.root"
histname_template = "adcSum_%s_%s"
outPath = "~/www/hcal/HCALPFG/201500727_HO_LEDAnalysis/AverageADC_vs_RunNumber.pdf"

runs = [231939,233771,238181,239598,243321]
depths = [4]
ietas = [ -15+i  for i in range(31)]
iphis = range(73)[1:]

selectedChannel = [(1,15,4),(4,15,4)]

# Open input file
inputFile = r.TFile(inputFilePath,"READ")

c = r.TCanvas()

c.Print(outPath+"[")
for ieta in ietas:
	for iphi in iphis:
		for depth in depths:
			# if (ieta,iphi,depth) not in selectedChannel: continue
			adcSums = []
			for run in runs:
				histname = histname_template%(run,depth)
				hist = inputFile.Get(histname)
				xbin = hist.GetXaxis().FindBin(ieta)
				ybin = hist.GetYaxis().FindBin(iphi)
				adcSum = hist.GetBinContent(xbin,ybin)
				adcSums.append(adcSum)
			graph = r.TGraph(len(runs),array("d",runs),array("d",adcSums))
			graph.SetTitle("%s %s %s  ; Run Number ; Average ADC Count"%(ieta,iphi,depth))
			c.Clear()
			graph.Draw()
			c.Print(outPath)
c.Print(outPath+"]")

				
# c.SaveAs("~/MyICWebsite/Hcal/HO_LEDAnalysis/AverageADC_vs_RunNumber.pdf")
