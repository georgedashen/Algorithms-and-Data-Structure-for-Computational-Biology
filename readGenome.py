# -*- coding: utf-8 -*-
"""
Created on Wed Oct 23 12:50:32 2019

@author: 陈焯阳
"""

def readGenome(filename):
    genome = ''
    with open(filename) as f:
        for line in f:
            if line[0] != '>':
                genome += line.rstrip()
    return genome
'''
genome = readGenome('ABCG8.fasta')
genome[:100]
len(genome)

counts = {'a':0, 'c':0, 'g':0, 't':0}
for base in genome:
    counts[base] += 1
print(counts)

import collections
collections.Counter(genome) #using package
'''