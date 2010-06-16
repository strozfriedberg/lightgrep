#!/usr/bin/env python
# encoding: utf-8
"""
regression.py

Created by Jon Stewart on 2010-05-05.
Copyright (c) 2010 Lightbox Technologies, Inc. All rights reserved.
"""

import sys
import os
import subprocess
import os.path as p
import filecmp

keysDir = './pytest/keys'
docsDir = './pytest/corpora'
resultsDir = './pytest/results'
tempDir = './tmp'

def run(lightgrep, keypath, docpath, temppath):
#  print(keypath)
  results = os.open(temppath, os.O_CREAT)
  proc = subprocess.Popen(['time', lightgrep, 'search', keypath, docpath], stdout=results, stderr=subprocess.PIPE)
  cerr = proc.communicate()[1].splitlines()
  #print cerr
  rec = {}
  for line in cerr:
    #print line
    atoms = line.split()
    while (len(atoms) >= 2):
      if (line.find("system")>0):
        idxsys = line.find("system")
        idxsplit = line.find(" ")
        idxusr = line.find("user")
        rec["real"] = "N/A"
        rec["user"] = line[0:idxusr]
        rec["sys"] = line[idxsplit:idxsys]
        break
      else:
        key = atoms.pop()
        rec[key] = atoms.pop()
  print("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s" % (docpath,
                                                    keypath,
                                                    rec['keywords'],
                                                    rec['vertices'],
                                                    rec['instructions'],
                                                    rec['hits'],
                                                    rec['real'],
                                                    rec['user'],
                                                    rec['sys'],
                                                    rec['searchTime']))

def main():
  keyfiles = os.listdir(keysDir)
  corpora = os.listdir(docsDir)
  lightgrep = p.abspath('./bin/test/test')
  print("doc\tkeyfile\tkeywords\tvertices\tinstructions\thits\treal\tuser\tsys\tsearchTime")
  if (p.exists(tempDir) == False):
    os.mkdir(tempDir)
  for doc in corpora:
    docpath = p.abspath(p.join(docsDir, doc))
    for k in keyfiles:
      keypath = p.abspath(p.join(keysDir, k))
      temppath = p.abspath(p.join(tempDir, k))
      run(lightgrep, keypath, docpath, temppath)
#      run('%s search %s %s > %s' % (lightgrep, keypath, docpath, resultspath))
  diff = filecmp.dircmp(resultsDir, tempDir)
  if (len(diff.diff_files) > 0 or len(diff.left_only) > 0 or len(diff.right_only) > 0):
    filecmp.dircmp(resultsDir, tempDir).report()

if __name__ == '__main__':
  main()
