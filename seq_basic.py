# -*- coding: utf-8 -*-
"""
Created on Wed Oct 23 10:58:49 2019

@author: 陈焯阳
"""

seq = 'ACGT'
seq[1]
len(seq)
e = ''
len(e)

seq1 = 'CCAA'
seq2 = 'GGTT'
print(seq + seq2)

seqs = ['A', 'C', 'G', 'T']
print(''.join(seqs))

import random
random.choice('ACGT')

random.seed(7)
seq = ''
for _ in range(10):
    seq += random.choice('ACGT')
print(seq)

seq_join = ''.join([random.choice('ACGT') for _ in range(10)])
print(seq_join)
seq[1:3]
seq[:3] #get prefix
#exactly the same as seq[0:3]

seq[7:len(seq)] #get suffix
seq[-3:] #the last 3 elements
