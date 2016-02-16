import os
from subprocess import call
from sys import argv

if not len(argv)==5:
	print "Usage: python run.py macros/analysisClass_YourAnalysis.C config/inputfilelist config/treelist output.root"
	exit(1)
else:
	if(os.path.exists("./src/analysisClass.C")):
		if not argv[1] in  os.readlink("./src/analysisClass.C") and os.path.exists("./src/analysisClass.o"):
			os.remove("./src/analysisClass.o")
		os.remove("./src/analysisClass.C")
	os.symlink("../%s"%argv[1],"./src/analysisClass.C")
	exitcode = call("make")
	if not exitcode==0:
		print "Compile failed ... "
	else:	
		call(["./main",argv[2],argv[3],argv[4]])
