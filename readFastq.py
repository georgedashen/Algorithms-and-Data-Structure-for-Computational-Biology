# -*- coding: utf-8 -*-
"""
Created on Wed Oct 23 13:03:56 2019

@author: 陈焯阳
"""

def readFastq(filename):
    sequences = []
    qualities = []
    with open(filename) as f:
        while True:
            f.readline()
            seq = f.readline().rstrip()
            f.readline()
            qual = f.readline().rstrip()
            if len(seq) == 0:
                break
            sequences.append(seq)
            qualities.append(qual)
    return sequences, qualities
'''
seqs, quals = readFastq('SRR835775_1.first1000.fastq')
print(seqs[:5])
print(quals[:5])

def phred33ToQ(qual):
    return ord(qual) - 33

def createHist(qualities):
    hist = [0] * 50
    for qual in qualities:
        for phred in qual:
            q = phred33ToQ(phred)
            hist[q] += 1
    return hist

h = createHist(quals)

import matplotlib.pyplot as plt
plt.bar(range(len(h)), h)
plt.show()
'''
def findGCByPos(reads):
    gc = [0] * 100
    totals = [0] * 100
    
    for read in reads:
        for i in range(len(read)):
            if read[i] == 'C' or read[i] == 'G':
                gc[i] += 1
            totals[i] += 1
    for i in range(len(gc)):
        if totals[i] > 0: # not necessary
            gc[i] /= float(totals[i])
    
    return gc
'''
gc = findGCByPos(seqs)
plt.plot(range(len(gc)), gc)
plt.show()

import collections
count = collections.Counter()
for seq in seqs:
    count.update(seq)
print(count)
''' 