#----------------------------------------------------------------------------
# Imports
#----------------------------------------------------------------------------

import subprocess as sp
import sys, os, re
import argparse

def atoi(text):
    return int(text) if text.isdigit() else text

def natural_keys(text):
    return [ atoi(c) for c in re.split('(\d+)', text) ]


#----------------------------------------------------------------------------
# Get input and output folders
# NB: only EOS folders are currently supported
#----------------------------------------------------------------------------

parser = argparse.ArgumentParser(description='Make an input list')
parser.add_argument('-i', metavar='INPUT' , dest='input_folders',action="store", required=True,nargs='*', help='(List of EOS or dCache folders (separated by spaces) to be used as input')
parser.add_argument('-o', metavar="OUTPUT", dest='output_folder',action="store" , required=True, help='Output folder where input list will be stored')
args = parser.parse_args()

#----------------------------------------------------------------------------
# Are we at FNAL or CERN?
#----------------------------------------------------------------------------

at_cern = False
at_fnal = False

if "HOSTNAME" in os.environ:
    at_fnal = ("fnal.gov" in os.environ["HOSTNAME"])
    at_cern = ("cern.ch"  in os.environ["HOSTNAME"] or "lxplus" in os.environ["HOSTNAME"])

#----------------------------------------------------------------------------
# Is there an EOS folder in our directories?
#----------------------------------------------------------------------------

use_eos = False
for input_folder in args.input_folders:
    if input_folder.startswith("/eos/"):
        use_eos = True
        break

#----------------------------------------------------------------------------
# Is there a /pnfs/ (dcache) folder in our directories?
#----------------------------------------------------------------------------

use_dcache = False
for input_folder in args.input_folders:
    if "/pnfs/" in input_folder:
        use_dcache = True
        break

#----------------------------------------------------------------------------
# If we're using EOS, get the latest/greatest EOS binary
#----------------------------------------------------------------------------

if use_eos and at_cern:
    eos_bin = sp.Popen ( "find /afs/cern.ch/project/eos/installation/ -name 'eos.select' | xargs ls -rt1 | tail -1", shell=True, stdout=sp.PIPE ).communicate()[0].strip()
    ls_command = eos_bin + " ls " 
else:
    ls_command = "ls "
    

#----------------------------------------------------------------------------
# Get list of file paths 
#----------------------------------------------------------------------------

file_paths = []
for folder in args.input_folders:
    this_ls_command = ls_command + folder 
    files = sp.Popen ( this_ls_command, shell=True, stdout=sp.PIPE ).communicate()[0].split()
    if use_eos and at_cern:
        file_paths = file_paths + ["root://eoscms/" + folder + "/" + i for i in files]
    elif use_dcache:
        file_paths = file_paths + ["dcache:" + folder + "/" + i for i in files]
    else:
        file_paths = file_paths + [folder + "/" + i for i in files]

file_paths.sort(key=natural_keys)

#----------------------------------------------------------------------------
# If the output directory does not exist, create it
#----------------------------------------------------------------------------

if not os.path.isdir ( args.output_folder ):
    os.system ( "mkdir -p " + args.output_folder )

#----------------------------------------------------------------------------
# Write the output list
#----------------------------------------------------------------------------

output_file_path = args.output_folder + "/inputListAll.txt"
output_file = open (output_file_path,"w")
for path in file_paths:
    output_file.write(path + "\n")
output_file.close()

#----------------------------------------------------------------------------
# Tell the user that we're done
#----------------------------------------------------------------------------

print "Success! I wrote an input list:"
print "\t", output_file_path
