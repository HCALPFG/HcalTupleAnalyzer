
import ROOT
from PlotParser import parser

ROOT.gROOT.SetBatch(ROOT.kTRUE)
parser.add_argument('-s', metavar="select", dest='select',action="store" , required=True, help='prefix for selecting plots',type=str)
parser.add_argument('-d', metavar="option", dest='option',action="store" , required=True, help='draw option',type=str)

args = parser.parse_args()

inFileName = args.inputPath
outFileName = args.outputPath
hist_prefix = args.select
drawOption = args.option

inputFile = ROOT.TFile(inFileName,"READ")
histNames = [k.GetName() for k in inputFile.GetListOfKeys()]
hists = [ inputFile.Get(histName) for histName in histNames if hist_prefix in histName]
maximum = max([hist.GetMaximum() for hist in hists])

print "Total Number of Hist: %s"%len(hists)
c = ROOT.TCanvas()
c.Print(outFileName+"[")
for i,hist in enumerate(hists):
	# if not ((i & 1000) == 0): continue
	# print i
	hist.SetStats(0)
	hist.Draw(drawOption)
	c.Print(outFileName)
c.Print(outFileName+"]")
