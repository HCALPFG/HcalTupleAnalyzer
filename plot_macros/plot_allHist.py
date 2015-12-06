
import ROOT
from PlotParser import parser
from Utils.rootTools import SetPalette

setPalette = SetPalette()
setPalette("kBird")

parser.add_argument('-d', metavar="drawOption", dest='drawOption',action="store" , required=False, help='draw option',type=str,default="colz")
parser.add_argument('-l', dest='logz',action="store_true" , required=False, help='draw option',default=False)

ROOT.gROOT.SetBatch(ROOT.kTRUE)
args = parser.parse_args()
inFileName = args.inputPath
outFileName = args.outputPath
drawOption = args.drawOption
setLogZ = args.logz

inputFile = ROOT.TFile(inFileName,"READ")
histNames = [k.GetName() for k in inputFile.GetListOfKeys()]
hists = [ inputFile.Get(histName) for histName in histNames]

hists.sort(key=lambda x: x.GetName())

c = ROOT.TCanvas()
if setLogZ:
	c.SetLogz()
c.Print(outFileName+"[")
for i,hist in enumerate(hists):
	hist.SetStats(0)
	hist.Draw(drawOption)
	hist.GetZaxis().SetRangeUser(0.01,1000.)
	c.Print(outFileName)
c.Print(outFileName+"]")
inputFile.Close()

