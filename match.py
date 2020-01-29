# -*- coding: utf-8 -*-
"""
Created on Wed Oct 23 11:23:01 2019

@author: 陈焯阳
"""

def longestCommonPrefix(s1, s2):
    i = 0
    while i < len(s1) and i < len(s2) and s1[i] == s2[i]:
        i += 1
    return s1[:i]

def match(s1, s2):
    if len(s1) != len(s2):
        return False
    
    for i in range(len(s1)):
        if s1[i] != s2[i]:
            return False
    
    return True

def reverseComplement(s):
    complement = {'A':'T', 'C':'G', 'T':'A', 'G':'C', 'N':'N'}
    c = ''
    for i in s:
        c = complement[i] + c
    return c
'''
longestCommonPrefix('ACGTTATAT', 'ACGTCGTA')
match('ATCGT', 'ATCGC')
reverseComplement('AAAATTTT')
'''
def naive(p, t):
    occurences = []
    for i in range((len(t)-len(p)) + 1):
        match = True
        for j in range(len(p)):
            if p[j] != t[i+j]:
                match = False
                break
        if match:
            occurences.append(i)
    return occurences
'''
naive('dream','I have a dream')

from readGenome import readGenome
genome = readGenome('phix.fa')
'''
import random
def generateReads(genome, numReads, readLen):
    reads = []
    for _ in range(numReads):
        start = random.randint(0, len(genome)-readLen)
        reads.append(genome[start : start+readLen])
    return reads
'''
reads = generateReads(genome, 100, 100)
numMatched = 0
for r in reads:
    matches = naive(r, genome)
    if len(matches) > 0:
        numMatched += 1
print('%d / %d reads matched exactly!' %(numMatched, len(reads)))

#import wget
#wget.download('https://d28rh4a8wq0iu5.cloudfront.net/ads1/data/ERR266411_1.first1000.fastq')

from readFastq import readFastq
phix_reads, _ = readFastq('ERR266411_1.first1000.fastq')
numMatched = 0
n = 0
for r in phix_reads:
    r = r[:30] #allow part of reads match
    matches = naive(r, genome)
    matches.extend(naive(reverseComplement(r), genome))
    n += 1
    if len(matches) > 0:
        numMatched += 1
print('%d / %d reads matched exactly!' %(numMatched, n))
'''