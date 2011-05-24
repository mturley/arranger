#!/usr/bin/python
import os
import subprocess
import argparse
import sys

parser = argparse.ArgumentParser(description='Generate lilypond fragments.')
parser.add_argument('-r','--res',type=int,help='output resolution',default=200)
parser.add_argument('infile',    help='name of lilypond file')
parser.add_argument('name',      help='name of output file')

args = parser.parse_args()

# generate png
r_lilypond = subprocess.call(['lilypond','--png',
                                         '-dresolution=%i' % (args.res),
                                         '-o%s' % (args.name),
                                         args.infile])

# if it exists, remove the postscript file
name_ps = '%s.ps' % (args.name)
if(os.path.exists(name_ps)) :
  os.remove(name_ps)

# if it exists, cut off the whitespace of the png file
name_png = '%s.png' % (args.name)
if(os.path.exists(name_png)) :
  subprocess.call(['convert',name_png,'-trim','+repage',name_png])

sys.exit(r_lilypond)
